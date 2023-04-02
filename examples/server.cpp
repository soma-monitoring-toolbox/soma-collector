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
static constexpr int soma_comm_split_color = 88;
static MPI_Comm soma_comm = MPI_COMM_WORLD;

static void parse_command_line(int argc, char** argv);

static void setup_admin_nodes(tl::engine engine, std::string server_addr, int rank, int size) {
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

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    ofstream addr_file;
    parse_command_line(argc, argv);
    MPI_Barrier(MPI_COMM_WORLD);
    int rank, size;
    int key, color;
    int new_rank;

    tl::engine engine(g_address, THALLIUM_SERVER_MODE, g_use_progress_thread, g_num_threads);
    std::vector<snt::Provider> providers;

    engine.enable_remote_shutdown();
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    MPI_Comm_split(MPI_COMM_WORLD, soma_comm_split_color, world_rank, &soma_comm); 
    MPI_Comm new_comm;
    MPI_Comm_rank(soma_comm, &rank);
    MPI_Comm_size(soma_comm, &size);

    std::cout << "SOMA COMM rank: " << rank << " and SOMA COMM size: " << size << endl;

    if(rank == 0) {
	    addr_file.open(getenv("SOMA_SERVER_ADDR_FILE"), ios::app);
	    addr_file << size << "\n";
	    addr_file.close();
    }
   
    int num_instances = std::stoi(std::string(getenv("SOMA_NUM_SERVER_INSTANCES")));

    if(num_instances == 1) {
        for(int i = 0; i < size; i++) {
	    if(rank == i) {
		    addr_file.open(getenv("SOMA_SERVER_ADDR_FILE"), ios::app);
		    addr_file << rank << " " << (std::string)engine.self() << "\n";
		    addr_file.close();
	    }
	    MPI_Barrier(soma_comm);
        }
        MPI_Comm_dup(soma_comm, &new_comm);
    } else {
        key = rank;
        color = (int)(rank/(size/num_instances));
        MPI_Comm_split(soma_comm, color, key, &new_comm);
        MPI_Comm_rank(new_comm, &new_rank);

        for(int i = 0; i < size; i++) {
	    if(rank == i) {
		    addr_file.open(getenv("SOMA_SERVER_ADDR_FILE"), ios::app);
		    addr_file << new_rank << " " << (std::string)engine.self() << "\n";
		    addr_file.close();
	    }
	    MPI_Barrier(soma_comm);
        }
    }
       
    for(unsigned i=0 ; i < g_num_providers; i++) {
        providers.emplace_back(engine, i, new_comm);
    }

    MPI_Barrier(soma_comm);
    setup_admin_nodes(engine, (std::string)engine.self(), rank, size);

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
