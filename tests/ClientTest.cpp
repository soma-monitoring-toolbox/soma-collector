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

class ClientTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( ClientTest );
    CPPUNIT_TEST( testOpenCollector );
    CPPUNIT_TEST_SUITE_END();

    static constexpr const char* collector_config = "{ \"path\" : \"mydb\" }";
    UUID collector_id;

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

    void testOpenCollector() {
        soma::Client client(engine);
        std::string addr = engine.self();
        
        Collector my_collector = client.open(addr, 0, collector_id);
        CPPUNIT_ASSERT_MESSAGE(
                "Collector should be valid",
                static_cast<bool>(my_collector));

        auto bad_id = UUID::generate();
        CPPUNIT_ASSERT_THROW_MESSAGE(
                "client.open should fail on non-existing collector",
                client.open(addr, 0, bad_id);
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION( ClientTest );
