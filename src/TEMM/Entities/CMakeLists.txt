set(INCROOT ${PROJECT_SOURCE_DIR}/include/TEMM/Entities)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/TEMM/Entities)

set(SRC
    ${SRCROOT}/ResourceManager.cpp
    ${INCROOT}/ResourceManager.hpp)
source_group("" FILES {SRC})

add_library(temm ${SRC})
