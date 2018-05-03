if( NOT TARGET LayouterUtils )

    include( ${CMAKE_CURRENT_LIST_DIR}/../Layouter/Layouter.cmake )

    include( ${CMAKE_CURRENT_LIST_DIR}/LayouterUtils.srcs.cmake )

    add_library( LayouterUtils STATIC ${SOURCES} )
    target_include_directories( LayouterUtils PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Source )

    target_link_libraries( LayouterUtils PUBLIC Layouter )
    target_include_directories( LayouterUtils PRIVATE ${CMAKE_CURRENT_LIST_DIR}/json/include )

endif( NOT TARGET LayouterUtils )
