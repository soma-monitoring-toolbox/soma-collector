include_directories(../include)

add_library(soma-test Main.cpp)
target_link_libraries(soma-test PkgConfig::cppunit soma-server soma-admin soma-client)

add_executable(AdminTest AdminTest.cpp)
target_link_libraries(AdminTest soma-test)

add_executable(ClientTest AdminTest.cpp)
target_link_libraries(ClientTest soma-test)

add_executable(CollectorTest CollectorTest.cpp)
target_link_libraries(CollectorTest soma-test)

add_test(NAME AdminTest COMMAND ./AdminTest AdminTest.xml)
add_test(NAME ClientTest COMMAND ./ClientTest ClientTest.xml)
add_test(NAME CollectorTest COMMAND ./CollectorTest CollectorTest.xml)
