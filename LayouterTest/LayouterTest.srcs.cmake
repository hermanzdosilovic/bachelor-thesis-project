set( SOURCES "" )

set( Source
    ${CMAKE_CURRENT_LIST_DIR}/Source/Matrix.hpp

    ${CMAKE_CURRENT_LIST_DIR}/Source/Test/Main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Test/MatrixTest.cpp
)

source_group( "Source" FILES ${Source} )
list( APPEND SOURCES ${Source} )
