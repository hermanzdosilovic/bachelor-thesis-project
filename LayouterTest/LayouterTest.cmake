if( NOT TARGET LayouterTest )

    include( ${CMAKE_CURRENT_LIST_DIR}/../Layouter/Layouter.cmake )
    include( ${CMAKE_CURRENT_LIST_DIR}/../LayouterUtils/LayouterUtils.cmake )

    include( ${CMAKE_CURRENT_LIST_DIR}/LayouterTest.srcs.cmake )

    add_executable( LayouterTest ${SOURCES} )
    target_link_libraries( LayouterTest PRIVATE Layouter LayouterUtils )
    target_include_directories( LayouterTest PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Source )

    target_include_directories( LayouterTest PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Catch2/single_include )

endif( NOT TARGET LayouterTest )
