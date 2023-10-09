/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#include "DummyBackend.hpp"
#include <iostream>
#include <fstream>

SOMA_REGISTER_BACKEND(dummy, DummyCollector);

void DummyCollector::sayHello() {
    std::cout << "Hello World" << std::endl;
}

void DummyCollector::soma_publish(std::string node) {
    //Renodify the conduit serialization
    conduit::Node n;
    n.parse(node,"conduit_base64_json");
    //Add to queue
    node_q.push(n);
    soma::RequestResult<bool> result;
    result.value() = true;
}

soma::RequestResult<bool> DummyCollector::soma_publish_async(std::string node, size_t pool_size, MPI_Comm comm) {
    //Renodify the conduit serialization
    conduit::Node n;
    n.parse(node,"conduit_base64_json");
    //Add to queue
    node_q.push(n);
    soma::RequestResult<bool> result;
    result.value() = true;
    return result;
}

soma::RequestResult<bool> DummyCollector::soma_write(std::string filename, int soma_op) {
    //std::cout << "SOMA-COLLECTOR: Received request through soma_write" << std::endl;
    //Write out queue to file
    std::ofstream datafile;
    if (soma_op == soma::OVERWRITE) {
	    datafile.open(filename, std::ios::out);
    } else {
    	    datafile.open(filename, std::ios::out | std::ios::app);
    }
    while (!node_q.empty()) {
	    conduit::Node n;
	    n = node_q.front();
	    datafile << n.to_yaml();
	    node_q.pop();
    }
    datafile.close();
    soma::RequestResult<bool> result;
    result.value() = true;
    return result;
}

soma::RequestResult<int32_t> DummyCollector::computeSum(int32_t x, int32_t y) {
    soma::RequestResult<int32_t> result;
    result.value() = x + y;
    return result;
}

soma::RequestResult<bool> DummyCollector::destroy() {
    soma::RequestResult<bool> result;
    result.value() = true;
    // or result.success() = true
    return result;
}

std::unique_ptr<soma::Backend> DummyCollector::create(const thallium::engine& engine, const json& config) {
    (void)engine;
    return std::unique_ptr<soma::Backend>(new DummyCollector(config));
}

std::unique_ptr<soma::Backend> DummyCollector::open(const thallium::engine& engine, const json& config) {
    (void)engine;
    return std::unique_ptr<soma::Backend>(new DummyCollector(config));
}
