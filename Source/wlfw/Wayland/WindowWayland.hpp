#pragma once
#ifndef WLFW_WINDOW_WAYLAND_HEADER
#define WLFW_WINDOW_WAYLAND_HEADER

#include "../NativeWindow.hpp"

#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

#include "xdg-shell-client-protocol.hpp"

namespace wl {
    ////////////////////////////////////////////////////////////
    /// \brief Window Wayland Class
    ///
    ////////////////////////////////////////////////////////////
    class WLFW_API WindowWayland : public NativeWindow {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief WindowWayland Constructor
        ///
        ////////////////////////////////////////////////////////////
        WindowWayland(const WindowProps& windowProps = WindowProps());

        ////////////////////////////////////////////////////////////
        /// \brief WindowWayland Destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~WindowWayland();

        ////////////////////////////////////////////////////////////
        /// \brief WindowWayland Update Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void Update();

        ////////////////////////////////////////////////////////////
        /// \brief WindowWayland Set Event Handler Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetEventHandler(const EventHandler& handler);

        ////////////////////////////////////////////////////////////
        /// \brief WindowWayland Get Display Function
        ///
        ////////////////////////////////////////////////////////////
        virtual wl_display*& GetDisplay();

        ////////////////////////////////////////////////////////////
        /// \brief WindowWayland Get Surface Function
        ///
        ////////////////////////////////////////////////////////////
        virtual wl_surface*& GetSurface();

        ////////////////////////////////////////////////////////////
        /// \brief WindowWayland Get Event Handler Function
        ///
        ////////////////////////////////////////////////////////////
        virtual EventHandler& GetEventHandler();

    private:
        static void RegistryHandleGlobal(void* data, wl_registry* registry, std::uint32_t name, const char* interface, std::uint32_t version);
        static void RegistryHandleGlobalRemove(void* data, wl_registry* registry, std::uint32_t name);

        friend void RegistryHandleGlobal(void*, wl_registry*, std::uint32_t, const char*, std::uint32_t);
        friend void RegistryHandleGlobalRemove(void*, wl_registry*, std::uint32_t);

        wl_display* m_display;
        wl_compositor* m_compositor;
        xdg_surface* m_xdgSurface;
        wl_surface* m_surface;
        wl_shm* m_shm;
        xdg_wm_base* m_xdgWmBase;
        xdg_toplevel* m_xdgToplevel;
        wl_registry* m_registry;
        wl_registry_listener m_registryListener;
        wl_buffer* m_buffer;
        EventHandler m_handler;

    };

    using Window = WindowWayland;
};

#endif