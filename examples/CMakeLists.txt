add_executable (example-server ${CMAKE_CURRENT_SOURCE_DIR}/server.cpp)
target_link_libraries(example-server
PRIVATE
    soma-server
    soma-admin
    conduit::conduit
    TCLAP::TCLAP
    MPI::MPI_CXX
)

add_executable (example-admin ${CMAKE_CURRENT_SOURCE_DIR}/admin.cpp)
target_link_libraries(example-admin
PRIVATE
    soma-admin
    spdlog::spdlog_header_only
    TCLAP::TCLAP
)

add_executable (example-client ${CMAKE_CURRENT_SOURCE_DIR}/client.cpp)
target_link_libraries (example-client
PRIVATE
    soma-client
    conduit::conduit
    TCLAP::TCLAP
    MPI::MPI_CXX
)

add_executable (proc-monitor ${CMAKE_CURRENT_SOURCE_DIR}/proc_monitor.cpp)
target_link_libraries (proc-monitor
PRIVATE
    soma-client
    conduit::conduit
    TCLAP::TCLAP
    MPI::MPI_CXX
)

add_executable (rp-monitor ${CMAKE_CURRENT_SOURCE_DIR}/rp_monitor.cpp)
target_link_libraries (rp-monitor
PRIVATE
    soma-client
    conduit::conduit
    TCLAP::TCLAP
    MPI::MPI_CXX
)

#add_subdirectory(lulesh-inst)

