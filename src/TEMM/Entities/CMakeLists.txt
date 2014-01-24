set(INCROOT ${PROJECT_SOURCE_DIR}/include/TEMM/Entities)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/TEMM/Entities)

set(SRC
    ${SRCROOT}/Component.cpp
    ${INCROOT}/Component.hpp
    ${SRCROOT}/Entity.cpp
    ${INCROOT}/Entity.hpp
    ${INCROOT}/ComponentPool.hpp)
source_group("" FILES {SRC})

add_library(temm-entities ${SRC})
target_link_libraries(temm-entities ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_DATE_TIME_LIBRARY} ${Boost_CHRONO_LIBRARY})
