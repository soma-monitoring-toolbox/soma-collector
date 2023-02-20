/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#ifndef __DUMMY_BACKEND_HPP
#define __DUMMY_BACKEND_HPP

#include <soma/Backend.hpp>

using json = nlohmann::json;

/**
 * Dummy implementation of an soma Backend.
 */
class DummyCollector : public soma::Backend {
   
    json m_config;

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
    soma::RequestResult<bool> soma_publish(std::string node) override;

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
