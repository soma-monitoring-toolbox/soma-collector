/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#ifndef __SOMA_COLLECTOR_HANDLE_HPP
#define __SOMA_COLLECTOR_HANDLE_HPP

#include <experimental/optional>
#include <thallium.hpp>
#include <memory>
#include <unordered_set>
#include <soma/Client.hpp>
#include <soma/NamespaceHandle.hpp>
#include <soma/Exception.hpp>
#include <soma/AsyncRequest.hpp>

#include <conduit/conduit.hpp>

namespace soma {

namespace tl = thallium;

class Client;
class CollectorHandleImpl;

/**
 * @brief A CollectorHandle object is a handle for a remote collector
 * on a server. It enables invoking the collector's functionalities.
 */
class CollectorHandle {

    friend class Client;

    public:

    /**
     * @brief Constructor. The resulting CollectorHandle handle will be invalid.
     */
    CollectorHandle();

    /**
     * @brief Copy-constructor.
     */
    CollectorHandle(const CollectorHandle&);

    /**
     * @brief Move-constructor.
     */
    CollectorHandle(CollectorHandle&&);

    /**
     * @brief Copy-assignment operator.
     */
    CollectorHandle& operator=(const CollectorHandle&);

    /**
     * @brief Move-assignment operator.
     */
    CollectorHandle& operator=(CollectorHandle&&);

    /**
     * @brief Destructor.
     */
    ~CollectorHandle();

    /**
     * @brief Returns the client this database has been opened with.
     */
    Client client() const;


    /**
     * @brief Checks if the CollectorHandle instance is valid.
     */
    operator bool() const;

    /**
     * @brief Sends an RPC to the collector to make it print a hello message.
     */
    void sayHello() const;

    /**
     * @brief Requests the publishing of conduit Node
     *
     * @param[in] node conduit::Node
     */
    void soma_publish(conduit::Node node) const;
    
    /**
     * @brief Asynchronously requests the publishing of conduit Node
     *
     * @param[in] node conduit::Node
     */
    thallium::async_response soma_publish_async(conduit::Node node) const;

    /**
     * @brief Creates a SOMA monitoring namespace and returns a namespace handle
     *
     * @param[in] namespace_name std::string
     */
    NamespaceHandle* soma_create_namespace(std::string namespace_name) const;

    /**
     * @brief Publishes a namespace after committing it. Also resets frequency_counter to publish_frequency
     *
     * @param[in] ns_handle NamespaceHandle
     */
    void soma_publish_namespace(NamespaceHandle *ns_handle) const;

    /**
     * @brief Commits a namespace
     *
     * @param[in] ns_handle NamespaceHandle
     */
    void soma_commit_namespace(NamespaceHandle *ns_handle) const;

    /**
     * @brief Asynchronously commits a namespace
     *
     * @param[in] ns_handle NamespaceHandle
     */
    std::experimental::optional<thallium::async_response> soma_commit_namespace_async(NamespaceHandle *ns_handle) const;
    //void soma_commit_namespace_async(NamespaceHandle *ns_handle, AsyncRequest *req) const;
    
    /**
     * @brief Sets a publish_frequency. Also resets frequency_counter to publish_frequency
     *
     * @param[in] ns_handle NamespaceHandle
     */
    void soma_set_publish_frequency(NamespaceHandle *ns_handle, int publish_frequency) const;

    /**
     * @brief Update a namespace handle with new data.
     *
     * @param[in] ns_handle NamespaceHandle
     * @param[in] uid Unique id string to be appended after the namespace, before the key
     * @param[in] key key, representing the "level" in the Conduit Node
     * @param[in] value double value (we should also support string, int in the future)
     * @param[in] op operation type (OVERWRITE, APPEND)
     */
    void soma_update_namespace(NamespaceHandle *ns_handle, std::string uid, std::string key, double value, int soma_op) const;

    /**
     * @brief Requests the data gets written to file 
     *
     * @param[in] node conduit::Node
     */
    void soma_write(std::string filename, bool* complete) const;

    /**
     * @brief Requests the target collector to compute the sum of two numbers.
     * If result is null, it will be ignored. If req is not null, this call
     * will be non-blocking and the caller is responsible for waiting on
     * the request.
     *
     * @param[in] x first integer
     * @param[in] y second integer
     * @param[out] result result
     * @param[out] req request for a non-blocking operation
     */
    void computeSum(int32_t x, int32_t y,
                    int32_t* result = nullptr,
                    AsyncRequest* req = nullptr) const;

    private:

    /**
     * @brief Constructor is private. Use a Client object
     * to create a CollectorHandle instance.
     *
     * @param impl Pointer to implementation.
     */
    CollectorHandle(const std::shared_ptr<CollectorHandleImpl>& impl);

    std::shared_ptr<CollectorHandleImpl> self;
};

}

#endif
