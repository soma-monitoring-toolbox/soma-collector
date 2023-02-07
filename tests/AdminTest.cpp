/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#include <soma/Admin.hpp>
#include <cppunit/extensions/HelperMacros.h>

extern thallium::engine engine;
extern std::string collector_type;

class AdminTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( AdminTest );
    CPPUNIT_TEST( testAdminCreateCollector );
    CPPUNIT_TEST_SUITE_END();

    static constexpr const char* collector_config = "{ \"path\" : \"mydb\" }";

    public:

    void setUp() {}
    void tearDown() {}

    void testAdminCreateCollector() {
        soma::Admin admin(engine);
        std::string addr = engine.self();

        soma::UUID collector_id;
        // Create a valid Collector
        CPPUNIT_ASSERT_NO_THROW_MESSAGE("admin.createCollector should return a valid Collector",
                collector_id = admin.createCollector(addr, 0, collector_type, collector_config));

        // Create a Collector with a wrong backend type
        soma::UUID bad_id;
        CPPUNIT_ASSERT_THROW_MESSAGE("admin.createCollector should throw an exception (wrong backend)",
                bad_id = admin.createCollector(addr, 0, "blabla", collector_config),
                soma::Exception);

        // Destroy the Collector
        CPPUNIT_ASSERT_NO_THROW_MESSAGE("admin.destroyCollector should not throw on valid Collector",
            admin.destroyCollector(addr, 0, collector_id));

        // Destroy an invalid Collector
        CPPUNIT_ASSERT_THROW_MESSAGE("admin.destroyCollector should throw on invalid Collector",
            admin.destroyCollector(addr, 0, bad_id),
            soma::Exception);
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION( AdminTest );
