/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#ifndef __SOMA_PROVIDER_IMPL_H
#define __SOMA_PROVIDER_IMPL_H

#include "soma/Backend.hpp"
#include "soma/UUID.hpp"

#include <thallium.hpp>
#include <thallium/serialization/stl/string.hpp>
#include <thallium/serialization/stl/vector.hpp>

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include <tuple>
#include <mpi.h>

#define FIND_COLLECTOR(__var__) \
        std::shared_ptr<Backend> __var__;\
        do {\
            std::lock_guard<tl::mutex> lock(m_backends_mtx);\
            auto it = m_backends.find(collector_id);\
            if(it == m_backends.end()) {\
                result.success() = false;\
                result.error() = "Collector with UUID "s + collector_id.to_string() + " not found";\
                req.respond(result);\
                spdlog::error("[provider:{}] Collector {} not found", id(), collector_id.to_string());\
                return;\
            }\
            __var__ = it->second;\
        }while(0)

namespace soma {

using namespace std::string_literals;
namespace tl = thallium;

class ProviderImpl : public tl::provider<ProviderImpl> {

    auto id() const { return get_provider_id(); } // for convenience

    using json = nlohmann::json;

    public:

    std::string          m_token;
    tl::pool             m_pool;
    MPI_Comm		 m_comm;
    // Admin RPC
    tl::remote_procedure m_create_collector;
    tl::remote_procedure m_open_collector;
    tl::remote_procedure m_close_collector;
    tl::remote_procedure m_destroy_collector;
    // Client RPC
    tl::remote_procedure m_check_collector;
    tl::remote_procedure m_say_hello;
    tl::remote_procedure m_soma_publish;
    tl::remote_procedure m_compute_sum;
    // Backends
    std::unordered_map<UUID, std::shared_ptr<Backend>> m_backends;
    tl::mutex m_backends_mtx;

    ProviderImpl(const tl::engine& engine, uint16_t provider_id, MPI_Comm comm, const tl::pool& pool)
    : tl::provider<ProviderImpl>(engine, provider_id)
    , m_pool(pool), m_comm(comm)
    , m_create_collector(define("soma_create_collector", &ProviderImpl::createCollector, pool))
    , m_open_collector(define("soma_open_collector", &ProviderImpl::openCollector, pool))
    , m_close_collector(define("soma_close_collector", &ProviderImpl::closeCollector, pool))
    , m_destroy_collector(define("soma_destroy_collector", &ProviderImpl::destroyCollector, pool))
    , m_check_collector(define("soma_check_collector", &ProviderImpl::checkCollector, pool))
    , m_say_hello(define("soma_say_hello", &ProviderImpl::sayHello, pool))
    , m_soma_publish(define("soma_publish", &ProviderImpl::soma_publish, pool))
    , m_compute_sum(define("soma_compute_sum",  &ProviderImpl::computeSum, pool))
    {
        spdlog::trace("[provider:{0}] Registered provider with id {0}", id());
    }

    ~ProviderImpl() {
        spdlog::trace("[provider:{}] Deregistering provider", id());
        m_create_collector.deregister();
        m_open_collector.deregister();
        m_close_collector.deregister();
        m_destroy_collector.deregister();
        m_check_collector.deregister();
        m_say_hello.deregister();
        m_soma_publish.deregister();
        m_compute_sum.deregister();
        spdlog::trace("[provider:{}]    => done!", id());
    }

    void createCollector(const tl::request& req,
                        const std::string& token,
                        const std::string& collector_type,
                        const std::string& collector_config) {

        spdlog::trace("[provider:{}] Received createCollector request", id());
        spdlog::trace("[provider:{}]    => type = {}", id(), collector_type);
        spdlog::trace("[provider:{}]    => config = {}", id(), collector_config);

        auto collector_id = UUID::generate();
        RequestResult<UUID> result;

        if(m_token.size() > 0 && m_token != token) {
            result.success() = false;
            result.error() = "Invalid security token";
            req.respond(result);
            spdlog::error("[provider:{}] Invalid security token {}", id(), token);
            return;
        }

        json json_config;
        try {
            json_config = json::parse(collector_config);
        } catch(json::parse_error& e) {
            result.error() = e.what();
            result.success() = false;
            spdlog::error("[provider:{}] Could not parse collector configuration for collector {}",
                    id(), collector_id.to_string());
            req.respond(result);
            return;
        }

        std::unique_ptr<Backend> backend;
        try {
            backend = CollectorFactory::createCollector(collector_type, get_engine(), json_config);
        } catch(const std::exception& ex) {
            result.success() = false;
            result.error() = ex.what();
            spdlog::error("[provider:{}] Error when creating collector {} of type {}:",
                    id(), collector_id.to_string(), collector_type);
            spdlog::error("[provider:{}]    => {}", id(), result.error());
            req.respond(result);
            return;
        }

        if(not backend) {
            result.success() = false;
            result.error() = "Unknown collector type "s + collector_type;
            spdlog::error("[provider:{}] Unknown collector type {} for collector {}",
                    id(), collector_type, collector_id.to_string());
            req.respond(result);
            return;
        } else {
            std::lock_guard<tl::mutex> lock(m_backends_mtx);
            m_backends[collector_id] = std::move(backend);
            result.value() = collector_id;
        }
        
        req.respond(result);
        spdlog::trace("[provider:{}] Successfully created collector {} of type {}",
                id(), collector_id.to_string(), collector_type);
    }

