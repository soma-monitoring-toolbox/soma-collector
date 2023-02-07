/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#ifndef __SOMA_ASYNC_REQUEST_IMPL_H
#define __SOMA_ASYNC_REQUEST_IMPL_H

#include <functional>
#include <thallium.hpp>

namespace soma {

namespace tl = thallium;

struct AsyncRequestImpl {

    AsyncRequestImpl(tl::async_response&& async_response)
    : m_async_response(std::move(async_response)) {}

    tl::async_response                     m_async_response;
    bool                                   m_waited = false;
    std::function<void(AsyncRequestImpl&)> m_wait_callback;

};

}

#endif
