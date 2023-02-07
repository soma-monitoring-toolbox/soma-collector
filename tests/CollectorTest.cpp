/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#include <cppunit/extensions/HelperMacros.h>
#include <soma/Client.hpp>
#include <soma/Admin.hpp>

extern thallium::engine engine;
extern std::string collector_type;

class CollectorTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( CollectorTest );
    CPPUNIT_TEST( testMakeCollectorHandle );
    CPPUNIT_TEST( testSayHello );
    CPPUNIT_TEST( testComputeSum );
    CPPUNIT_TEST_SUITE_END();

    static constexpr const char* collector_config = "{ \"path\" : \"mydb\" }";
    soma::UUID collector_id;

    public:

    void setUp() {
        soma::Admin admin(engine);
        std::string addr = engine.self();
        collector_id = admin.createCollector(addr, 0, collector_type, collector_config);
    }

    void tearDown() {
        soma::Admin admin(engine);
        std::string addr = engine.self();
        admin.destroyCollector(addr, 0, collector_id);
    }

    void testMakeCollectorHandle() {
        soma::Client client(engine);
        std::string addr = engine.self();

        CPPUNIT_ASSERT_NO_THROW_MESSAGE(
                "client.makeCollectorHandle should not throw for valid id.",
                client.makeCollectorHandle(addr, 0, collector_id));

        auto bad_id = soma::UUID::generate();
        CPPUNIT_ASSERT_THROW_MESSAGE(
                "client.makeCollectorHandle should throw for invalid id.",
                client.makeCollectorHandle(addr, 0, bad_id),
                soma::Exception);
        
        CPPUNIT_ASSERT_THROW_MESSAGE(
                "client.makeCollectorHandle should throw for invalid provider.",
                client.makeCollectorHandle(addr, 1, collector_id),
                std::exception);
        
        CPPUNIT_ASSERT_NO_THROW_MESSAGE(
                "client.makeCollectorHandle should not throw for invalid id when check=false.",
                client.makeCollectorHandle(addr, 0, bad_id, false));

        CPPUNIT_ASSERT_NO_THROW_MESSAGE(
                "client.makeCollectorHandle should not throw for invalid provider when check=false.",
                client.makeCollectorHandle(addr, 1, collector_id, false));
    }

    void testSayHello() {
        soma::Client client(engine);
        std::string addr = engine.self();
        
        soma::CollectorHandle my_collector = client.makeCollectorHandle(addr, 0, collector_id);

        CPPUNIT_ASSERT_NO_THROW_MESSAGE(
                "my_collector.sayHello() should not throw.",
                my_collector.sayHello());
    }

    void testComputeSum() {
        soma::Client client(engine);
        std::string addr = engine.self();
        
        soma::CollectorHandle my_collector = client.makeCollectorHandle(addr, 0, collector_id);

        int32_t result = 0;
        CPPUNIT_ASSERT_NO_THROW_MESSAGE(
                "my_collector.computeSum() should not throw.",
                my_collector.computeSum(42, 51, &result));

        CPPUNIT_ASSERT_EQUAL_MESSAGE(
                "42 + 51 should be 93",
                93, result);

        CPPUNIT_ASSERT_NO_THROW_MESSAGE(
                "my_collector.computeSum() should not throw when passed NULL.",
                my_collector.computeSum(42, 51, nullptr));

        soma::AsyncRequest request;
        CPPUNIT_ASSERT_NO_THROW_MESSAGE(
                "my_collector.computeSum() should not throw when called asynchronously.",
                my_collector.computeSum(42, 51, &result, &request));

        CPPUNIT_ASSERT_NO_THROW_MESSAGE(
                "request.wait() should not throw.",
                request.wait());
    }

};
CPPUNIT_TEST_SUITE_REGISTRATION( CollectorTest );
