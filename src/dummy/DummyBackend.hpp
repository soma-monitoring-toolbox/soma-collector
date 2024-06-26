/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#ifndef __DUMMY_BACKEND_HPP
#define __DUMMY_BACKEND_HPP

#include "soma/NamespaceHandle.hpp"
#include <soma/Backend.hpp>
#include <conduit/conduit.hpp>
#include <queue>
#include <vector>

using json = nlohmann::json;

/**
 * Dummy implementation of an soma Backend.
 */
class DummyCollector : public soma::Backend {
   
    json m_config;
    //std::vector <conduit::Node, std::vector<conduit::Node>> node_q;
    //std::queue <conduit::Node, std::deque<conduit::Node>> node_q;
    std::deque <conduit::Node> node_q;
    int last_index = 0;

    public:

    /**
     * @brief Constructor.
     */
    DummyCollector(const json& config)
    : m_config(config) {}

    /**
     * @brief Move-constructor.
     */
    DummyCollector(DummyCollector&&) = default;

    /**
     * @brief Copy-constructor.
     */
    DummyCollector(const DummyCollector&) = default;

    /**
     * @brief Move-assignment operator.
     */
    DummyCollector& operator=(DummyCollector&&) = default;

    /**
     * @brief Copy-assignment operator.
     */
    DummyCollector& operator=(const DummyCollector&) = default;

    /**
     * @brief Destructor.
     */
    virtual ~DummyCollector() = default;

    /**
     * @brief Prints Hello World.
     */
    void sayHello() override;

    /**
     * @brief Publishes a conduit node.
     */
    void soma_publish(std::string node) override;
    
    /**
     * @brief Publishes a conduit node.
     */
    soma::RequestResult<bool> soma_publish_async(std::string node, size_t pool_size, MPI_Comm comm) override;

    /**
     * @brief Performs some analysis and writes out results.
     */
    soma::RequestResult<bool> soma_analyze(std::string filename, int soma_op, size_t pool_size, MPI_Comm comm) override;
    
    /**
     * @brief Writes performance data to a file.
     */
    soma::RequestResult<bool> soma_write(std::string filename, int soma_op) override;
    
    /**
     * @brief Compute the sum of two integers.
     *
     * @param x first integer
     * @param y second integer
     *
     * @return a RequestResult containing the result.
     */
    soma::RequestResult<int32_t> computeSum(int32_t x, int32_t y) override;

    /**
     * @brief Destroys the underlying collector.
     *
     * @return a RequestResult<bool> instance indicating
     * whether the database was successfully destroyed.
     */
    soma::RequestResult<bool> destroy() override;

    /**
     * @brief Static factory function used by the CollectorFactory to
     * create a DummyCollector.
     *
     * @param engine Thallium engine
     * @param config JSON configuration for the collector
     *
     * @return a unique_ptr to a collector
     */
    static std::unique_ptr<soma::Backend> create(const thallium::engine& engine, const json& config);

    /**
     * @brief Static factory function used by the CollectorFactory to
     * open a DummyCollector.
     *
     * @param engine Thallium engine
     * @param config JSON configuration for the collector
     *
     * @return a unique_ptr to a collector
     */
    static std::unique_ptr<soma::Backend> open(const thallium::engine& engine, const json& config);
};

#endif
