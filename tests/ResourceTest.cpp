/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#include <cppunit/extensions/HelperMacros.h>
#include <alpha/Client.hpp>
#include <alpha/Admin.hpp>

extern thallium::engine engine;
extern std::string resource_type;

class ResourceTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( ResourceTest );
    CPPUNIT_TEST( testMakeResourceHandle );
    CPPUNIT_TEST( testSayHello );
    CPPUNIT_TEST( testComputeSum );
    CPPUNIT_TEST_SUITE_END();

    static constexpr const char* resource_config = "{ \"path\" : \"mydb\" }";
    alpha::UUID resource_id;

    public:

    void setUp() {
        alpha::Admin admin(engine);
        std::string addr = engine.self();
        resource_id = admin.createResource(addr, 0, resource_type, resource_config);
    }

    void tearDown() {
        alpha::Admin admin(engine);
        std::string addr = engine.self();
        admin.destroyResource(addr, 0, resource_id);
    }

    void testMakeResourceHandle() {
        alpha::Client client(engine);
        std::string addr = engine.self();

        CPPUNIT_ASSERT_NO_THROW_MESSAGE(
                "client.makeResourceHandle should not throw for valid id.",
                client.makeResourceHandle(addr, 0, resource_id));

        auto bad_id = alpha::UUID::generate();
        CPPUNIT_ASSERT_THROW_MESSAGE(
                "client.makeResourceHandle should throw for invalid id.",
                client.makeResourceHandle(addr, 0, bad_id),
                alpha::Exception);
        
        CPPUNIT_ASSERT_THROW_MESSAGE(
                "client.makeResourceHandle should throw for invalid provider.",
                client.makeResourceHandle(addr, 1, resource_id),
                std::exception);
        
        CPPUNIT_ASSERT_NO_THROW_MESSAGE(
                "client.makeResourceHandle should not throw for invalid id when check=false.",
                client.makeResourceHandle(addr, 0, bad_id, false));

        CPPUNIT_ASSERT_NO_THROW_MESSAGE(
                "client.makeResourceHandle should not throw for invalid provider when check=false.",
                client.makeResourceHandle(addr, 1, resource_id, false));
    }

    void testSayHello() {
        alpha::Client client(engine);
        std::string addr = engine.self();
        
        alpha::ResourceHandle my_resource = client.makeResourceHandle(addr, 0, resource_id);

        CPPUNIT_ASSERT_NO_THROW_MESSAGE(
                "my_resource.sayHello() should not throw.",
                my_resource.sayHello());
    }

    void testComputeSum() {
        alpha::Client client(engine);
        std::string addr = engine.self();
        
        alpha::ResourceHandle my_resource = client.makeResourceHandle(addr, 0, resource_id);

        int32_t result = 0;
        CPPUNIT_ASSERT_NO_THROW_MESSAGE(
                "my_resource.computeSum() should not throw.",
                my_resource.computeSum(42, 51, &result));

        CPPUNIT_ASSERT_EQUAL_MESSAGE(
                "42 + 51 should be 93",
                93, result);

        CPPUNIT_ASSERT_NO_THROW_MESSAGE(
                "my_resource.computeSum() should not throw when passed NULL.",
                my_resource.computeSum(42, 51, nullptr));

        alpha::AsyncRequest request;
        CPPUNIT_ASSERT_NO_THROW_MESSAGE(
                "my_resource.computeSum() should not throw when called asynchronously.",
                my_resource.computeSum(42, 51, &result, &request));

        CPPUNIT_ASSERT_NO_THROW_MESSAGE(
                "request.wait() should not throw.",
                request.wait());
    }

};
CPPUNIT_TEST_SUITE_REGISTRATION( ResourceTest );
