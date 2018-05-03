if( NOT TARGET Layouter )

    include( ${CMAKE_CURRENT_LIST_DIR}/Layouter.srcs.cmake )

    add_library( Layouter INTERFACE )
    target_include_directories( Layouter INTERFACE ${CMAKE_CURRENT_LIST_DIR}/Source )

endif( NOT TARGET Layouter )
