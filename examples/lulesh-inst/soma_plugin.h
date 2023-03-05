#ifndef __SOMA_PLUGIN_H
#define __SOMA_PLUGIN_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <assert.h>
#include <ctype.h>
#include <unistd.h>
#include <mutex>

#include <thallium.hpp>
#include <soma/Client.hpp>
#include <conduit/conduit.hpp>

//extern "C" {

static std::string read_nth_line(const std::string& filename, int n);
static void parse_command_line();

soma::CollectorHandle soma_plugin_init_mochi(int myRank);
//soma::CollectorHandle soma_plugin_init_mochi(int myRank);
//}
#endif
