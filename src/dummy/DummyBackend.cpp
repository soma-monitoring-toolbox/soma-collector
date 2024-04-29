/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#include "DummyBackend.hpp"
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>

SOMA_REGISTER_BACKEND(dummy, DummyCollector);

void DummyCollector::sayHello() {
    std::cout << "Hello World" << std::endl;
}

void DummyCollector::soma_publish(std::string node) {
    //Renodify the conduit serialization
    conduit::Node n;
    n.parse(node,"conduit_base64_json");
    //Add to queue
    node_q.push_front(n);
    soma::RequestResult<bool> result;
    result.value() = true;
}

soma::RequestResult<bool> DummyCollector::soma_publish_async(std::string node, size_t pool_size, MPI_Comm comm) {
    //Renodify the conduit serialization
    conduit::Node n;
    n.parse(node,"conduit_base64_json");
    //Add to queue
    node_q.push_front(n);
    soma::RequestResult<bool> result;
    result.value() = true;
    return result;
}

soma::RequestResult<bool> DummyCollector::soma_analyze(std::string filename, int soma_op, size_t pool_size, MPI_Comm comm) {
    std::cout << "SOMA-COLLECTOR: Received request through soma_analyze" << std::endl;
    //Write out queue to file
    std::ofstream datafile;
    if (soma_op == soma::OVERWRITE) {
	    datafile.open(filename, std::ios::out);
    } else {
    	    datafile.open(filename, std::ios::out | std::ios::app);
    }
    if (node_q.size() > 0) {
	    conduit::Node n;
	    n = node_q.front();
	    double prev_total, prev_idle;
	    prev_total = prev_idle = 0;
    	    //'user', 'nice', 'system', 'idle', 'iowait', 'irq', 'softirq', 'steal', 'guest', 'guest_nice'
	    double user, nice, system, idle, iowait, irq, softirq, steal;
	    user = nice = system = idle = iowait = irq = softirq = steal = 0;
	    // calc overall CPU utilization - eventually restructure this the right way
	    conduit::NodeIterator itr = n["PROC"].children();
	    while(itr.has_next()) {
		    conduit::Node &tn = itr.next();
    		    std::string timestamp = itr.name();
		    std::string cur_cpu_vals = tn["stat"]["cpu"].to_string();
		    if ( cur_cpu_vals.front() == '"' ) {
    			cur_cpu_vals.erase( 0, 1 ); // erase the first character
    			cur_cpu_vals.erase( cur_cpu_vals.size() - 1 ); // erase the last character
		    }	
		    boost::algorithm::trim(cur_cpu_vals);
		    auto line_ss = std::istringstream(cur_cpu_vals);
                    std::string val;
                    int i = 0;
		    while( std::getline(line_ss, val, ' ') ) {
			boost::algorithm::trim(val);
			switch (i) {
				case 0:
					user = std::stod(val);
					break;
				case 1:
					nice = std::stod(val);
					break;
				case 2:
					system = std::stod(val);
					break;
				case 3:
					idle = std::stod(val);
					break;
				case 4:
					iowait = std::stod(val);
					break;
				case 5:
					irq = std::stod(val);
					break;
				case 6:
					softirq = std::stod(val);
					break;
				case 7:
					steal = std::stod(val);
					break;
				case 8:
					//guest = std::stod(val);
					break;
				case 9:
					//guest_nice = std::stod(val);
					break;
			}
			i++;
		    }
		    double cur_idle = idle + iowait;
		    double cur_total = cur_idle + user + nice + system + irq + softirq + steal;
		    
		    if (prev_total > 0) {
			double total_delta = cur_total - prev_total;
			double idle_delta = cur_idle - prev_idle;
			double percent = 100*((total_delta - idle_delta) / total_delta);
		        datafile << "Current CPU Utilization: " << percent << std::endl;
		    }
		    // assign values to previous
		    prev_total = cur_total;
		    prev_idle = cur_idle;
	    }
    }
    datafile.close();
    soma::RequestResult<bool> result;
    result.value() = true;
    return result;
}

soma::RequestResult<bool> DummyCollector::soma_write(std::string filename, int soma_op) {
    //std::cout << "SOMA-COLLECTOR: Received request through soma_write" << std::endl;
    //Write out queue to file
    std::ofstream datafile;
    if (soma_op == soma::OVERWRITE) {
	    datafile.open(filename, std::ios::out);
    } else {
    	    datafile.open(filename, std::ios::out | std::ios::app);
    }
    conduit::Node n;
    n = node_q.front();
    datafile << n.to_yaml();
    datafile.close();
    soma::RequestResult<bool> result;
    result.value() = true;
    return result;
}

soma::RequestResult<int32_t> DummyCollector::computeSum(int32_t x, int32_t y) {
    soma::RequestResult<int32_t> result;
    result.value() = x + y;
    return result;
}

soma::RequestResult<bool> DummyCollector::destroy() {
    soma::RequestResult<bool> result;
    result.value() = true;
    // or result.success() = true
    return result;
}

std::unique_ptr<soma::Backend> DummyCollector::create(const thallium::engine& engine, const json& config) {
    (void)engine;
    return std::unique_ptr<soma::Backend>(new DummyCollector(config));
}

std::unique_ptr<soma::Backend> DummyCollector::open(const thallium::engine& engine, const json& config) {
    (void)engine;
    return std::unique_ptr<soma::Backend>(new DummyCollector(config));
}
