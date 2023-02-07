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

class ClientTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( ClientTest );
    CPPUNIT_TEST( testOpenResource );
    CPPUNIT_TEST_SUITE_END();

    static constexpr const char* resource_config = "{ \"path\" : \"mydb\" }";
    UUID resource_id;

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

    void testOpenResource() {
        alpha::Client client(engine);
        std::string addr = engine.self();
        
        Resource my_resource = client.open(addr, 0, resource_id);
        CPPUNIT_ASSERT_MESSAGE(
                "Resource should be valid",
                static_cast<bool>(my_resource));

        auto bad_id = UUID::generate();
        CPPUNIT_ASSERT_THROW_MESSAGE(
                "client.open should fail on non-existing resource",
                client.open(addr, 0, bad_id);
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION( ClientTest );
