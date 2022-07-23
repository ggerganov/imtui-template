if (MY_IMTUI_PROJECT_ALL_WARNINGS)
    if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    else()
        # todo : windows
    endif()
endif()

#
## Main

set(TARGET imtui-app)

add_executable(${TARGET}
    main.cpp
    )

target_link_libraries(${TARGET} PRIVATE
    imtui-ncurses
    ${CMAKE_DL_LIBS}
    )
