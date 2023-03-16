#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <assert.h>
#include <ctype.h>
#include <unistd.h>
#include <mutex>

#include "soma_plugin.h"

#ifdef USE_MPI
#include<mpi.h>
#endif

/* Globals -- Yikes, I know. */
static bool enabled{false};
static bool initialized{false};
static bool opened{false};
static bool done{false};
static int my_rank = 0;
static int size = 0;
static std::string g_address_file;
static std::string g_address;
static std::string g_protocol = "na+sm";
static std::string g_collector;
static unsigned    g_provider_id;
static std::string g_log_level = "info";
int reduction_frequency = 1;
static thallium::engine *engine;
soma::Client *client;
soma::CollectorHandle soma_client;
int server_instance_id = 0;

/* Helper function to read and parse input args */
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

void parse_command_line(int myRank) {

    char *addr_file_name = getenv("SOMA_SERVER_ADDR_FILE");
    char *node_file_name = getenv("SOMA_NODE_ADDR_FILE");
    int num_server = 0;
    num_server = std::stoi(std::string(getenv("SOMA_NUM_SERVERS_PER_INSTANCE")));
    server_instance_id = std::stoi(std::string(getenv("SOMA_SERVER_INSTANCE_ID")));
    int my_server_offset = num_server % (myRank+1);
    std::cout << "myRank, my_server_offset, server_instance_id, num_server" << "," << myRank << "," << my_server_offset << "," << server_instance_id << "," << num_server << std::endl;
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

soma::CollectorHandle soma_plugin_init_mochi(int myRank) {

    /* Grab my server instance address and other deets */
    parse_command_line(myRank);

    // Initialize the thallium server
    engine = new thallium::engine(g_protocol, THALLIUM_CLIENT_MODE);

    // Initialize a Client
    client = new soma::Client(*engine);

    // Create a handle from provider 0
    soma::CollectorHandle collector = (*client).makeCollectorHandle(g_address, g_provider_id,
                    soma::UUID::from_string(g_collector.c_str()));

    initialized = true;
    
    // return collector handle?
    return collector;
}

