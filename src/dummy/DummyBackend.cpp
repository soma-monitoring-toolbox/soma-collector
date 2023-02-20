/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#include "DummyBackend.hpp"
#include <iostream>

SOMA_REGISTER_BACKEND(dummy, DummyCollector);

void DummyCollector::sayHello() {
    std::cout << "Hello World" << std::endl;
}

soma::RequestResult<bool> DummyCollector::soma_publish(std::string node) {
    conduit::Node n;
    n.parse(node,"conduit_json");

    std::cout << "Soma Publish" << std::endl;
    std::cout << node << std::endl;

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
