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
#include <filesystem>

namespace tl = thallium;
int use_local = 0;

static std::string g_address_file;
static std::string g_address;
static std::string g_protocol;
static std::string g_collector;
static unsigned    g_provider_id;
static std::string g_log_level = "info";
static constexpr int rp_mon_comm_split_color = 99;
static MPI_Comm rp_mon_comm = MPI_COMM_WORLD;

static thallium::engine *engine;
static soma::Client *client;
static soma::CollectorHandle soma_collector;
static soma::NamespaceHandle *ns_handle;
int server_instance_id = 0;
static std::vector<thallium::async_response> requests;

//static void parse_command_line();

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
    std::cerr << "protocol " << g_protocol << std::endl; 
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
    
    int my_rank, my_size, world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_split(MPI_COMM_WORLD, rp_mon_comm_split_color, world_rank, &rp_mon_comm);
    MPI_Comm_rank(rp_mon_comm, &my_rank);
    MPI_Comm_size(rp_mon_comm, &my_size);

    // set up timers
    std::chrono::time_point start_init_time = std::chrono::steady_clock::now();

    parse_command_line(my_rank);
    
    // Initialize the thallium server
    engine = new tl::engine(g_protocol, THALLIUM_CLIENT_MODE);

    try {

        // Initialize a Client
        client = new soma::Client(*engine);
        
	// Create the client handle 
        soma_collector = (*client).makeCollectorHandle(g_address, g_provider_id,
                    soma::UUID::from_string(g_collector.c_str()));
	ns_handle = soma_collector.soma_create_namespace("RP");

	// Get ENV VAR settings	
	int monitoring_frequency = 1;
        char * frequency = getenv("RP_SOMA_MONITORING_FREQUENCY");
	if (frequency != NULL) { 
	    monitoring_frequency = std::atoi(frequency);
	}
	soma_collector.soma_set_publish_frequency(ns_handle, monitoring_frequency);
	std::cout << "RP: Monitoring/publish frequency is: " << monitoring_frequency << std::endl;
	
	int write_frequency = 100;
        char * w_frequency = getenv("RP_WRITE_FREQUENCY");
	if (w_frequency != NULL) { 
	    write_frequency = std::atoi(w_frequency);
	}
	int write_counter = write_frequency;
	std::cout << "RP_WRITE_FREQUENCY: Write to file frequency is: " << write_counter  << std::endl;
        
	int sleep_time = 100;
	char * sleepy = getenv("RP_SOMA_SLEEP_TIME");
	if (sleepy != NULL) { 
	    sleep_time = std::atoi(sleepy);
	}
	std::cout << "RP_SOMA_SLEEP_TIME is " << sleep_time << " ms" << std::endl;
	
	int run_time = 10;
	char * runny = getenv("RP_SOMA_RUN_TIME");
	if (runny != NULL) { 
	    run_time = std::atoi(runny);
	}
	std::cout << "RP_SOMA_RUN_TIME is " << run_time << " ms" << std::endl;
	
	std::string rp_file_path = getenv("RP_FILE_PATH");
	std::cout << "Reading from RP file sandbox: " << rp_file_path << std::endl;

	// update timers
        std::chrono::duration initial_time(std::chrono::steady_clock::now() - start_init_time);
        std::chrono::duration total_pub_time = std::chrono::nanoseconds::zero();
        std::chrono::duration total_read_time = std::chrono::nanoseconds::zero();
        std::chrono::duration total_write_time = std::chrono::nanoseconds::zero();

	//std::chrono::duration total_time(initial_time);
        int num_samples = 0;

        // temporarily hardcode a run of 10 minutes
        std::chrono::time_point start = std::chrono::steady_clock::now();
	bool keep_running = true;

	while (keep_running) {	
	    
	    std::chrono::time_point start_read_time = std::chrono::steady_clock::now();
	  
	    // Check which task folders exist
	    for (const auto &entry : std::filesystem::directory_iterator(rp_file_path)){
	    	if (entry.is_directory()) {
		    if (entry.path().string().find("task") != std::string::npos) {
			std::string task_dir = entry.path().string();
			for (const auto &taskfile : std::filesystem::directory_iterator(task_dir)) {
			    if (taskfile.path().string().find(".prof") != std::string::npos) {

				std::string rp_file_name = taskfile.path().string();
	    			// Periodically read from RP files
	    			std::string rp_time_key = rp_file_name; 
	    			// read from rp profile to get workflow data
	    			auto rp_fs = std::ifstream(rp_file_name);
	    			std::string line;
            			while( std::getline(rp_fs, line) ) {            
	    			    auto line_ss = std::istringstream(line);
				    std::string val;
				    int i = 0;
				    std::string label, time, event, comp, thread, uid, state, msg;
				    while( std::getline(line_ss, val, ',') ) {            
		    			switch (i) {
						case 0:
		            				time = val;
			    				break;
		        			case 1:
			    				event = val;
			    				break;
		        			case 2: 
		            				comp = val;
			   			 	break;
	                			case 3:
	      		    				thread = val;
			    				break;
		        			case 4:
    			    				uid = val;
			    				break;
		        			case 5:
    			    				state = val;
			    				break;
		        			case 6:
    			    				msg = val;
			    				break;
		    			}			
		    			i++;
	            		}
				// Update the namespace per low level metric
                		soma_collector.soma_update_namespace(ns_handle, rp_time_key, time, event, soma::OVERWRITE);    
            		
				}
			    }
			}
		    }
		}
	    }
	    
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

	    write_counter--;
	    bool shutdown = (std::chrono::steady_clock::now() - start) >= std::chrono::minutes(run_time); 
	    //if we've hit our runtime minute duration we write and exit, else just write
	    if(write_counter == 0 || shutdown) {

		std::chrono::time_point start_write_time = std::chrono::steady_clock::now();
                // write to file
                std::string outfile = "rp_data_soma.txt";
                bool write_done;
                soma_collector.soma_write(outfile, &write_done, soma::OVERWRITE);
		std::chrono::duration write_time(std::chrono::steady_clock::now() - start_write_time);
                total_write_time += write_time;
		
                if (shutdown) {

                    using Ss = std::chrono::milliseconds;
		    std::cout << "RP Client Write Time " << std::chrono::duration_cast<Ss>(write_time).count() << std::endl;
                    std::cout << "RP Client Initialization Time " << std::chrono::duration_cast<Ss>(initial_time).count()  << std::endl;
                    std::cout << "RP Client Read Time " << std::chrono::duration_cast<Ss>(total_read_time).count() << std::endl;
                    std::cout << "RP CLient Pub Time " << std::chrono::duration_cast<Ss>(total_pub_time).count() << std::endl;
                    //std::cout << "RP Client Total Time " << std::chrono::duration_cast<Ss>(total_time).count() << std::endl;
                    std::cout << "RP Client Num Samples " << num_samples << std::endl;
		    // sleep so write can finish and then exit
                    std::this_thread::sleep_for(std::chrono::minutes(1));
                    keep_running = false;
	        }
		// reset the write counter
		write_counter = write_frequency;

            }

	    // Configured with an environment variable
	    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	} // end while

    } catch(const soma::Exception& ex) {
        std::cerr << ex.what() << std::endl;
        exit(-1);
    }

   /* for(auto i = requests.begin(); i != requests.end(); i++) {
        i->wait();
    }

    if (mon_rank == 0) {
        std::string outfile = "rp_data_soma.txt";
        bool write_done;
        soma_collector.soma_write(outfile, &write_done);
    }*/

    if (rp_mon_comm != MPI_COMM_WORLD) {
        MPI_Comm_free(&rp_mon_comm);
        rp_mon_comm = MPI_COMM_NULL;
    }
    MPI_Finalize();
    return 0;
}

