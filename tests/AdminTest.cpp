/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#include <alpha/Admin.hpp>
#include <cppunit/extensions/HelperMacros.h>

extern thallium::engine engine;
extern std::string resource_type;

class AdminTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( AdminTest );
    CPPUNIT_TEST( testAdminCreateResource );
    CPPUNIT_TEST_SUITE_END();

    static constexpr const char* resource_config = "{ \"path\" : \"mydb\" }";

    public:

    void setUp() {}
    void tearDown() {}

    void testAdminCreateResource() {
        alpha::Admin admin(engine);
        std::string addr = engine.self();

        alpha::UUID resource_id;
        // Create a valid Resource
        CPPUNIT_ASSERT_NO_THROW_MESSAGE("admin.createResource should return a valid Resource",
                resource_id = admin.createResource(addr, 0, resource_type, resource_config));

        // Create a Resource with a wrong backend type
        alpha::UUID bad_id;
        CPPUNIT_ASSERT_THROW_MESSAGE("admin.createResource should throw an exception (wrong backend)",
                bad_id = admin.createResource(addr, 0, "blabla", resource_config),
                alpha::Exception);

        // Destroy the Resource
        CPPUNIT_ASSERT_NO_THROW_MESSAGE("admin.destroyResource should not throw on valid Resource",
            admin.destroyResource(addr, 0, resource_id));

        // Destroy an invalid Resource
        CPPUNIT_ASSERT_THROW_MESSAGE("admin.destroyResource should throw on invalid Resource",
            admin.destroyResource(addr, 0, bad_id),
            alpha::Exception);
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION( AdminTest );
