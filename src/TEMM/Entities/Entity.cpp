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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <TEMM/Entities/Entity.hpp>


namespace temm {
////////////////////////////////////////////////////////////
Entity::Entity(): Component() {
}


////////////////////////////////////////////////////////////
Entity::~Entity() {
	for (unsigned i = 0; i < m_components.size(); ++i) {
		m_components[i]->m_entity = 0;
	}
}


////////////////////////////////////////////////////////////
void Entity::update(int delta, DeltaType delta_type) {
	for (unsigned i = 0; i < m_components.size(); ++i) {
		m_components[i]->update(delta, delta_type);
	}
}


////////////////////////////////////////////////////////////
bool Entity::attach(Component& component) {
	if (component.m_entity == 0) {
		component.m_entity = this;
		m_components.push_back(&component);
		return true;
	}
	return false;
}


////////////////////////////////////////////////////////////
unsigned Entity::numComponents() {
	return m_components.size();
}

}

