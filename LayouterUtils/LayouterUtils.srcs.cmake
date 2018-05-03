set( SOURCES "" )

set( Source
    ${CMAKE_CURRENT_LIST_DIR}/Source/OcrResultSerializer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/OcrResultSerializer.hpp
)

source_group( "Source" FILES ${Source} )
list( APPEND SOURCES ${Source} )
