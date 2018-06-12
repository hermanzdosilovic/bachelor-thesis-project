if( NOT TARGET LayouterDemo )

    include( ${CMAKE_CURRENT_LIST_DIR}/../Layouter/Layouter.cmake )
    include( ${CMAKE_CURRENT_LIST_DIR}/../LayouterUtils/LayouterUtils.cmake )

    include( ${CMAKE_CURRENT_LIST_DIR}/LayouterDemo.srcs.cmake )

    add_executable( LayouterDemo ${SOURCES} )
    target_include_directories( LayouterDemo PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Dependencies/cmdline )
    target_include_directories( LayouterDemo PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Dependencies/matplotlib-cpp )
    target_link_libraries( LayouterDemo PRIVATE Layouter LayouterUtils ${PYTHON_LIBRARIES} )

    option( LayouterDemo_USE_MATPLOTLIB "Use matplotlib for plotting results" OFF )
    if ( LayouterDemo_USE_MATPLOTLIB )
        target_compile_definitions( LayouterDemo PUBLIC LAYOUTERDEMO_USE_MATPLOTLIB )
        find_package( PythonLibs 2.7 )
        target_include_directories( LayouterDemo PRIVATE ${PYTHON_INCLUDE_DIRS} )
        target_link_libraries( LayouterDemo PRIVATE ${PYTHON_LIBRARIES} )
    endif( LayouterDemo_USE_MATPLOTLIB )

endif( NOT TARGET LayouterDemo )
