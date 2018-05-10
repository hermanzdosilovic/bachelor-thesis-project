if( NOT TARGET Layouter )

    include( ${CMAKE_CURRENT_LIST_DIR}/Layouter.srcs.cmake )

    add_library( Layouter STATIC ${SOURCES} )
    target_include_directories( Layouter PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Source )

endif( NOT TARGET Layouter )
