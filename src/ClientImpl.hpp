/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#ifndef __SOMA_CLIENT_IMPL_H
#define __SOMA_CLIENT_IMPL_H

#include <thallium.hpp>
#include <thallium/serialization/stl/unordered_set.hpp>
#include <thallium/serialization/stl/unordered_map.hpp>
#include <thallium/serialization/stl/string.hpp>

namespace soma {

namespace tl = thallium;

class ClientImpl {

    public:

    tl::engine           m_engine;
    tl::remote_procedure m_check_collector;
    tl::remote_procedure m_say_hello;
    tl::remote_procedure m_compute_sum;

    // SOMA API Calls
    tl::remote_procedure m_soma_publish;
    tl::remote_procedure m_soma_publish_async;
    tl::remote_procedure m_soma_analyze;
    tl::remote_procedure m_soma_write;

    ClientImpl(const tl::engine& engine)
    : m_engine(engine)
    , m_check_collector(m_engine.define("soma_check_collector"))
    , m_say_hello(m_engine.define("soma_say_hello").disable_response())
    , m_compute_sum(m_engine.define("soma_compute_sum"))
    , m_soma_publish(m_engine.define("soma_publish"))
    , m_soma_publish_async(m_engine.define("soma_publish_async"))
    , m_soma_analyze(m_engine.define("soma_analyze"))
    , m_soma_write(m_engine.define("soma_write"))
    {}

    ClientImpl(margo_instance_id mid)
    : ClientImpl(tl::engine(mid)) {}

    ~ClientImpl() {}
};

}

#endif
