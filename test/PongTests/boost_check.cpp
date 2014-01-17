#define BOOST_TEST_MODULE BoostCheck
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(BoostWorks) {
	bool t = true;
	BOOST_CHECK_EQUAL(t, true);
}
