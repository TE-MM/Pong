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

#ifndef ENTITY_HPP
#define ENTITY_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <TEMM/Entities/Component.hpp>
#include <vector>


namespace temm {

////////////////////////////////////////////////////////////
/// \brief Composite Component representing an entity
///
////////////////////////////////////////////////////////////
class Entity: public Component {
public:

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	////////////////////////////////////////////////////////////
	Entity();

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	/// Releases all attachment to components, allowing them
	/// to be taken by other entities.
	///
	////////////////////////////////////////////////////////////
	~Entity();

	////////////////////////////////////////////////////////////
	/// \brief As composite, updates constitutive components
	///
	/// Calls update() on all constituent components that make
	/// up the entity.
	///
	/// \param delta      Desired frames per second or milliseconds since last iteration
	/// \param delta_type Specification of delta
	///
	////////////////////////////////////////////////////////////
	void update(int delta, DeltaType delta_type);

	////////////////////////////////////////////////////////////
	/// \brief Attaches component to entity
	///
	/// Attaches component to entity, becoming part of the
	/// composite entity. Once part of the entity, the component
	/// cannot be attached to another.
	///
	/// \param component The component to be attached to
	///
	////////////////////////////////////////////////////////////
	bool attach(Component& component);

	////////////////////////////////////////////////////////////
	/// \brief Returns number of components attached
	///
	/// \return Number of attached components
	///
	////////////////////////////////////////////////////////////
	unsigned numComponents();

private:

	Entity(const Entity&);
	Entity& operator=(const Entity&);

	////////////////////////////////////////////////////////////
	/// Member data
	////////////////////////////////////////////////////////////
	std::vector<Component*> m_components; ///< Constituent components
};

} // namespace temm

#endif // ENTITY_HPP

