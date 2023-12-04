/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#include <soma/Client.hpp>
#include <tclap/CmdLine.h>
#include <iostream>
#include <assert.h>
#include <sstream>
#include <fstream>
#include <conduit/conduit.hpp>
#include <mpi.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <limits.h>
#include <ctime>
#include <chrono>
#include <thread>


namespace tl = thallium;
int use_local = 0;

static std::string g_address_file;
static std::string g_address;
static std::string g_protocol;
static std::string g_collector;
static unsigned    g_provider_id;
static std::string g_log_level = "info";
static constexpr int mon_comm_split_color = 83;
static MPI_Comm mon_comm = MPI_COMM_WORLD;

static thallium::engine *engine;
static soma::Client *client;
static soma::CollectorHandle soma_collector;
static soma::NamespaceHandle *ns_handle;
int server_instance_id = 0;
static std::vector<thallium::async_response> requests;


static std::string read_nth_line(const std::string& filename, int n)
{
   std::ifstream in(filename.c_str());

   std::string s;
   //for performance
   s.reserve(200);

   //skip N lines
   for(int i = 0; i < n; ++i)
       std::getline(in, s);

   std::getline(in,s);
   return s;
}

void parse_command_line(int my_rank) {

    char *addr_file_name = getenv("SOMA_SERVER_ADDR_FILE");
    char *node_file_name = getenv("SOMA_NODE_ADDR_FILE");
    int num_server = 1;
    num_server = std::stoi(std::string(getenv("SOMA_NUM_SERVERS_PER_INSTANCE")));
    server_instance_id = std::stoi(std::string(getenv("SOMA_MON_SERVER_INSTANCE_ID")));
    int my_server_offset = my_rank % num_server;
    g_address_file = addr_file_name;
    std::string l = read_nth_line(g_address_file, server_instance_id*num_server + my_server_offset + 1);
    std::string delimiter = " ";
    size_t pos = 0;
    pos = l.find(delimiter);
    std::string server_rank_str = l.substr(0, pos);
    std::stringstream s_(server_rank_str);
    int server_rank;
    s_ >> server_rank;
    l.erase(0, pos + delimiter.length());
    g_address = l;
    g_provider_id = 0;
    g_collector = read_nth_line(std::string(node_file_name), server_instance_id*num_server + my_server_offset);
    g_protocol = g_address.substr(0, g_address.find(":"));
}

bool
init_mpi_threaded(int thread_level)
{
    int thread_support_level = -1;
    int result               = MPI_Init_thread(NULL, NULL, thread_level, &thread_support_level);
    if(thread_support_level < thread_level || result != MPI_SUCCESS) {
        return false;
    }
    return true;
}

