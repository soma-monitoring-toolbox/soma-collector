/*
 * (C) 2020 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include "soma/Exception.hpp"
#include "soma/Client.hpp"
#include "soma/CollectorHandle.hpp"
#include "soma/RequestResult.hpp"

#include "ClientImpl.hpp"
#include "CollectorHandleImpl.hpp"

#include <thallium/serialization/stl/string.hpp>

namespace tl = thallium;

namespace soma {

Client::Client() = default;

Client::Client(const tl::engine& engine)
: self(std::make_shared<ClientImpl>(engine)) {}

Client::Client(margo_instance_id mid)
: self(std::make_shared<ClientImpl>(mid)) {}

Client::Client(const std::shared_ptr<ClientImpl>& impl)
: self(impl) {}

Client::Client(Client&& other) = default;

Client& Client::operator=(Client&& other) = default;

Client::Client(const Client& other) = default;

Client& Client::operator=(const Client& other) = default;


Client::~Client() = default;

const tl::engine& Client::engine() const {
    return self->m_engine;
}

Client::operator bool() const {
    return static_cast<bool>(self);
}

CollectorHandle Client::makeCollectorHandle(
        const std::string& address,
        uint16_t provider_id,
        const UUID& collector_id,
        bool check) const {
    auto endpoint  = self->m_engine.lookup(address);
    auto ph        = tl::provider_handle(endpoint, provider_id);
    RequestResult<bool> result;
    result.success() = true;
    //std::cout << "making collector handle" << std::endl;
    if(check) {
        result = self->m_check_collector.on(ph)(collector_id);
//	std::cout << "collector handle check returned" << std::endl;
    }
    if(result.success()) {
//	std::cout << "collector impl" << std::endl;
        auto collector_impl = std::make_shared<CollectorHandleImpl>(self, std::move(ph), collector_id);
	return CollectorHandle(collector_impl);
    } else {
        throw Exception(result.error());
        return CollectorHandle(nullptr);
    }
}

std::string Client::getConfig() const {
    return "{}";
}

}
