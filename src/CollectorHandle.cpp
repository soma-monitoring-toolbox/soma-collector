/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#include "soma/CollectorHandle.hpp"
#include "soma/RequestResult.hpp"
#include "soma/Exception.hpp"

#include "AsyncRequestImpl.hpp"
#include "ClientImpl.hpp"
#include "CollectorHandleImpl.hpp"

#include <thallium/serialization/stl/string.hpp>
#include <thallium/serialization/stl/pair.hpp>

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
