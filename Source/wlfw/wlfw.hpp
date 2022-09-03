#pragma once
#ifndef WLFW_HEADER
#define WLFW_HEADER

#include "wlfwpch.hpp"

#ifdef WLFW_SHARED_LIBRARY
    #ifdef WLFW_SHARED_BUILD
        #ifdef _MSC_VER
            #define WLFW_API __declspec(dllexport)
        #else
            #define WLFW_API __attribute__((visibility("default")))
        #endif
    #else
        #ifdef _MSC_VER
            #define WLFW_API __declspec(dllimport)
        #else
            #define WLFW_API __attribute__((visibility("hidden")))
        #endif
    #endif
#else
    #define WLFW_API
#endif

////////////////////////////////////////////////////////////
/// \brief WLFW_BYTE Is Define Which Will Move Your Value
///
////////////////////////////////////////////////////////////
#define WLFW_BYTE(value) (1 << value)

#ifdef WLFW_WINDOW_PLATFORM_WIN32
    #include <Windows.h>
    #include <windowsx.h>
#else
    #ifdef WLFW_UNIX_WINDOW_PLATFORM_X11
        #include <X11/X11.h>
        #include <X11/Xlib.h>
    #elif WLFW_UNIX_WINDOW_PLATFORM_XCB
        #include <xcb/xcb.h>
    #elif WLFW_UNIX_WINDOW_PLATFORM_WAYLAND
        #include <wayland-client.h>
        #include <wayland-client-core.h>
        #include <wayland-client-protocol.h>
    #endif
#endif

#ifdef WLFW_DEBUG
    ////////////////////////////////////////////////////////////
    /// \brief WLFW_TRACE Is Define Which Will Trace Your Errors In Code
    ///
    ////////////////////////////////////////////////////////////
    #define WLFW_TRACE() { std::cerr << "wlfw trace : " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTION__ << '\n'; }
#else
    ////////////////////////////////////////////////////////////
    /// \brief WLFW_TRACE Is Not Used
    ///
    ////////////////////////////////////////////////////////////
    #define WLFW_TRACE()
#endif

////////////////////////////////////////////////////////////
/// \brief WLFW_CHECK Is Define Which Execute WLFW_TRACE If Your Entered Value Is Invalid
///
////////////////////////////////////////////////////////////
#define WLFW_CHECK(value) if(!value) { WLFW_TRACE(); }

#endif