/*void parse_command_line(int argc, char** argv) {

    try {
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

        TCLAP::CmdLine cmd("SOMA client", ' ', "0.1");
        TCLAP::ValueArg<std::string> addressArg("a","address","Address or server", true,"","string");
        TCLAP::ValueArg<unsigned>    providerArg("p", "provider", "Provider id to contact (default 0)", false, 0, "int");
        TCLAP::ValueArg<std::string> nodeArg("r","node","Node id", true, soma::UUID().to_string(),"string");
        TCLAP::ValueArg<std::string> logLevel("v","verbose", "Log level (trace, debug, info, warning, error, critical, off)", false, "info", "string");
        cmd.add(addressArg);
        cmd.add(providerArg);
        cmd.add(nodeArg);
        cmd.add(logLevel);
        cmd.parse(argc, argv);

	// The logic below grabs the server address corresponding the client's MPI rank (MXM case) 
	size_t pos = 0;
        g_address_file = addressArg.getValue();
	std::string delimiter = " ";
	std::string l = read_nth_line(g_address_file, rank+1);
	pos = l.find(delimiter);
	std::string server_rank_str = l.substr(0, pos);
	std::stringstream s_(server_rank_str);
	int server_rank;
	s_ >> server_rank;
	assert(server_rank == rank);
	l.erase(0, pos + delimiter.length());
	g_address = l;

        g_provider_id = providerArg.getValue();
        g_collector = read_nth_line(nodeArg.getValue(), rank);
        g_log_level = logLevel.getValue();
        g_protocol = g_address.substr(0, g_address.find(":"));
    } catch(TCLAP::ArgException &e) {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
        exit(-1);
    }
}*/
