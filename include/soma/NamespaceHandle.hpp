/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#ifndef __SOMA_NAMESPACE_HANDLE_HPP
#define __SOMA_NAMESPACE_HANDLE_HPP

#include <string>
#include <conduit/conduit.hpp>

namespace soma {

/**
 * @brief The NamespaceHandle object is an opaque object used to create
 * and manage a SOMA monitoring namespace.
 * It contains the following fields:
 * - namespace_name that contains the namespace name
 * - dirty_bit that specifies if a namespace is "uncommitted" or "open"
 * - publish_frequency specifies how often a publish RPC is generated as a result
 *   of a commit operation
 * - frequency_counter that is decremented everytime a commit operation is invoked
 * - conduit_node representing the raw conduit::Node 
 *
 */

enum SOMA_OP {OVERWRITE, APPEND};

class NamespaceHandle {
    
    public:

    NamespaceHandle() = default;
    ~NamespaceHandle() = default;
    NamespaceHandle(std::string namespace_name) {
	    m_namespace_name = namespace_name;
	    m_node[namespace_name.c_str()] = "namespace";
    }

    std::string& get_namespace_name() {
        return m_namespace_name;
    }

    int& get_frequency_counter() {
        return m_frequency_counter;
    }

    void reset_frequency_counter() {
	m_frequency_counter = m_publish_frequency;
    }

    int& get_publish_frequency() {
        return m_publish_frequency;
    }

    bool& get_is_uncommitted() {
        return m_dirty_bit;
    }

    conduit::Node get_raw_node() {
	return m_node;
    }

    void update_node(std::string key, double value) {
	m_node[key.c_str()] = value;
    }

    void update_node(std::string key, std::string value) {
	m_node[key.c_str()] = value;
    }

    void update_node(std::string key, std::vector<double> values) {
	for (int i = 0; i < values.size(); i++) {
		conduit::Node &list_entry = m_node[key.c_str()].append();
    		list_entry.set(values[i]);
	}
    }
/*    
    void append_node(std::string key, double value) {
	m_node[key.c_str()] = value;
    }
*/
    private:

    bool        m_dirty_bit = false;
    std::string m_namespace_name = "soma_namespace";
    conduit::Node m_node;
    int 	m_publish_frequency = 1;
    int		m_frequency_counter = 1;
};

}

#endif
