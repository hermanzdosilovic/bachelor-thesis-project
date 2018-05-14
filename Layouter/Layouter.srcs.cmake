set( SOURCES "" )

set( Source
    ${CMAKE_CURRENT_LIST_DIR}/Source/Layouter/NoneLayouter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Layouter/NoneLayouter.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/OcrChar.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/OcrChar.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/OcrResult.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/OcrResult.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Types.hpp
)

source_group( "Source" FILES ${Source} )
list( APPEND SOURCES ${Source} )
