set( SOURCES "" )

set( Source
    ${CMAKE_CURRENT_LIST_DIR}/Source/TestResult.hpp

    ${CMAKE_CURRENT_LIST_DIR}/Source/Test/Main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Test/MatrixTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Test/EditDistanceTest.cpp

    ${CMAKE_CURRENT_LIST_DIR}/Source/Test/Aligner/AlignerTest.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Test/Aligner/MaxOverlapAlignerTest.cpp

    ${CMAKE_CURRENT_LIST_DIR}/Source/Test/Spacer/AvgCharCenterDistanceSpacerTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Test/Spacer/AvgCharWidthSpacerTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Test/Spacer/AvgRelativeDistanceSpacerTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Source/Test/Spacer/SpacerTest.hpp
)

source_group( "Source" FILES ${Source} )
list( APPEND SOURCES ${Source} )
