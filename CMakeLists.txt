cmake_minimum_required(VERSION 3.17)
project(wlfw)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(WLFW_SOURCE
    Source/wlfw/wlfw.hpp
    Source/wlfw/wlfw.cpp
    Source/wlfw/Window.hpp
    Source/wlfw/NativeWindow.hpp
    Source/wlfw/NativeWindow.cpp
    Source/wlfw/Event.hpp
    Source/wlfw/EventHandler.hpp
)

set(WLFW_UNIX_WINDOW_PLATFORM Wayland)
if(UNIX)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)

    if(WLFW_UNIX_WINDOW_PLATFORM STREQUAL "X11")
        message("-- Using X11")
        find_package(X11 REQUIRED)

        set(WLFW_PLATFORM_SOURCE
            Source/wlfw/X11/WindowX11.hpp
            Source/wlfw/X11/WindowX11.cpp
        )
    elseif(WLFW_UNIX_WINDOW_PLATFORM STREQUAL "XCB")
        message("-- Using XCB")
        find_package(X11 REQUIRED)

        set(WLFW_PLATFORM_SOURCE
            Source/wlfw/XCB/WindowXCB.hpp
            Source/wlfw/XCB/WindowXCB.cpp
        )
    elseif(WLFW_UNIX_WINDOW_PLATFORM STREQUAL "Wayland")
        message("-- Using Wayland")
        
        # execute_process(COMMAND wget https://cgit.freedesktop.org/wayland/wayland-protocols/plain/stable/xdg-shell/xdg-shell.xml)

        # execute_process(COMMAND wayland-scanner client-header ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell.xml ${CMAKE_SOURCE_DIR}/Source/wlfw/Wayland/xdg-shell-client-protocol.hpp)
        # execute_process(COMMAND wayland-scanner private-code ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell.xml ${CMAKE_SOURCE_DIR}/Source/wlfw/Wayland/xdg-shell-protocol.cpp)

        set(WLFW_PLATFORM_SOURCE
            Source/wlfw/Wayland/xdg-shell-client-protocol.hpp
            Source/wlfw/Wayland/xdg-shell-protocol.cpp
            Source/wlfw/Wayland/WindowWayland.hpp
            Source/wlfw/Wayland/WindowWayland.cpp
        )
    endif()
else()
    message("-- Using Win32")

    set(WLFW_PLATFORM_SOURCE
        Source/wlfw/Win32/WindowWin32.hpp
        Source/wlfw/Win32/WindowWin32.cpp
    )
endif()

option(WLFW_SHARED_LIBRARY "wlfw build using shared libraries" OFF)
option(WLFW_SHARED_BUILD "wlfw build shared library files" OFF)

if(WLFW_SHARED_LIBRARY)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWLFW_SHARED_LIBRARY")
    if(WLFW_SHARED_BUILD)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWLFW_SHARED_BUILD")
    endif()
    add_library(${PROJECT_NAME} SHARED ${WLFW_SOURCE} ${WLFW_PLATFORM_SOURCE})
else()
    add_library(${PROJECT_NAME} STATIC ${WLFW_SOURCE} ${WLFW_PLATFORM_SOURCE})
endif()

target_precompile_headers(${PROJECT_NAME} PUBLIC Source/wlfw/wlfwpch.hpp Source/wlfw/wlfwpch.cpp)
target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:WLFW_DEBUG> $<$<CONFIG:RelWithDebInfo>:WLFW_DEBUG>)

if(UNIX)
    if(WLFW_UNIX_WINDOW_PLATFORM STREQUAL "X11")
        target_compile_definitions(${PROJECT_NAME} PUBLIC "-DWLFW_UNIX_WINDOW_PLATFORM_X11")
        target_link_libraries(${PROJECT_NAME} PUBLIC X11 Threads::Threads)
    elseif(WLFW_UNIX_WINDOW_PLATFORM STREQUAL "XCB")
        target_compile_definitions(${PROJECT_NAME} PUBLIC "-DWLFW_UNIX_WINDOW_PLATFORM_XCB")
        target_link_libraries(${PROJECT_NAME} PUBLIC X11 xcb Threads::Threads)
    elseif(WLFW_UNIX_WINDOW_PLATFORM STREQUAL "Wayland")
        target_compile_definitions(${PROJECT_NAME} PUBLIC "-DWLFW_UNIX_WINDOW_PLATFORM_WAYLAND")
        target_link_libraries(${PROJECT_NAME} PUBLIC wayland-client Threads::Threads)
    endif()
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC "-DWLFW_WINDOW_PLATFORM_WIN32")
endif()

add_subdirectory(Examples)