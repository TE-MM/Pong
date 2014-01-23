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
#include <TEMM/Entities/Component.hpp>
#include <TEMM/Entities/Entity.hpp>


namespace temm {
////////////////////////////////////////////////////////////
Component::Component(): m_entity(0) {
}


////////////////////////////////////////////////////////////
Component::~Component() {
	release();
}


////////////////////////////////////////////////////////////
void Component::release() {
	if (m_entity != 0) {
		for (unsigned i = 0; i < m_entity->m_components.size(); ++i) {
			if (m_entity->m_components[i] == this) {
				m_entity->m_components.erase(m_entity->m_components.begin() + i);
				break;
			}
		}
		m_entity = 0;
	}
}

} // namespace temm

