set( SOURCES "" )

set( Source
    ${CMAKE_CURRENT_LIST_DIR}/Source/OcrChar.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/OcrResult.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Types.hpp
)

source_group( "Source" FILES ${Source} )
list( APPEND SOURCES ${Source} )
