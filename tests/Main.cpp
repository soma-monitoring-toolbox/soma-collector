/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#include <fstream>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <spdlog/spdlog.h>

#include <alpha/Client.hpp>
#include <alpha/Admin.hpp>
#include <alpha/Provider.hpp>

namespace tl = thallium;

tl::engine engine;
std::string resource_type = "dummy";

int main(int argc, char** argv) {

    // Initialize logging
    spdlog::set_level(spdlog::level::trace);

    // Get the top level suite from the registry    
    CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

    // Adds the test to the list of test to run
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( suite );

    std::ofstream xmlOutFile;
    if(argc >= 2) {
        const char* xmlOutFileName = argv[1];
        xmlOutFile.open(xmlOutFileName);
        // Change the default outputter to output XML results into a file
        runner.setOutputter(new CppUnit::XmlOutputter(&runner.result(), xmlOutFile));
    } else {
        // Change the default outputter to output XML results into stderr
        runner.setOutputter(new CppUnit::XmlOutputter(&runner.result(), std::cerr));
    }
    if(argc >= 3) {
        resource_type = argv[2];
    }

    // Initialize the thallium server
    engine = tl::engine("na+sm", THALLIUM_SERVER_MODE);

    // Initialize the Sonata provider
    alpha::Provider provider(engine);

    // Run the tests.
    bool wasSucessful = runner.run();

    // Finalize the engine
    engine.finalize();

    if(argc >= 2)
       xmlOutFile.close();

    // Return error code 1 if the one of test failed.
    return wasSucessful ? 0 : 1;
}
