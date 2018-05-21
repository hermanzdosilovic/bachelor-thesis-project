if( NOT TARGET LayouterUtils )

    include( ${CMAKE_CURRENT_LIST_DIR}/../Layouter/Layouter.cmake )

    include( ${CMAKE_CURRENT_LIST_DIR}/LayouterUtils.srcs.cmake )

    add_library( LayouterUtils STATIC ${SOURCES} )
    target_include_directories( LayouterUtils PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Source )

    target_include_directories( LayouterUtils PRIVATE ${CMAKE_CURRENT_LIST_DIR}/json/include )
    target_include_directories( LayouterUtils PUBLIC  ${CMAKE_CURRENT_LIST_DIR}/spdlog/include )

    find_package( Threads )

    target_link_libraries( LayouterUtils PUBLIC Layouter ${CMAKE_THREAD_LIBS_INIT} stdc++fs )

endif( NOT TARGET LayouterUtils )
