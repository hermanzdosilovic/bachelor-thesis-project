set( SOURCES "" )

set( Source
    ${CMAKE_CURRENT_LIST_DIR}/Source/Main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Statistics.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Statistics.hpp
)

source_group( "Source" FILES ${Source} )
list( APPEND SOURCES ${Source} )