    void openCollector(const tl::request& req,
                      const std::string& token,
                      const std::string& collector_type,
                      const std::string& collector_config) {

        spdlog::trace("[provider:{}] Received openCollector request", id());
        spdlog::trace("[provider:{}]    => type = {}", id(), collector_type);
        spdlog::trace("[provider:{}]    => config = {}", id(), collector_config);

        auto collector_id = UUID::generate();
        RequestResult<UUID> result;

        if(m_token.size() > 0 && m_token != token) {
            result.success() = false;
            result.error() = "Invalid security token";
            req.respond(result);
            spdlog::error("[provider:{}] Invalid security token {}", id(), token);
            return;
        }

        json json_config;
        try {
            json_config = json::parse(collector_config);
        } catch(json::parse_error& e) {
            result.error() = e.what();
            result.success() = false;
            spdlog::error("[provider:{}] Could not parse collector configuration for collector {}",
                    id(), collector_id.to_string());
            req.respond(result);
            return;
        }

        std::unique_ptr<Backend> backend;
        try {
            backend = CollectorFactory::openCollector(collector_type, get_engine(), json_config);
        } catch(const std::exception& ex) {
            result.success() = false;
            result.error() = ex.what();
            spdlog::error("[provider:{}] Error when opening collector {} of type {}:",
                    id(), collector_id.to_string(), collector_type);
            spdlog::error("[provider:{}]    => {}", id(), result.error());
            req.respond(result);
            return;
        }

        if(not backend) {
            result.success() = false;
            result.error() = "Unknown collector type "s + collector_type;
            spdlog::error("[provider:{}] Unknown collector type {} for collector {}",
                    id(), collector_type, collector_id.to_string());
            req.respond(result);
            return;
        } else {
            std::lock_guard<tl::mutex> lock(m_backends_mtx);
            m_backends[collector_id] = std::move(backend);
            result.value() = collector_id;
        }
        
        req.respond(result);
        spdlog::trace("[provider:{}] Successfully created collector {} of type {}",
                id(), collector_id.to_string(), collector_type);
    }

    void closeCollector(const tl::request& req,
                        const std::string& token,
                        const UUID& collector_id) {
        spdlog::trace("[provider:{}] Received closeCollector request for collector {}",
                id(), collector_id.to_string());

        RequestResult<bool> result;

        if(m_token.size() > 0 && m_token != token) {
            result.success() = false;
            result.error() = "Invalid security token";
            req.respond(result);
            spdlog::error("[provider:{}] Invalid security token {}", id(), token);
            return;
        }

        {
            std::lock_guard<tl::mutex> lock(m_backends_mtx);

            if(m_backends.count(collector_id) == 0) {
                result.success() = false;
                result.error() = "Collector "s + collector_id.to_string() + " not found";
                req.respond(result);
                spdlog::error("[provider:{}] Collector {} not found", id(), collector_id.to_string());
                return;
            }

            m_backends.erase(collector_id);
        }
        req.respond(result);
        spdlog::trace("[provider:{}] Collector {} successfully closed", id(), collector_id.to_string());
    }
    
    void destroyCollector(const tl::request& req,
                         const std::string& token,
                         const UUID& collector_id) {
        RequestResult<bool> result;
        spdlog::trace("[provider:{}] Received destroyCollector request for collector {}", id(), collector_id.to_string());

        if(m_token.size() > 0 && m_token != token) {
            result.success() = false;
            result.error() = "Invalid security token";
            req.respond(result);
            spdlog::error("[provider:{}] Invalid security token {}", id(), token);
            return;
        }

        {
            std::lock_guard<tl::mutex> lock(m_backends_mtx);

            if(m_backends.count(collector_id) == 0) {
                result.success() = false;
                result.error() = "Collector "s + collector_id.to_string() + " not found";
                req.respond(result);
                spdlog::error("[provider:{}] Collector {} not found", id(), collector_id.to_string());
                return;
            }

            result = m_backends[collector_id]->destroy();
            m_backends.erase(collector_id);
        }

        req.respond(result);
        spdlog::trace("[provider:{}] Collector {} successfully destroyed", id(), collector_id.to_string());
    }

    void checkCollector(const tl::request& req,
                       const UUID& collector_id) {
        spdlog::trace("[provider:{}] Received checkCollector request for collector {}", id(), collector_id.to_string());
        RequestResult<bool> result;
        FIND_COLLECTOR(collector);
        result.success() = true;
        req.respond(result);
        spdlog::trace("[provider:{}] Code successfully executed on collector {}", id(), collector_id.to_string());
    }

    void sayHello(const tl::request& req,
                  const UUID& collector_id) {
        spdlog::trace("[provider:{}] Received sayHello request for collector {}", id(), collector_id.to_string());
        RequestResult<bool> result;
        FIND_COLLECTOR(collector);
        collector->sayHello();
        spdlog::trace("[provider:{}] Successfully executed sayHello on collector {}", id(), collector_id.to_string());
    }

    // Soma Publish API call
    void soma_publish(const tl::request& req,
                     const UUID& collector_id,
                     std::string node) {
        spdlog::trace("[provider:{}] Received soma_publish for collector {}", id(), collector_id.to_string());
        RequestResult<bool> result;
        FIND_COLLECTOR(collector);
        result = collector->soma_publish(node);
        req.respond(result);
        spdlog::trace("[provider:{}] Successfully executed soma_publish on collector {}", id(), collector_id.to_string());
    }

    void computeSum(const tl::request& req,
                    const UUID& collector_id,
                    int32_t x, int32_t y) {
        spdlog::trace("[provider:{}] Received sayHello request for collector {}", id(), collector_id.to_string());
        RequestResult<int32_t> result;
        FIND_COLLECTOR(collector);
        result = collector->computeSum(x, y);
        req.respond(result);
        spdlog::trace("[provider:{}] Successfully executed computeSum on collector {}", id(), collector_id.to_string());
    }

};

}

#endif
