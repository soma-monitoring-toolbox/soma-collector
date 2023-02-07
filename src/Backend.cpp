/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#include "soma/Backend.hpp"

namespace tl = thallium;

namespace soma {

using json = nlohmann::json;

std::unordered_map<std::string,
                std::function<std::unique_ptr<Backend>(const tl::engine&, const json&)>> CollectorFactory::create_fn;

std::unordered_map<std::string,
                std::function<std::unique_ptr<Backend>(const tl::engine&, const json&)>> CollectorFactory::open_fn;

std::unique_ptr<Backend> CollectorFactory::createCollector(const std::string& backend_name,
                                                         const tl::engine& engine,
                                                         const json& config) {
    auto it = create_fn.find(backend_name);
    if(it == create_fn.end()) return nullptr;
    auto& f = it->second;
    return f(engine, config);
}

std::unique_ptr<Backend> CollectorFactory::openCollector(const std::string& backend_name,
                                                       const tl::engine& engine,
                                                       const json& config) {
    auto it = open_fn.find(backend_name);
    if(it == open_fn.end()) return nullptr;
    auto& f = it->second;
    return f(engine, config);
}

}
