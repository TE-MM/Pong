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
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <stdexcept>


namespace temm {
template<class C> class ComponentPool;
template<class C> class PoolPtr;
class Entity;

template<class C>
class ComponentPtr {
public:

	void release() {
		boost::shared_ptr<ComponentPool<C> > ptr = m_pool.lock();
		(*ptr)[m_index].release();
	}

	bool hasResource() {
		boost::shared_ptr<ComponentPool<C> > ptr = m_pool.lock();
		if (ptr) return true;
		return false;
	}

	C& operator*() const {
		boost::shared_ptr<ComponentPool<C> > ptr = m_pool.lock();
		if (!ptr) throw std::runtime_error;
		return (*ptr)[m_index];
	}

	C* operator->() const {
		boost::shared_ptr<ComponentPool<C> > ptr = m_pool.lock();
		if (!ptr) throw new std::runtime_error("Dereferencing deleted component.");
		return &(*ptr)[m_index];
	}

private:

	friend class ComponentPool<C>;

	ComponentPtr(unsigned index, boost::weak_ptr<ComponentPool<C> > pool) :
		m_index(index),
		m_pool(pool) {
	}
	
	////////////////////////////////////////////////////////////
	/// Member data
	////////////////////////////////////////////////////////////
	unsigned                           m_index; ///< Index to resource
	boost::weak_ptr<ComponentPool<C> > m_pool;  ///< Weak reference to component pool
};


template<class C>
class ComponentPool {
public:

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	////////////////////////////////////////////////////////////
	~ComponentPool() {
		delete[] m_pool;
		delete[] m_available;
	}

	ComponentPtr<C> lock(Entity& entity) {
		unsigned i = 0;
		for (; i < SIZE; ++i) {
			if (m_available[i] == true) m_available[i] = false;
		}
		if (i < SIZE) {
			entity.attach(m_pool[i]);
			++m_acquired;
			boost::shared_ptr<ComponentPool<C> > s_ptr(this);
			boost::weak_ptr<ComponentPool<C> > w_ptr(s_ptr);
			return ComponentPtr<C>(i, w_ptr);
		}
		boost::weak_ptr<ComponentPool<C> > w_ptr;
		return ComponentPtr<C>(0, w_ptr);
	}

	void update(int delta, DeltaType delta_type) {
		for (unsigned i = 0; i < SIZE; ++i) {
			if (m_available[i] == false) m_pool[i].update(delta, delta_type);
		}
	}

	unsigned acquired() {
		return m_acquired;
	}

	C& operator[](unsigned index) {
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
		m_available(new bool[number]),
		SIZE(number) {
		for (unsigned i = 0; i < SIZE; ++i) {
			m_available[i] = true;
		}
	}

	////////////////////////////////////////////////////////////
	/// Member data
	////////////////////////////////////////////////////////////
	C*             m_pool;      ///< Actual pool
	bool*          m_available; ///< Availablility index
	unsigned       m_acquired;  ///< Number of locked resources
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

private:

	////////////////////////////////////////////////////////////
	/// Member data
	////////////////////////////////////////////////////////////
	boost::shared_ptr<ComponentPool<C> > m_pool; ///< Pointer to ComponentPool object
};

} // namespace temm

#endif // COMPONENT_POOL_HPP

