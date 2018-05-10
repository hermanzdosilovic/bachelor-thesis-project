set( SOURCES "" )

set( Source
    ${CMAKE_CURRENT_LIST_DIR}/Source/DatasetReader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/DatasetReader.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/OcrResultSerializer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/OcrResultSerializer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/String.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/String.hpp
)

source_group( "Source" FILES ${Source} )
list( APPEND SOURCES ${Source} )
