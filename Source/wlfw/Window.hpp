#pragma once
#ifndef WLFW_WINDOW_HEADER
#define WLFW_WINDOW_HEADER

#ifdef WLFW_WINDOW_PLATFORM_WIN32
    #include "Win32/WindowWin32.hpp"
#else
    #ifdef WLFW_UNIX_WINDOW_PLATFORM_X11
        #include "X11/WindowX11.hpp"
    #elif WLFW_UNIX_WINDOW_PLATFORM_XCB
        #include "XCB/WindowXCB.hpp"
    #elif WLFW_UNIX_WINDOW_PLATFORM_WAYLAND
        #include "Wayland/WindowWayland.hpp"
    #endif
#endif

#endif