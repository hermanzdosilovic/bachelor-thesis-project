set( SOURCES "" )

set( Source
    ${CMAKE_CURRENT_LIST_DIR}/Source/Matrix.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/EditDistance.hpp

    ${CMAKE_CURRENT_LIST_DIR}/Source/Test/Main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Test/MatrixTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Test/EditDistanceTest.cpp
)

source_group( "Source" FILES ${Source} )
list( APPEND SOURCES ${Source} )
