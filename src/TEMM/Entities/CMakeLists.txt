set(INCROOT ${PROJECT_SOURCE_DIR}/include/TEMM/Entities)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/TEMM/Entities)

set(SRC
    ${SRCROOT}/Component.cpp
    ${INCROOT}/Component.hpp
    ${SRCROOT}/Entity.cpp
    ${INCROOT}/Entity.hpp
    ${SRCROOT}/ComponentPool.cpp
    ${INCROOT}/ComponentPool.hpp)
source_group("" FILES {SRC})

add_library(temm-entities ${SRC})
