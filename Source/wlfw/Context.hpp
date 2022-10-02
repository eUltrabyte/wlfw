#pragma once
#ifndef WLFW_CONTEXT_HEADER
#define WLFW_CONTEXT_HEADER

#include "Window.hpp"

#ifdef WLFW_WINDOW_PLATFORM_WIN32
    #ifdef WLFW_CONTEXT_OPENGL
        
    #elif WLFW_CONTEXT_VULKAN
        #define VK_USE_PLATFORM_WIN32_KHR
        #include <vulkan/vulkan.h>
    #endif
#else
    #ifdef WLFW_UNIX_WINDOW_PLATFORM_X11
        #ifdef WLFW_CONTEXT_OPENGL

        #elif WLFW_CONTEXT_VULKAN
            #define VK_USE_PLATFORM_XLIB_KHR
            #include <vulkan/vulkan.h>
        #endif
    #elif WLFW_UNIX_WINDOW_PLATFORM_XCB
        #ifdef WLFW_CONTEXT_OPENGL

        #elif WLFW_CONTEXT_VULKAN
            #define VK_USE_PLATFORM_XCB_KHR
            #include <vulkan/vulkan.h>
        #endif
    #elif WLFW_UNIX_WINDOW_PLATFORM_WAYLAND
        #ifdef WLFW_CONTEXT_OPENGL

        #elif WLFW_CONTEXT_VULKAN
            #define VK_USE_PLATFORM_WAYLAND_KHR
            #include <vulkan/vulkan.h>
        #endif
    #endif
#endif

namespace wl {
    ////////////////////////////////////////////////////////////
    /// \brief Context Class
    ///
    ////////////////////////////////////////////////////////////
    class WLFW_API Context {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Context Constructor
        ///
        ////////////////////////////////////////////////////////////
        Context();

        ////////////////////////////////////////////////////////////
        /// \brief Context Destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~Context() = default;

        #ifdef WLFW_CONTEXT_OPENGL
            ////////////////////////////////////////////////////////////
            /// \brief Context Get OpenGL Context Function
            ///
            ////////////////////////////////////////////////////////////
        
        #elif WLFW_CONTEXT_VULKAN
            ////////////////////////////////////////////////////////////
            /// \brief Context Get Vulkan Instance Extensions Function
            ///
            ////////////////////////////////////////////////////////////
            virtual std::vector<const char*>& GetExtensions();

            ////////////////////////////////////////////////////////////
            /// \brief Context Create Vulkan Surface KHR Function
            ///
            ////////////////////////////////////////////////////////////
            virtual VkSurfaceKHR& CreateSurface(VkInstance instance, const Window& window);
        #endif

    private:
        #ifdef WLFW_CONTEXT_OPENGL
        
        #elif WLFW_CONTEXT_VULKAN
            std::vector<const char*> m_extensions;
            VkSurfaceKHR m_surface;
        #endif

    };
};

#endif