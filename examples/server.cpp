/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#include <soma/Provider.hpp>
#include <soma/Admin.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <tclap/CmdLine.h>
#include <mpi.h>

namespace tl = thallium;
namespace snt = soma;
using namespace std;

static std::string g_address = "na+sm";
static unsigned    g_num_providers = 1;
static int         g_num_threads = 0;
static std::string g_log_level = "info";
static bool        g_use_progress_thread = false;
static constexpr int soma_comm_split_color = 38;
static MPI_Comm soma_comm = MPI_COMM_WORLD;

static void parse_command_line(int argc, char** argv);

static void setup_admin_nodes(tl::engine engine, std::string server_addr, int rank, int size, MPI_Comm comm) {
    ofstream addr_file;

    // Initialize the thallium server
    soma::Admin admin(engine);

    for(int i = 0; i < size; i++) {
        if(rank == i) {
	    addr_file.open(getenv("SOMA_NODE_ADDR_FILE"), ios::app);
	    try {
		    auto id = admin.createCollector(server_addr, 0, "dummy", "{\"path\" : \"mydb\" }", "");
		    // Any of the above functions may throw a soma::Exception
		    addr_file << id.to_string() << "\n";
	    } catch(const soma::Exception& ex) {
	    	    std::cerr << ex.what() << std::endl;
	            exit(-1);
	    }
	    addr_file.close();
	}

	MPI_Barrier(soma_comm);
    }

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

int main(int argc, char** argv) {
    //MPI_Init(&argc, &argv);
    int thread_level = MPI_THREAD_MULTIPLE;
    if (!init_mpi_threaded(thread_level)){
          printf("Unable to initialize MPI at thread level %d\n", thread_level);
	  return 1;
    }

    int soma_rank, soma_size, world_rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    MPI_Comm soma_comm;
    MPI_Comm_split(MPI_COMM_WORLD, soma_comm_split_color, world_rank, &soma_comm);
    MPI_Comm_rank(soma_comm, &soma_rank);
    MPI_Comm_size(soma_comm, &soma_size);

    ofstream addr_file;
    parse_command_line(argc, argv);
    MPI_Barrier(soma_comm);
    
    tl::engine engine(g_address, THALLIUM_SERVER_MODE, g_use_progress_thread, g_num_threads);
    std::vector<snt::Provider> providers;

    engine.enable_remote_shutdown();

    int num_instances;
    try {
        num_instances = std::stoi(std::string(getenv("SOMA_NUM_SERVER_INSTANCES")));
    } catch (std::exception e){
        num_instances = 1;
    }


    int num_servers_per_instance;

    //If SOMA_NUM_SERVERS_PER_INSTANCE is set, use that to divide the servers into instances
    //Otherwise, if SOMA_NUM_SERVER_INSTANCES is set, divide the servers into that many instances (if possible)
    try {
    	num_servers_per_instance = std::stoi(std::string(getenv("SOMA_NUM_SERVERS_PER_INSTANCE")));
    } catch (std::exception e){
        num_servers_per_instance = soma_size/num_instances;
    }

    int instance_id = soma_rank / num_servers_per_instance;
    
    int soma_instance_rank, soma_instance_size;
    MPI_Comm soma_instance_comm;

    MPI_Comm_split(soma_comm, 1000 + instance_id, 0, &soma_instance_comm);
    MPI_Comm_rank(soma_instance_comm, &soma_instance_rank);
    MPI_Comm_size(soma_instance_comm, &soma_instance_size);

    if(soma_rank == 0) {
	    addr_file.open(getenv("SOMA_SERVER_ADDR_FILE"), ios::app);
	    addr_file << soma_size << "\n";
	    addr_file.close();
    }

    char * filename = getenv("SOMA_SERVER_ADDR_FILE");

    for(int i = 0; i < soma_size; i++) {
	if(soma_rank == i) {
	    addr_file.open(getenv("SOMA_SERVER_ADDR_FILE"), ios::app);
	    addr_file << soma_rank << " " << (std::string)engine.self() << "\n";
	    addr_file.close();
	}
	MPI_Barrier(soma_comm);

    }
      
    for(size_t i = 0 ; i < g_num_providers; i++) {
        providers.emplace_back(engine, i, soma_instance_comm);
    }
    
    //Not sure why this sync is needed...
    MPI_Barrier(soma_comm);
    setup_admin_nodes(engine, (std::string)engine.self(), soma_rank, soma_size, soma_comm);
    //Sync with client
    MPI_Barrier(MPI_COMM_WORLD);

    //std::cout << "SERVER SYNCED WITH CLIENT RANKS" << std::endl;
    engine.wait_for_finalize();
    MPI_Finalize();
    return 0;
}

void parse_command_line(int argc, char** argv) {
    try {
        TCLAP::CmdLine cmd("Spawns a Ams daemon", ' ', "0.1");
        TCLAP::ValueArg<std::string> addressArg("a","address","Address or protocol (e.g. ofi+tcp)", true,"","string");
        TCLAP::ValueArg<unsigned>    providersArg("n", "num-providers", "Number of providers to spawn (default 1)", false, 1, "int");
        TCLAP::SwitchArg progressThreadArg("p","use-progress-thread","Use a Mercury progress thread", cmd, false);
        TCLAP::ValueArg<int> numThreads("t","num-threads", "Number of threads for RPC handlers", false, 0, "int");
        TCLAP::ValueArg<std::string> logLevel("v","verbose", "Log level (trace, debug, info, warning, error, critical, off)", false, "info", "string");
        cmd.add(addressArg);
        cmd.add(providersArg);
        cmd.add(numThreads);
        cmd.add(logLevel);
        cmd.parse(argc, argv);
        g_address = addressArg.getValue();
        g_num_providers = providersArg.getValue();
        g_num_threads = numThreads.getValue();
        g_use_progress_thread = progressThreadArg.getValue();
        g_log_level = logLevel.getValue();
    } catch(TCLAP::ArgException &e) {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
        exit(-1);
    }
}
