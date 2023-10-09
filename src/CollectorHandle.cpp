/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#include "soma/CollectorHandle.hpp"
#include "soma/RequestResult.hpp"
#include "soma/NamespaceHandle.hpp"
#include "soma/Exception.hpp"

#include "AsyncRequestImpl.hpp"
#include "ClientImpl.hpp"
#include "CollectorHandleImpl.hpp"

#include <thallium/serialization/stl/string.hpp>
#include <thallium/serialization/stl/pair.hpp>

#include <conduit/conduit.hpp>

namespace soma {

CollectorHandle::CollectorHandle() = default;

CollectorHandle::CollectorHandle(const std::shared_ptr<CollectorHandleImpl>& impl)
: self(impl) {}

CollectorHandle::CollectorHandle(const CollectorHandle&) = default;

CollectorHandle::CollectorHandle(CollectorHandle&&) = default;

CollectorHandle& CollectorHandle::operator=(const CollectorHandle&) = default;

CollectorHandle& CollectorHandle::operator=(CollectorHandle&&) = default;

CollectorHandle::~CollectorHandle() = default;

CollectorHandle::operator bool() const {
    return static_cast<bool>(self);
}

Client CollectorHandle::client() const {
    return Client(self->m_client);
}

void CollectorHandle::sayHello() const {
    if(not self) throw Exception("Invalid soma::CollectorHandle object");
    auto& rpc = self->m_client->m_say_hello;
    auto& ph  = self->m_ph;
    auto& collector_id = self->m_collector_id;
    rpc.on(ph)(collector_id);
}

// Soma Publish Synchronous API call
void CollectorHandle::soma_publish(conduit::Node node) const {
    if(not self) throw Exception("Invalid soma::CollectorHandle object");
    auto& rpc = self->m_client->m_soma_publish;
    auto& ph  = self->m_ph;
    auto& collector_id = self->m_collector_id;
    RequestResult<bool> result = rpc.on(ph)(collector_id, node.to_string("conduit_base64_json"));
    if(not result.success()) {
        throw Exception(result.error());
    }
}

// Asynchronous publish API call
thallium::async_response CollectorHandle::soma_publish_async(conduit::Node node) const {
    if(not self) throw Exception("Invalid soma::CollectorHandle object");
    auto& rpc = self->m_client->m_soma_publish_async;
    auto& ph  = self->m_ph;
    auto& collector_id = self->m_collector_id;
    auto response = rpc.on(ph).async(collector_id, node.to_string("conduit_base64_json"));
    return response;
}


NamespaceHandle* CollectorHandle::soma_create_namespace(std::string namespace_name) const {
    if(not self) throw Exception("Invalid soma::CollectorHandle object");
    return new NamespaceHandle(namespace_name);
}

void CollectorHandle::soma_publish_namespace(NamespaceHandle *ns_handle) const {
    if(not self) throw Exception("Invalid soma::CollectorHandle object");
    (*ns_handle).get_is_uncommitted() = false;
    (*ns_handle).get_frequency_counter() = (*ns_handle).get_publish_frequency();
    soma_publish((*ns_handle).get_raw_node());
}

// Blocking commit namespace, calls blocking publish at appropriate frequency
void CollectorHandle::soma_commit_namespace(NamespaceHandle *ns_handle) const {
    if(not self) throw Exception("Invalid soma::CollectorHandle object");
    (*ns_handle).get_is_uncommitted() = false;
    (*ns_handle).get_frequency_counter() -= 1;
    /* Publish the node if the frequency_counter reaches 0 */
    if((*ns_handle).get_frequency_counter() == 0) {
	soma_publish_namespace(ns_handle);
    	// reset the frequency counter
	(*ns_handle).reset_frequency_counter();
    };
}

// Asynchronous commit namespace, call async publish at appropriate frequency
std::experimental::optional<thallium::async_response> CollectorHandle::soma_commit_namespace_async(NamespaceHandle *ns_handle) const {
    if(not self) throw Exception("Invalid soma::CollectorHandle object");
    (*ns_handle).get_is_uncommitted() = false;
    (*ns_handle).get_frequency_counter() -= 1;
    // Publish the node if the frequency_counter reaches 0 
    if((*ns_handle).get_frequency_counter() == 0) {
	auto response = soma_publish_async((*ns_handle).get_raw_node());
    	// reset the frequency counter
	(*ns_handle).reset_frequency_counter();
	return response;
    }
    return {};
}

void CollectorHandle::soma_set_publish_frequency(NamespaceHandle *ns_handle, int freq) const {
    if(not self) throw Exception("Invalid soma::CollectorHandle object");
    (*ns_handle).get_publish_frequency() = freq;
    (*ns_handle).get_frequency_counter() = (*ns_handle).get_publish_frequency();
}

// Overloaded function, this one takes a single double value when updating the Conduit Node
void CollectorHandle::soma_update_namespace(NamespaceHandle *ns_handle, std::string uid, std::string key, double value, int soma_op) const {
    if(not self) throw Exception("Invalid soma::CollectorHandle object");
    (*ns_handle).get_is_uncommitted() = true;

    std::string conduit_key = (*ns_handle).get_namespace_name() + "/" + uid + "/" + key;
    if(soma_op == soma::OVERWRITE) {
        (*ns_handle).update_node(conduit_key, value);
    }
}

// Overloaded function, this one takes a single string value when updating the Conduit Node
void CollectorHandle::soma_update_namespace(NamespaceHandle *ns_handle, std::string uid, std::string key, std::string value, int soma_op) const {
    if(not self) throw Exception("Invalid soma::CollectorHandle object");
    (*ns_handle).get_is_uncommitted() = true;

    std::string conduit_key = (*ns_handle).get_namespace_name() + "/" + uid + "/" + key;
    if(soma_op == soma::OVERWRITE) {
        (*ns_handle).update_node(conduit_key, value);
    }
}

// Overloaded function, this one takes a list and appends a list of values to a Conduit Node
void CollectorHandle::soma_update_namespace(NamespaceHandle *ns_handle, std::string uid, std::string key, std::vector<double> values, int soma_op) const {
    if(not self) throw Exception("Invalid soma::CollectorHandle object");
    (*ns_handle).get_is_uncommitted() = true;
    
    std::string conduit_key = (*ns_handle).get_namespace_name() + "/" + uid + "/" + key;
    if(soma_op == soma::OVERWRITE) {
        (*ns_handle).update_node(conduit_key, values);
    }
}

// Soma write API call - writes data to file
void CollectorHandle::soma_write(std::string filename, bool* complete, int soma_op) const {
    if (not self) throw Exception("Invalid soma::CollectorHandle object");
    auto& rpc = self->m_client->m_soma_write;
    auto& ph = self->m_ph;
    auto& collector_id = self->m_collector_id;
    RequestResult<bool> result = rpc.on(ph)(collector_id, filename, soma_op);
    if (result.success()) {
	*complete = result.value();
    }
    if (not result.success()) {
        throw Exception(result.error());
    }
}

void CollectorHandle::computeSum(
        int32_t x, int32_t y,
        int32_t* result,
        AsyncRequest* req) const
{
    if(not self) throw Exception("Invalid soma::CollectorHandle object");
    auto& rpc = self->m_client->m_compute_sum;
    auto& ph  = self->m_ph;
    auto& collector_id = self->m_collector_id;
    if(req == nullptr) { // synchronous call
        RequestResult<int32_t> response = rpc.on(ph)(collector_id, x, y);
        if(response.success()) {
            if(result) *result = response.value();
        } else {
            throw Exception(response.error());
        }
    } else { // asynchronous call
        auto async_response = rpc.on(ph).async(collector_id, x, y);
        auto async_request_impl =
            std::make_shared<AsyncRequestImpl>(std::move(async_response));
        async_request_impl->m_wait_callback =
            [result](AsyncRequestImpl& async_request_impl) {
                RequestResult<int32_t> response =
                    async_request_impl.m_async_response.wait();
                    if(response.success()) {
                        if(result) *result = response.value();
                    } else {
                        throw Exception(response.error());
                    }
            };
        *req = AsyncRequest(std::move(async_request_impl));
    }
}

}
