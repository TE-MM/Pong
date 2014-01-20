#include <TEMM/Entities/ResourceManager.hpp>
#define BOOST_TEST_MODULE ManagerTest
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ResourceManagerTest)

BOOST_AUTO_TEST_CASE(ConstructorTest) {
	BOOST_CHECK_NO_THROW(temm::ResourceManager rm);
}

BOOST_AUTO_TEST_SUITE_END()
