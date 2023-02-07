/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#ifndef __SOMA_COLLECTOR_HANDLE_IMPL_H
#define __SOMA_COLLECTOR_HANDLE_IMPL_H

#include <soma/UUID.hpp>

namespace soma {

class CollectorHandleImpl {

    public:

    UUID                        m_collector_id;
    std::shared_ptr<ClientImpl> m_client;
    tl::provider_handle         m_ph;

    CollectorHandleImpl() = default;
    
    CollectorHandleImpl(const std::shared_ptr<ClientImpl>& client, 
                       tl::provider_handle&& ph,
                       const UUID& collector_id)
    : m_collector_id(collector_id)
    , m_client(client)
    , m_ph(std::move(ph)) {}
};

}

#endif
