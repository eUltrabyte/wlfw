#pragma once
#ifndef WLFW_HEADER
#define WLFW_HEADER

#include "wlfwpch.hpp"

#ifdef WLFW_UNIX_WINDOW_PLATFORM_WIN32

#else

#endif

#ifdef WLFW_DEBUG
    #define WLFW_TRACE() { std::cerr << "wlfw trace : " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTION__; }
#else
    #define WLFW_TRACE()
#endif

#define WLFW_CHECK(value) if(!value) { WLFW_TRACE(); }

#endif