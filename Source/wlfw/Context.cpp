#include "Context.hpp"

namespace wl {
    Context::Context() {
        #ifdef WLFW_WINDOW_PLATFORM_WIN32
            #ifdef WLFW_CONTEXT_OPENGL
                
            #elif WLFW_CONTEXT_VULKAN
                m_extensions.emplace_back("VK_KHR_surface");
                m_extensions.emplace_back("VK_KHR_win32_surface");
            #endif
        #else
            #ifdef WLFW_UNIX_WINDOW_PLATFORM_X11
                #ifdef WLFW_CONTEXT_OPENGL

                #elif WLFW_CONTEXT_VULKAN
                    m_extensions.emplace_back("VK_KHR_surface");
                    m_extensions.emplace_back("VK_KHR_xlib_surface");
                #endif
            #elif WLFW_UNIX_WINDOW_PLATFORM_XCB
                #ifdef WLFW_CONTEXT_OPENGL

                #elif WLFW_CONTEXT_VULKAN
                    m_extensions.emplace_back("VK_KHR_surface");
                    m_extensions.emplace_back("VK_KHR_xcb_surface");
                #endif
            #elif WLFW_UNIX_WINDOW_PLATFORM_WAYLAND
                #ifdef WLFW_CONTEXT_OPENGL

                #elif WLFW_CONTEXT_VULKAN
                    m_extensions.emplace_back("VK_KHR_surface");
                    m_extensions.emplace_back("VK_KHR_wayland_surface");
                #endif
            #endif
        #endif
    }

    #ifdef WLFW_CONTEXT_OPENGL
        
    #elif WLFW_CONTEXT_VULKAN
        std::vector<const char*>& Context::GetExtensions() {
            return m_extensions;
        }

        VkSurfaceKHR& Context::CreateSurface(VkInstance instance, const Window& window) {
            #ifdef WLFW_WINDOW_PLATFORM_WIN32
                #ifdef WLFW_CONTEXT_OPENGL
                    
                #elif WLFW_CONTEXT_VULKAN
                    VkWin32SurfaceCreateInfoKHR win32SurfaceCreateInfo { };
                    win32SurfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
                    win32SurfaceCreateInfo.pNext = nullptr;
                    win32SurfaceCreateInfo.flags = 0;
                    win32SurfaceCreateInfo.hinstance = window.GetHINSTANCE();
                    win32SurfaceCreateInfo.hwnd = window.GetHWND();

                    vkCreateWin32SurfaceKHR(instance, &win32SurfaceCreateInfo, nullptr, &m_surface);
                #endif
            #else
                #ifdef WLFW_UNIX_WINDOW_PLATFORM_X11
                    #ifdef WLFW_CONTEXT_OPENGL

                    #elif WLFW_CONTEXT_VULKAN
                        VkXlibSurfaceCreateInfoKHR xlibSurfaceCreateInfo { };
                        xlibSurfaceCreateInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
                        xlibSurfaceCreateInfo.pNext = nullptr;
                        xlibSurfaceCreateInfo.flags = 0;
                        xlibSurfaceCreateInfo.dpy = window.GetDisplay();
                        xlibSurfaceCreateInfo.window = window.GetWindow();

                        vkCreateXlibSurfaceKHR(instance, &xlibSurfaceCreateInfo, nullptr, &m_surface);
                    #endif
                #elif WLFW_UNIX_WINDOW_PLATFORM_XCB
                    #ifdef WLFW_CONTEXT_OPENGL

                    #elif WLFW_CONTEXT_VULKAN
                        VkXcbSurfaceCreateInfoKHR xcbSurfaceCreateInfo { };
                        xcbSurfaceCreateInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
                        xcbSurfaceCreateInfo.pNext = nullptr;
                        xcbSurfaceCreateInfo.flags = 0;
                        xcbSurfaceCreateInfo.connection = window.GetConnection();
                        xcbSurfaceCreateInfo.window = window.GetWindow();

                        vkCreateXcbSurfaceKHR(instance, &xcbSurfaceCreateInfo, nullptr, &m_surface);
                    #endif
                #elif WLFW_UNIX_WINDOW_PLATFORM_WAYLAND
                    #ifdef WLFW_CONTEXT_OPENGL

                    #elif WLFW_CONTEXT_VULKAN
                        VkWaylandSurfaceCreateInfoKHR waylandSurfaceCreateInfo { };
                        waylandSurfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
                        waylandSurfaceCreateInfo.pNext = nullptr;
                        waylandSurfaceCreateInfo.flags = 0;
                        waylandSurfaceCreateInfo.display = window.GetDisplay();
                        waylandSurfaceCreateInfo.surface = window.GetSurface();

                        vkCreateWaylandSurfaceKHR(instance, &waylandSurfaceCreateInfo, nullptr, &m_surface);
                    #endif
                #endif
            #endif

            return m_surface;
        }
    #endif
};