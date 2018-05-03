if( NOT TARGET LayouterDemo )

    include( ${CMAKE_CURRENT_LIST_DIR}/../Layouter/Layouter.cmake )
    include( ${CMAKE_CURRENT_LIST_DIR}/../LayouterUtils/LayouterUtils.cmake )

    include( ${CMAKE_CURRENT_LIST_DIR}/LayouterDemo.srcs.cmake )

    add_executable( LayouterDemo ${SOURCES} )
    target_link_libraries( LayouterDemo PRIVATE Layouter LayouterUtils )

endif( NOT TARGET LayouterDemo )
