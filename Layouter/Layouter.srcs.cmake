set( SOURCES "" )

set( Source
    ${CMAKE_CURRENT_LIST_DIR}/Source/Layouter/Aligner/Aligner.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Layouter/Aligner/MaxOverlapAligner.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Layouter/Aligner/MaxOverlapAligner.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Layouter/Aligner/NoneAligner.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Layouter/Aligner/NoneAligner.hpp

    ${CMAKE_CURRENT_LIST_DIR}/Source/Layouter/Spacer/Spacer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Layouter/Spacer/AvgCharWidthSpacer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Layouter/Spacer/AvgCharWidthSpacer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Layouter/Spacer/AvgRelativeDistanceSpacer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Layouter/Spacer/AvgRelativeDistanceSpacer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Layouter/Spacer/AvgCharCenterDistanceSpacer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Layouter/Spacer/AvgCharCenterDistanceSpacer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Layouter/Spacer/NoneSpacer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Layouter/Spacer/NoneSpacer.hpp

    ${CMAKE_CURRENT_LIST_DIR}/Source/Layouter/Layouter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Layouter/Layouter.hpp

    ${CMAKE_CURRENT_LIST_DIR}/Source/OcrChar.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/OcrChar.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/OcrResult.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/OcrResult.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Types.hpp
)

source_group( "Source" FILES ${Source} )
list( APPEND SOURCES ${Source} )
