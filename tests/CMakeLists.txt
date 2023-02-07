include_directories(../include)

add_library(alpha-test Main.cpp)
target_link_libraries(alpha-test PkgConfig::cppunit alpha-server alpha-admin alpha-client)

add_executable(AdminTest AdminTest.cpp)
target_link_libraries(AdminTest alpha-test)

add_executable(ClientTest AdminTest.cpp)
target_link_libraries(ClientTest alpha-test)

add_executable(ResourceTest ResourceTest.cpp)
target_link_libraries(ResourceTest alpha-test)

add_test(NAME AdminTest COMMAND ./AdminTest AdminTest.xml)
add_test(NAME ClientTest COMMAND ./ClientTest ClientTest.xml)
add_test(NAME ResourceTest COMMAND ./ResourceTest ResourceTest.xml)
