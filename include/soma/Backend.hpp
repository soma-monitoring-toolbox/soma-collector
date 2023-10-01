/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#ifndef __SOMA_BACKEND_HPP
#define __SOMA_BACKEND_HPP

#include <soma/RequestResult.hpp>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <nlohmann/json.hpp>
#include <thallium.hpp>
#include <mpi.h>

/**
 * @brief Helper class to register backend types into the backend factory.
 */
template<typename BackendType>
class __SomaBackendRegistration;

namespace soma {

/**
 * @brief Interface for collector backends. To build a new backend,
 * implement a class MyBackend that inherits from Backend, and put
 * SOMA_REGISTER_BACKEND(mybackend, MyBackend); in a cpp file
 * that includes your backend class' header file.
 *
 * Your backend class should also have two static functions to
 * respectively create and open a collector:
 *
 * std::unique_ptr<Backend> create(const json& config)
 * std::unique_ptr<Backend> attach(const json& config)
 */
class Backend {
    
    public:

    /**
     * @brief Constructor.
     */
    Backend() = default;

    /**
     * @brief Move-constructor.
     */
    Backend(Backend&&) = default;

    /**
     * @brief Copy-constructor.
     */
    Backend(const Backend&) = default;

    /**
     * @brief Move-assignment operator.
     */
    Backend& operator=(Backend&&) = default;

    /**
     * @brief Copy-assignment operator.
     */
    Backend& operator=(const Backend&) = default;

    /**
     * @brief Destructor.
     */
    virtual ~Backend() = default;

    /**
     * @brief Prints Hello World.
     */
    virtual void sayHello() = 0;

    /**
     * @brief Publishes a conduit node.
     */
    virtual void soma_publish(std::string node) = 0;

    /**
     * @brief Publishes a conduit node.
     */
    virtual soma::RequestResult<bool> soma_publish_async(std::string node, size_t pool_size, MPI_Comm comm) = 0;

    /**
     * @brief Writes data to file.
     */
    virtual soma::RequestResult<bool> soma_write(std::string filename) = 0;

    /**
     * @brief Compute the sum of two integers.
     *
     * @param x first integer
     * @param y second integer
     *
     * @return a RequestResult containing the result.
     */
    virtual RequestResult<int32_t> computeSum(int32_t x, int32_t y) = 0;

    /**
     * @brief Destroys the underlying collector.
     *
     * @return a RequestResult<bool> instance indicating
     * whether the database was successfully destroyed.
     */
    virtual RequestResult<bool> destroy() = 0;

};

/**
 * @brief The CollectorFactory contains functions to create
 * or open collectors.
 */
class CollectorFactory {

    template<typename BackendType>
    friend class ::__SomaBackendRegistration;

    using json = nlohmann::json;

    public:

    CollectorFactory() = delete;

    /**
     * @brief Creates a collector and returns a unique_ptr to the created instance.
     *
     * @param backend_name Name of the backend to use.
     * @param engine Thallium engine.
     * @param config Configuration object to pass to the backend's create function.
     *
     * @return a unique_ptr to the created Collector.
     */
    static std::unique_ptr<Backend> createCollector(const std::string& backend_name,
                                                   const thallium::engine& engine,
                                                   const json& config);

    /**
     * @brief Opens an existing database and returns a unique_ptr to the
     * created backend instance.
     *
     * @param backend_name Name of the backend to use.
     * @param engine Thallium engine.
     * @param config Configuration object to pass to the backend's open function.
     *
     * @return a unique_ptr to the created Backend.
     */
    static std::unique_ptr<Backend> openCollector(const std::string& backend_name,
                                                const thallium::engine& engine,
                                                const json& config);

    private:

    static std::unordered_map<std::string,
                std::function<std::unique_ptr<Backend>(const thallium::engine&, const json&)>> create_fn;
    
    static std::unordered_map<std::string,
                std::function<std::unique_ptr<Backend>(const thallium::engine&, const json&)>> open_fn;
};

} // namespace soma


#define SOMA_REGISTER_BACKEND(__backend_name, __backend_type) \
    static __SomaBackendRegistration<__backend_type> __soma ## __backend_name ## _backend( #__backend_name )

template<typename BackendType>
class __SomaBackendRegistration {

    using json = nlohmann::json;

    public:

    __SomaBackendRegistration(const std::string& backend_name)
    {
        soma::CollectorFactory::create_fn[backend_name] = [](const thallium::engine& engine, const json& config) {
            return BackendType::create(engine, config);
        };
        soma::CollectorFactory::open_fn[backend_name] = [](const thallium::engine& engine, const json& config) {
            return BackendType::open(engine, config);
        };
    }
};

#endif
