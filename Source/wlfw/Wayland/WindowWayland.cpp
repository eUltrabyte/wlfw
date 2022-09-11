#include "WindowWayland.hpp"
 
namespace wl {
    wl_compositor* compositor = nullptr;
    wl_shell* shell = nullptr;

    static void global_registry_handler(void* data, struct wl_registry* registry, uint32_t id, const char* interface, uint32_t version) {
        if(strcmp(interface, "wl_compositor") == 0) {
            compositor = (wl_compositor*)wl_registry_bind(registry, id, &wl_compositor_interface, 1);
        } else if (strcmp(interface, "wl_shell") == 0) {
            shell = (wl_shell*)wl_registry_bind(registry, id, &wl_shell_interface, 1);
        }
    }

    static void global_registry_remover(void* data, struct wl_registry* registry, uint32_t id) {
        printf("Got a registry losing event for %d\n", id);
    }

    static const struct wl_registry_listener registry_listener = {
        global_registry_handler,
        global_registry_remover
    };

    WindowWayland::WindowWayland(const WindowProps& windowProps)
        : NativeWindow(windowProps) {
        m_display = nullptr;
        m_compositor = nullptr;
        m_surface = nullptr;
        m_shell = nullptr;
        m_shellSurface = nullptr;
        m_handler = { };

        m_display = wl_display_connect(0);
        struct wl_registry* registry = wl_display_get_registry(m_display);
        wl_registry_add_listener(registry, &registry_listener, 0);

        wl_display_dispatch(m_display);
        wl_display_roundtrip(m_display);

        m_surface = wl_compositor_create_surface(compositor);

        m_shellSurface = wl_shell_get_shell_surface(shell, m_surface);
        wl_shell_surface_set_toplevel(m_shellSurface);
    }
 
    WindowWayland::~WindowWayland() {
        wl_display_disconnect(m_display);
    }
 
    void WindowWayland::Update() {
        
    }
 
    void WindowWayland::SetEventHandler(const EventHandler& handler) {
        m_handler = handler;
    }
 
    wl_display*& WindowWayland::GetDisplay() {
        return m_display;
    }
 
    wl_compositor*& WindowWayland::GetCompositor() {
        return m_compositor;
    }
 
    EventHandler& WindowWayland::GetEventHandler() {
        return m_handler;
    }
};