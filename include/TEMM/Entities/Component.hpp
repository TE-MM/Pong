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

#ifndef COMPONENT_HPP
#define COMPONENT_HPP


namespace temm {
class Entity;

////////////////////////////////////////////////////////////
/// \brief Constants passed to Component::update()
///
/// The component updates according to either the desired
/// framerate or the amount of milliseconds since the last
/// game loop iteration.
///
////////////////////////////////////////////////////////////
enum DeltaType {
	FRAMES_PER_SECOND,
	MILLISECONDS_PASSED
};

////////////////////////////////////////////////////////////
/// \brief Base class for component-based object system
///
////////////////////////////////////////////////////////////
class Component {
public:

	////////////////////////////////////////////////////////////
	/// \brief Base constructor
	///
	////////////////////////////////////////////////////////////
	Component();

	////////////////////////////////////////////////////////////
	/// \brief Virtual destructor
	///
	/// Since Component is a base class, it is necessary for its
	/// destructor to be virtual so that its derived class may
	/// be destructed accordingly.
	///
	////////////////////////////////////////////////////////////
	virtual ~Component();

	////////////////////////////////////////////////////////////
	/// \brief Method called on game loop iteration
	///
	/// Template method to be overridden by subclasses. Updates
	/// the component's state on each game loop iteration.
	///
	/// \param delta      Desired frames per second or milliseconds since last iteration
	/// \param delta_type Specification of delta
	///
	////////////////////////////////////////////////////////////
	virtual void update(int delta, DeltaType delta_type) = 0;

	////////////////////////////////////////////////////////////
	/// \brief Releases bond with entity
	///
	/// Releases bond with current entity and becomes available
	/// for reuse.
	///
	////////////////////////////////////////////////////////////
	void release();

private:

	Component(const Component&);
	Component& operator=(const Component&);

	////////////////////////////////////////////////////////////
	/// Member data
	////////////////////////////////////////////////////////////
	Entity* m_entity; ///< Currently bonded entity
};

} // namespace temm

#endif // COMPONENT_HPP


////////////////////////////////////////////////////////////
/// \class temm::Component
/// \ingroup entities
///
/// Components are like properties that inhere in an
/// underlying substance, the entity. The entity has no
/// characteristics. It's the "glue" that holds the various
/// components together to make the thing.
///
/// The relationship between entity and component is a
/// one-to-many relationship. Components have no meaning
/// apart from the entity they inhere in. For this reason,
/// entities reference components by composition, and
/// components require an entity in construction. Upon an
/// entity's being destroyed, so too are all its components.
/// An entity may also release a component at any time.
///
/// The Component class is a base class. It has a pure
/// virtual update() method that is defined in its
/// subclasses.
///
////////////////////////////////////////////////////////////

