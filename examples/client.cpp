/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#include <soma/Client.hpp>
#include <spdlog/spdlog.h>
#include <tclap/CmdLine.h>
#include <iostream>

#include <conduit.hpp>

namespace tl = thallium;
using namespace conduit;

static std::string g_address;
static std::string g_protocol;
static std::string g_collector;
static unsigned    g_provider_id;
static std::string g_log_level = "info";

static void parse_command_line(int argc, char** argv);

int main(int argc, char** argv) {
    parse_command_line(argc, argv);
    spdlog::set_level(spdlog::level::from_str(g_log_level));

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
        collector.ams_publish(n);

    } catch(const soma::Exception& ex) {
        std::cerr << ex.what() << std::endl;
        exit(-1);
    }

    return 0;
}

void parse_command_line(int argc, char** argv) {
    try {
        TCLAP::CmdLine cmd("Soma client", ' ', "0.1");
        TCLAP::ValueArg<std::string> addressArg("a","address","Address or server", true,"","string");
        TCLAP::ValueArg<unsigned>    providerArg("p", "provider", "Provider id to contact (default 0)", false, 0, "int");
        TCLAP::ValueArg<std::string> collectorArg("r","collector","Collector id", true, soma::UUID().to_string(),"string");
        TCLAP::ValueArg<std::string> logLevel("v","verbose", "Log level (trace, debug, info, warning, error, critical, off)", false, "info", "string");
        cmd.add(addressArg);
        cmd.add(providerArg);
        cmd.add(collectorArg);
        cmd.add(logLevel);
        cmd.parse(argc, argv);
        g_address = addressArg.getValue();
        g_provider_id = providerArg.getValue();
        g_collector = collectorArg.getValue();
        g_log_level = logLevel.getValue();
        g_protocol = g_address.substr(0, g_address.find(":"));
    } catch(TCLAP::ArgException &e) {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
        exit(-1);
    }
}
