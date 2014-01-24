////////////////////////////////////////////////////////////////////////////////
// Entities - A Library of Things, not Pixels
// Part of the TEMM libraries
// Copyright (c) 2014 Tanner Evins and Matthew Miller
// Permission to use, copy, modify, distribute and sell this software for any
//     purpose is hereby granted without fee, provided that the above copyright
//     notice appear in all copies and that both that copyright notice and this
//     permission notice appear in supporting documentation.
// The authors make no representations about the suitability of this software
//     for any purpose. It is provided "as is" without express or implied
//     warranty.
////////////////////////////////////////////////////////////////////////////////

#include <TEMM/Entities/Component.hpp>
#include <TEMM/Entities/Entity.hpp>
#include <SFML/System.hpp>
#include <boost/shared_ptr.hpp>
#define BOOST_TEST_MODULE ManagerTest
#include <boost/test/unit_test.hpp>

////////////////////////////////////////////////////////////
/// Dummy derived class of component. Increments its single
/// data member on update()
///
////////////////////////////////////////////////////////////
class PhoneyComponey : public temm::Component {
public:
	PhoneyComponey(): updatee(0) {}
	void update(int delta, temm::DeltaType delta_type) {
		++updatee;
	}
	unsigned getValue() const {
		return updatee;
	}
private:
	unsigned updatee;
};


////////////////////////////////////////////////////////////
/// Test Suite: Entities and Components
///
/// Entities are composite components. Entities mean nothing
/// apart from the components that make them up.
///
/// This suite tests entities acquiring standalone
/// components without pools. Components may be placed on
/// the stack.
///
////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(EntitiesAndComponentsSutie)

	////////////////////////////////////////////////////////////
	/// Basic use case
	///
	////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(BasicProperUse) {

		// Create entity
		temm::Entity e;

		// Create component
		PhoneyComponey c;

		// Attach entity to component
		// Check success or failure and number of components
		bool attach_success = e.attach(c);
		BOOST_CHECK_EQUAL(attach_success, true);
		unsigned num_components = e.numComponents();
		BOOST_CHECK_EQUAL(num_components, 1);

		// Update all constituent components
		e.update(1, temm::FRAMES_PER_SECOND);

		// Check that component was in fact updated
		unsigned value = c.getValue();
		BOOST_CHECK_EQUAL(value, 1);

	}

	////////////////////////////////////////////////////////////
	/// There is only one entity to a component. An entity that
	/// tries to attach to a taken component will fail to do so.
	///
	////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(MultipleEntities) {

		// Create two entities
		temm::Entity e0;
		temm::Entity e1;

		// Create one component
		PhoneyComponey c;

		// Entity e0 successfully attaches
		e0.attach(c);

		// Entity e1 tries and fails
		bool attach_success = e1.attach(c);
		BOOST_CHECK_EQUAL(attach_success, false);
		unsigned num_components = e1.numComponents();
		BOOST_CHECK_EQUAL(num_components, 0);

	}

	////////////////////////////////////////////////////////////
	/// If a component falls out of scope before its entity,
	/// the entity must be aware of this occurrence.
	///
	////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(PrematureComponent) {

		temm::Entity e;

		{ // Component is declared in interior scope

			PhoneyComponey c;
			e.attach(c);

		} // Component falls out of scope

		unsigned num_components = e.numComponents();
		BOOST_CHECK_EQUAL(num_components, 0);

	}

	////////////////////////////////////////////////////////////
	/// Components may be manually released at any time, at
	/// which point they can be taken by other entities.
	///
	////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(ManualRelease) {

		temm::Entity e0;
		temm::Entity e1;
		PhoneyComponey c;

		e0.attach(c);
		e0.update(1, temm::FRAMES_PER_SECOND);

		// Release the component from e0
		c.release();

		// Check that e0 knows
		unsigned num_components = e0.numComponents();
		BOOST_CHECK_EQUAL(num_components, 0);

		// e1 acquires component; check for successful acquisition
		bool attach_success = e1.attach(c);
		BOOST_CHECK_EQUAL(attach_success, true);
		num_components = e1.numComponents();
		BOOST_CHECK_EQUAL(num_components, 1);

		e1.update(1, temm::FRAMES_PER_SECOND);

		// Check that each entity updated the component
		unsigned value = c.getValue();
		BOOST_CHECK_EQUAL(value, 2);

	}

BOOST_AUTO_TEST_SUITE_END()

