# set source files
set (server-src-files
     Provider.cpp
     Backend.cpp)

set (client-src-files
     Client.cpp
     CollectorHandle.cpp
     AsyncRequest.cpp)

set (admin-src-files
     Admin.cpp)

set (dummy-src-files
     dummy/DummyBackend.cpp)

set (module-src-files
     BedrockModule.cpp)

# load package helper for generating cmake CONFIG packages
include (CMakePackageConfigHelpers)

# where to install files for "find_package"
set (soma-pkg "share/cmake/soma")

# set version fo shared library
set (soma-vers "${SOMA_VERSION_MAJOR}.${SOMA_VERSION_MINOR}")

# server library
add_library (soma-server ${server-src-files} ${dummy-src-files})
target_link_libraries (soma-server
    thallium
    PkgConfig::ABTIO
    PkgConfig::UUID
    nlohmann_json::nlohmann_json
    spdlog::spdlog)
target_include_directories (soma-server PUBLIC $<INSTALL_INTERFACE:include>)
target_include_directories (soma-server BEFORE PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>)
target_include_directories (soma-server BEFORE PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)
set_target_properties (soma-server
    PROPERTIES VERSION ${SOMA_VERSION}
    SOVERSION ${SOMA_VERSION_MAJOR})

# client library
add_library (soma-client ${client-src-files})
target_link_libraries (soma-client thallium PkgConfig::UUID spdlog::spdlog)
target_include_directories (soma-client PUBLIC $<INSTALL_INTERFACE:include>)
target_include_directories (soma-client BEFORE PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>)
target_include_directories (soma-client BEFORE PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)
set_target_properties (soma-client
    PROPERTIES VERSION ${SOMA_VERSION}
    SOVERSION ${SOMA_VERSION_MAJOR})

# admin library
add_library (soma-admin ${admin-src-files})
target_link_libraries (soma-admin thallium PkgConfig::UUID nlohmann_json::nlohmann_json spdlog::spdlog)
target_include_directories (soma-admin PUBLIC $<INSTALL_INTERFACE:include>)
target_include_directories (soma-admin BEFORE PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>)
target_include_directories (soma-admin BEFORE PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)
set_target_properties (soma-admin
    PROPERTIES VERSION ${SOMA_VERSION}
    SOVERSION ${SOMA_VERSION_MAJOR})

if (${ENABLE_BEDROCK})
# bedrock module library
add_library (soma-bedrock-module ${module-src-files})
target_link_libraries (soma-bedrock-module soma-server soma-admin soma-client bedrock-server)
target_include_directories (soma-bedrock-module PUBLIC $<INSTALL_INTERFACE:include>)
target_include_directories (soma-bedrock-module BEFORE PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>)
target_include_directories (soma-bedrock-module BEFORE PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)
set_target_properties (soma-bedrock-module
    PROPERTIES VERSION ${SOMA_VERSION}
    SOVERSION ${SOMA_VERSION_MAJOR})
endif ()

# installation stuff (packaging and install commands)
write_basic_package_version_file(
    "soma-config-version.cmake"
    VERSION ${SOMA_VERSION}
    COMPATIBILITY AnyNewerVersion)

# generate our config file for find_package()
set(INCLUDE_INSTALL_DIR include/)
set(LIB_INSTALL_DIR lib/)
configure_package_config_file(soma-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/soma-config.cmake
  INSTALL_DESTINATION ${LIB_INSTALL_DIR}/soma/cmake
  PATH_VARS INCLUDE_INSTALL_DIR)

# some bits for the pkg-config file
set (DEST_DIR "${CMAKE_INSTALL_PREFIX}")
set (SERVER_PRIVATE_LIBS "-lsoma-server")
set (CLIENT_PRIVATE_LIBS "-lsoma-client")
set (ADMIN_PRIVATE_LIBS  "-lsoma-admin")
configure_file ("soma-server.pc.in" "soma-server.pc" @ONLY)
configure_file ("soma-client.pc.in" "soma-client.pc" @ONLY)
configure_file ("soma-admin.pc.in"  "soma-admin.pc"  @ONLY)

# configure config.h
configure_file ("config.h.in" "config.h" @ONLY) 

# "make install" rules
install (TARGETS soma-admin soma-server soma-client
         EXPORT soma-targets
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib)
if (${ENABLE_BEDROCK})
    install (TARGETS soma-bedrock-module
             ARCHIVE DESTINATION lib
             LIBRARY DESTINATION lib)
endif ()
install (EXPORT soma-targets
         DESTINATION ${soma-pkg}
         FILE "soma-targets.cmake")
install (FILES "${CMAKE_CURRENT_BINARY_DIR}/soma-config.cmake"
               "${CMAKE_CURRENT_BINARY_DIR}/soma-config-version.cmake"
         DESTINATION ${soma-pkg} )
install (DIRECTORY ../include/soma
         DESTINATION include
         FILES_MATCHING PATTERN "*.hpp")
install (FILES "${CMAKE_CURRENT_BINARY_DIR}/soma-server.pc"
               "${CMAKE_CURRENT_BINARY_DIR}/soma-client.pc"
               "${CMAKE_CURRENT_BINARY_DIR}/soma-admin.pc"
         DESTINATION "lib/pkgconfig/")
