/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#ifndef __SOMA_ADMIN_IMPL_H
#define __SOMA_ADMIN_IMPL_H

#include <thallium.hpp>

namespace soma {

namespace tl = thallium;

class AdminImpl {

    public:

    tl::engine           m_engine;
    tl::remote_procedure m_create_collector;
    tl::remote_procedure m_open_collector;
    tl::remote_procedure m_close_collector;
    tl::remote_procedure m_destroy_collector;

    AdminImpl(const tl::engine& engine)
    : m_engine(engine)
    , m_create_collector(m_engine.define("soma_create_collector"))
    , m_open_collector(m_engine.define("soma_open_collector"))
    , m_close_collector(m_engine.define("soma_close_collector"))
    , m_destroy_collector(m_engine.define("soma_destroy_collector"))
    {}

    AdminImpl(margo_instance_id mid)
    : AdminImpl(tl::engine(mid)) {
    }

    ~AdminImpl() {}
};

}

#endif
