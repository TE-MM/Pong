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
#include <TEMM/Entities/ComponentPool.hpp>
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
/// Dummy function that expects to successfully acquire a
/// resource
///
////////////////////////////////////////////////////////////
int shareThread(const temm::PoolPtr<PhoneyComponey>& ptr) {
	temm::Entity e;
	temm::component_index index = ptr->lock(e);
	return 0;
}


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

////////////////////////////////////////////////////////////
/// Test Suite: Entities and Pools
///
/// This suite tests the various ways a user can have
/// entities acquire resources from component pools.
///
/// Pools are always dynamically allocated and shared. They
/// can only be referenced by its custom PoolPtr.
///
////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(EntitiesAndPoolsSuite)

	////////////////////////////////////////////////////////////
	/// Demonstrates how entities and pools are basically used.
	/// Preferably the pool's lifetime is longer than the
	/// entity. Here the pool is initialized, and the entity
	/// acquires resources and releases them as it falls out of
	/// scope.
	///
	////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(BasicProperUse) {

		// Create pool of 16 free PhoneyComponey objects
		temm::PoolPtr<PhoneyComponey> ptr(16);

		{ // Enter scope for entity creation

			// Create blank entity
			temm::Entity e;

			// Acquire available resource for entity e
			// Initialize weak pointer
			temm::component_index index = ptr->lock(e);

			// Resource pool should have 15 free resources
			unsigned inner_acquired = ptr->acquired();
			BOOST_CHECK_EQUAL(inner_acquired, 1);

			// Update entity's components
			BOOST_CHECK_NO_THROW(e.update(1, temm::FRAMES_PER_SECOND));

			// Check that component updated accordingly
			unsigned value = ptr[index].getValue();
			BOOST_CHECK_EQUAL(value, 1);

			// Entity knows how many components it has
			unsigned num_components = e.numComponents();
			BOOST_CHECK_EQUAL(num_components, 1);

		} // As entity e falls out of scope, locked resources are freed.

		// Resource pool should have 16 free resources
		unsigned outer_acquired = ptr->acquired();
		BOOST_CHECK_EQUAL(outer_acquired, 0);

	} // As ptr falls out of scope, the pool resources are freed since there are no other references

	////////////////////////////////////////////////////////////
	/// Component pools are meant to be used across several
	/// threads. This tests that multiple threads can acquire
	/// and release resources from the same pool.
	///
	////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(SharedUse) {

		// Create pool to be shared; this time only 4 objects
		temm::PoolPtr<PhoneyComponey> ptr(4);

		// Create thread that will reference the same resource pool
		// Thread acquires exactly one resource
		sf::Thread thread(&shareThread, ptr);
		thread.launch();

		// Create local entity
		temm::Entity e;

		// Lock three available resources
		for (unsigned i = 0; i < 3; ++i) {
			ptr->lock(e);
		}

		// Delay execution until thread finishes
		thread.wait();

		// At this point, the thread has finished executing. The
		// resources acquired by the thread should be freed,
		// allowing our entity to acquire the last free resource.
		temm::component_index index = ptr->lock(e);
		bool yes_or_no = (index < 4);
		BOOST_CHECK_EQUAL(yes_or_no, true);

	}

	////////////////////////////////////////////////////////////
	/// Sometimes an entity's lifetime is longer than its
	/// components. If an entity's resources no longer exist,
	/// it's call to update() must handle appropriately.
	///
	////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(EntityOuterScope) {

		// Create the entity in the outer scope
		temm::Entity e;

		// Outer pool to be updated
		temm::PoolPtr<PhoneyComponey> outer_ptr(1);

		// Acquire outer pool resource and initialize weak
		// pointer to a variable
		temm::component_index index = outer_ptr->lock(e);

		{ // Inner scope for our resource pool

			// Pool with just one resource and just one reference
			temm::PoolPtr<PhoneyComponey> inner_ptr(1);

			// Acquire the available resource
			inner_ptr->lock(e);

		}

		// Attempt to update, even if the component no longer exists
		BOOST_CHECK_NO_THROW(e.update(1, temm::FRAMES_PER_SECOND));

		// Existing component should have updated
		unsigned value = outer_ptr[index].getValue();
		BOOST_CHECK_EQUAL(value, 1);

		// Entity should be aware that it no longer has inner scoped component
		unsigned num_components = e.numComponents();
		BOOST_CHECK_EQUAL(num_components, 1);

	}

	////////////////////////////////////////////////////////////
	/// An entity does not have to fall out of scope to release
	/// a component. It can free its hold onto a component at
	/// anytime using its release method.
	///
	////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(ManualRelease) {

		// Create pool and entity, and acquire a resource
		temm::PoolPtr<PhoneyComponey> ptr(4);
		temm::Entity e;
		temm::component_index index = ptr->lock(e);

		// Release the resource
		ptr[index].release();

		// Check that it has been properly released
		unsigned num_components = e.numComponents();
		BOOST_CHECK_EQUAL(num_components, 0);
		unsigned acquired_resources = ptr->acquired();
		BOOST_CHECK_EQUAL(acquired_resources, 0);

	}

	////////////////////////////////////////////////////////////
	/// Besides centralizing shared resource acquisition,
	/// another advantage of using pools is to be able to update
	/// all pooled, acquired resources at once. This makes for
	/// flexible ways of calling update().
	///
	////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(UpdateThruPool) {

		// Initialize entities and pool
		temm::Entity e0;
		temm::Entity e1;
		temm::PoolPtr<PhoneyComponey> ptr(2);

		// Acquire resources
		temm::component_index c0 = ptr->lock(e0);
		temm::component_index c1 = ptr->lock(e1);

		ptr->update(1, temm::FRAMES_PER_SECOND);

		// Check component c0
		unsigned value = ptr[c0].getValue();
		BOOST_CHECK_EQUAL(value, 1);

		// Check component c1
		value = ptr[c1].getValue();
		BOOST_CHECK_EQUAL(value, 1);

	}

BOOST_AUTO_TEST_SUITE_END()