int main() {
    //MPI_Init(&argc, &argv);
    int thread_level = MPI_THREAD_MULTIPLE;
    if (!init_mpi_threaded(thread_level)){
          printf("Unable to initialize MPI at thread level %d\n", thread_level);
          return 1;
    }
    
    int mon_rank, mon_size, world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_split(MPI_COMM_WORLD, mon_comm_split_color, world_rank, &mon_comm);
    MPI_Comm_rank(mon_comm, &mon_rank);
    MPI_Comm_size(mon_comm, &mon_size);
    
    // set up timers
    std::chrono::time_point start_init_time = std::chrono::steady_clock::now();

    parse_command_line(mon_rank);
    
    // Initialize the thallium server
    engine = new tl::engine(g_protocol, THALLIUM_CLIENT_MODE);

    try {

        // Initialize a Client
        client = new soma::Client(*engine);
        
	// Create the client handle 
        soma_collector = (*client).makeCollectorHandle(g_address, g_provider_id,
                    soma::UUID::from_string(g_collector.c_str()));
	ns_handle = soma_collector.soma_create_namespace("PROC");

	// Get ENV VAR settings	
	int monitoring_frequency = 1;
        char * frequency = getenv("PROC_SOMA_MONITORING_FREQUENCY");
	if (frequency != NULL) { 
	    monitoring_frequency = std::atoi(frequency);
	}
	soma_collector.soma_set_publish_frequency(ns_handle, monitoring_frequency);
	std::cout << "PROC: Monitoring/publish frequency is: " << monitoring_frequency << std::endl;
	
	int write_frequency = 100;
        char * w_frequency = getenv("PROC_WRITE_FREQUENCY");
	if (w_frequency != NULL) { 
	    write_frequency = std::atoi(w_frequency);
	}
	int write_counter = write_frequency;
	std::cout << "PROC_WRITE_FREQUENCY: Write to file frequency is: " << write_counter  << std::endl;
        
	int sleep_time = 5000;
	char * sleepy = getenv("PROC_SOMA_SLEEP_TIME");
	if (sleepy != NULL) { 
	    sleep_time = std::atoi(sleepy);
	}
	std::cout << "PROC_SOMA_SLEEP_TIME is " << sleep_time << " ms" << std::endl;

	int run_time = 10;
	char * runtime = getenv("PROC_SOMA_RUN_TIME");
	if (runtime != NULL) { 
	    run_time = std::atoi(runtime);
	}
	std::cout << "PROC_SOMA_RUN_TIME is " << run_time << " mins" << std::endl;
	//initialized = true;

	// Get Node Name
	char c_hostname[HOST_NAME_MAX];
	gethostname(c_hostname, HOST_NAME_MAX);
	std::string hostname(c_hostname);
	
	// update timers
	std::chrono::duration initial_time(std::chrono::steady_clock::now() - start_init_time);
	std::chrono::duration total_pub_time = std::chrono::nanoseconds::zero();
	std::chrono::duration total_read_time = std::chrono::nanoseconds::zero();
	//std::chrono::duration total_time(initial_time);
	int num_samples = 0;

	// temporarily hardcode a run of 10 minutes
	std::chrono::time_point start = std::chrono::steady_clock::now();

	while (1) {
	    
    	    std::chrono::time_point start_read_time = std::chrono::steady_clock::now();
	    auto now = std::chrono::system_clock::now();
	    std::time_t timestamp = std::chrono::system_clock::to_time_t(now);

	    // Periodically read from sysinfo
	    //std::time_t timestamp = std::time(nullptr);
	    //std::string host_time_key = hostname;
	    //std::string host_time_key = hostname + "/"+ std::to_string(timestamp);
	    std::string host_time_key = std::to_string(timestamp);
	    struct sysinfo info;
	    ::sysinfo(&info);
	    double utime = info.uptime;
	    double nprocs = info.procs;
	    double freeram = info.freeram;

	    // read from /proc/stat to get CPU load
	    auto stat_file = std::ifstream("/proc/stat");
	    std::string line, temp;
	    std::vector<double> cpu_vals;
            std::string stat_key = host_time_key + "/stat/";
	    while( std::getline(stat_file, line) ) {		
		// first line without cpu info will end reading
		if (line.find("cpu") == std::string::npos) {
    		    break;
		}
		int word_ct = 0;
		std::string word = "";
		std::string cpukey = "";
		std::string cpuval = "";
		std::istringstream iss{line};
		while (std::getline(iss, word, ' ')) {
		    if (word_ct == 0) {
			cpukey = word;
		    }
		    else {
			cpuval += " ";
	  		cpuval += word;
		    }
		    word_ct++;
		}
	        // Update the namespace with a list per line
		// first five chars become key, rest are value string
		soma_collector.soma_update_namespace(ns_handle, stat_key, cpukey, cpuval, soma::OVERWRITE); 	
		//soma_collector.soma_update_namespace(ns_handle, stat_key, line.substr(0,5), line.substr(6), soma::OVERWRITE); 	
	    }

	    soma_collector.soma_update_namespace(ns_handle, host_time_key, "Uptime", utime, soma::OVERWRITE);
	    soma_collector.soma_update_namespace(ns_handle, host_time_key, "Num Processes", nprocs, soma::OVERWRITE);
	    soma_collector.soma_update_namespace(ns_handle, host_time_key, "Available RAM", freeram, soma::OVERWRITE);

	    //end read timer & begin pub timer
	    std::chrono::time_point end_read_time = std::chrono::steady_clock::now();
	    // Publish to the SOMA server
            auto response = soma_collector.soma_commit_namespace_async(ns_handle);
	    if (response) {
	        requests.push_back(*std::move(response));
	    }

	    std::chrono::time_point end_pub_time = std::chrono::steady_clock::now();
	    std::chrono::duration read_time(end_read_time - start_read_time);
	    std::chrono::duration pub_time(end_pub_time - end_read_time);
	    total_read_time += read_time;
	    total_pub_time +=  pub_time;
	    num_samples += 1;
	    
	    // if we've hit our runtime minute duration we write and exit
	    if(std::chrono::steady_clock::now() - start > std::chrono::minutes(run_time)) { 
           	 
		using Ss = std::chrono::milliseconds;
		std::cout << "PROC Client Initialization Time " << std::chrono::duration_cast<Ss>(initial_time).count()  << std::endl;
		std::cout << "PROC Client Read Time " << std::chrono::duration_cast<Ss>(total_read_time).count() << std::endl;
		std::cout << "PROC Client Pub Time " << std::chrono::duration_cast<Ss>(total_pub_time).count() << std::endl;
		//std::cout << "PROC Client Total Time " << std::chrono::duration_cast<Ss>(total_time).count() << std::endl;
		std::cout << "PROC Client Num Samples " << num_samples << std::endl;
	    //write_counter--;
	    // Eventually will have a better shutdown signal for now just write every so often
	    //if (write_counter==0) {
		std::chrono::time_point start_write_time = std::chrono::steady_clock::now();
	        // write to file
                std::string outfile = hostname +"_proc_data_soma.txt";
                bool write_done;
                soma_collector.soma_write(outfile, &write_done, soma::OVERWRITE);
		
		std::cout << "PROC Client Writing to File: " << outfile << std::endl; 
		std::chrono::duration write_time(std::chrono::steady_clock::now() - start_write_time);
		std::cout << "PROC Client Write Time " << std::chrono::duration_cast<Ss>(write_time).count() << std::endl;
		// reset the write counter
	    	//write_counter = write_frequency;
	    //}
	    	// sleep so write can finish and then exit
		std::this_thread::sleep_for(std::chrono::minutes(1));
		break;
	

	    }

	    // Sleep for configured amount of time
	    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	} 

    } catch(const soma::Exception& ex) {
        std::cerr << ex.what() << std::endl;
        exit(-1);
    }

   /* for(auto i = requests.begin(); i != requests.end(); i++) {
        i->wait();
    }

    if (mon_rank == 0) {
        std::string outfile = "proc_data_soma.txt";
        bool write_done;
        soma_collector.soma_write(outfile, &write_done);
    }*/

    if (mon_comm != MPI_COMM_WORLD) {
        MPI_Comm_free(&mon_comm);
        mon_comm = MPI_COMM_NULL;
    }
    MPI_Finalize();
    return 0;
}

