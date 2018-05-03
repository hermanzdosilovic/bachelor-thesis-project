cmake_minimum_required( VERSION 3.10 )
project( core-layouter CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

include( ${CMAKE_CURRENT_LIST_DIR}/Layouter/Layouter.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/LayouterDemo/LayouterDemo.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/LayouterUtils/LayouterUtils.cmake )
