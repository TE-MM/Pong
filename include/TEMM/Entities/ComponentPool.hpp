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

#ifndef COMPONENT_POOL_HPP
#define COMPONENT_POOL_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <TEMM/Entities/Entity.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <stdexcept>


namespace temm {
template<class C> class PoolPtr;

typedef unsigned component_index;

template<class C>
class ComponentPool {
public:

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	////////////////////////////////////////////////////////////
	~ComponentPool() {
		delete[] m_pool;
	}

	component_index lock(Entity& entity) {
		unsigned i = 0;
		for (; i < SIZE; ++i) {
			if (m_pool[i].m_entity == 0 ) {
				entity.attach(m_pool[i]);
				break;
			}
		}
		return i;
	}

	void update(int delta, DeltaType delta_type) {
		for (unsigned i = 0; i < SIZE; ++i) {
			if (m_pool[i].m_entity != 0) m_pool[i].update(delta, delta_type);
		}
	}

	unsigned acquired() {
		unsigned acquired = 0;
		for (unsigned i = 0; i < SIZE; ++i) {
			if (m_pool[i].m_entity != 0) {
				acquired++;
			}
		}
		return acquired;
	}

	C& operator[](component_index index) {
		if (index < SIZE) return m_pool[index];
		throw new std::out_of_range("We require more minerals. Pool too small.");
	}

private:

	friend class PoolPtr<C>;

	////////////////////////////////////////////////////////////
	/// \brief Main constructor
	///
	////////////////////////////////////////////////////////////
	ComponentPool(unsigned number):
		m_pool(new C[number]),
		//m_available(new bool[number]),
		//m_acquired(0),
		SIZE(number) {
	}

	////////////////////////////////////////////////////////////
	/// Member data
	////////////////////////////////////////////////////////////
	C*             m_pool;      ///< Actual pool
	//bool*          m_available; ///< Availablility index
	//unsigned       m_acquired;  ///< Number of locked resources
	const unsigned SIZE;        ///< Size of pool
};


template<class C>
class PoolPtr {
public:

	////////////////////////////////////////////////////////////
	/// \brief Main constructor
	///
	/// This is the only method by which a user can construct a
	/// component pool. The point is to abstract away "new" and
	/// complications with boost shared_ptr.
	///
	////////////////////////////////////////////////////////////
	PoolPtr(unsigned number): m_pool(new ComponentPool<C>(number)) {}

	const boost::shared_ptr<ComponentPool<C> >& operator->() const {
		return m_pool;
	}

	ComponentPool<C>& operator*() const {
		return *m_pool;
	}

	C& operator[](component_index index) {
		return (*m_pool)[index];
	}

private:

	////////////////////////////////////////////////////////////
	/// Member data
	////////////////////////////////////////////////////////////
	boost::shared_ptr<ComponentPool<C> > m_pool; ///< Pointer to ComponentPool object
};

} // namespace temm

#endif // COMPONENT_POOL_HPP

