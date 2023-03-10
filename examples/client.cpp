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
#include <conduit/conduit.hpp>
#include <mpi.h>

namespace tl = thallium;
using namespace conduit;
int use_local = 0;

static std::string g_address_file;
static std::string g_address;
static std::string g_protocol;
static std::string g_collector;
static unsigned    g_provider_id;
static std::string g_log_level = "info";

static void parse_command_line(int argc, char** argv);

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

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    parse_command_line(argc, argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Initialize the thallium server
    tl::engine engine(g_protocol, THALLIUM_CLIENT_MODE);

    try {

        // Initialize a Client
        soma::Client client(engine);

        // Open the Database "mydatabase" from provider 0
        soma::CollectorHandle collector =
            client.makeCollectorHandle(g_address, g_provider_id,
                    soma::UUID::from_string(g_collector.c_str()));

        collector.sayHello();

        // Test compute sum
        int32_t result;
        collector.computeSum(32, 54, &result);

        // Test Conduit Node
        Node n;
        n["test"] = "test_value";
        collector.soma_publish(n);

    } catch(const soma::Exception& ex) {
        std::cerr << ex.what() << std::endl;
        exit(-1);
    }

    MPI_Finalize();
    return 0;
}

void parse_command_line(int argc, char** argv) {

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

	/* The logic below grabs the server address corresponding the client's MPI rank (MXM case) */
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
}
