#include "WindowWayland.hpp"
 
namespace wl {
    static xdg_wm_base* xdgWmBase = nullptr;
    static xdg_toplevel* xdgTopLevel = nullptr;
    static wl_shm* shm = nullptr;
    static wl_compositor* compositor = nullptr;

    void RandomName(char* buffer) {
        struct timespec timeSpecification;
        clock_gettime(CLOCK_REALTIME, &timeSpecification);
        long x = timeSpecification.tv_nsec;
        for(int i = 0; i < 6; ++i) {
            buffer[i] = 'A' + (x & 15) + (x & 16) * 2;
            x >>= 5;
        }
    }

    int OpenShm() {
        char name[] = "/wlfw-window-XXXXXX";
        int retries = 999;
        while(retries > 0 && errno == EEXIST) {
            RandomName(name + std::strlen(name) - 6);
            --retries;
            int file = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0600);
            if(file >= 0) {
                shm_unlink(name);
                return file;
            }
        }

        return -1;
    }

    int CreateShm(long size) {
        int file = OpenShm();
        if(file < 0) {
            return file;
        }

        if(ftruncate(file, size) < 0) {
            close(file);
            return -1;
        }

        return file;
    }

    WindowWayland::WindowWayland(const WindowProps& windowProps)
        : NativeWindow(windowProps) {
        m_display = nullptr;
        m_shm = nullptr;
        m_compositor = nullptr;
        m_xdgSurface = nullptr;
        m_surface = nullptr;
        m_handler = { };

        m_display = wl_display_connect(0);
        m_registry = wl_display_get_registry(m_display);

        m_registryListener.global = RegistryHandleGlobal;
        m_registryListener.global_remove = RegistryHandleGlobalRemove;

        wl_registry_add_listener(m_registry, &m_registryListener, 0);
        wl_display_roundtrip(m_display);

        m_xdgWmBase = xdgWmBase;
        m_xdgToplevel = xdgTopLevel;
        m_shm = shm;
        m_compositor = compositor;

        m_surface = wl_compositor_create_surface(m_compositor);
        m_xdgSurface = xdg_wm_base_get_xdg_surface(m_xdgWmBase, m_surface);
        m_xdgToplevel = xdg_surface_get_toplevel(m_xdgSurface);

        int fd = CreateShm(GetWindowProps()->GetWidth() * 4 * GetWindowProps()->GetHeight());
        if(fd < 0) {
            std::cout << "buffer file creation failed : " << GetWindowProps()->GetWidth() * 4 * GetWindowProps()->GetHeight() << '\n';
        }

        void* shmData = mmap(0, GetWindowProps()->GetWidth() * 4 * GetWindowProps()->GetHeight(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if(shmData == MAP_FAILED) {
            std::cout << "mmap failed\n";
            close(fd);
        }

        wl_shm_pool* pool = wl_shm_create_pool(m_shm, fd, GetWindowProps()->GetWidth() * 4 * GetWindowProps()->GetHeight());
        m_buffer = wl_shm_pool_create_buffer(pool, 0, GetWindowProps()->GetWidth(), GetWindowProps()->GetHeight(), GetWindowProps()->GetWidth() * 4, WL_SHM_FORMAT_ARGB8888);
        wl_shm_pool_destroy(pool);

        wl_surface_commit(m_surface);
        wl_display_roundtrip(m_display);

        wl_surface_attach(m_surface, m_buffer, 0, 0);
        wl_surface_commit(m_surface);
    }
 
    WindowWayland::~WindowWayland() {
        wl_display_disconnect(m_display);
    }
 
    void WindowWayland::Update() {
        wl_display_dispatch(m_display);
    }
 
    void WindowWayland::SetEventHandler(const EventHandler& handler) {
        m_handler = handler;
    }
 
    wl_display*& WindowWayland::GetDisplay() {
        return m_display;
    }
 
    wl_surface*& WindowWayland::GetSurface() {
        return m_surface;
    }
 
    EventHandler& WindowWayland::GetEventHandler() {
        return m_handler;
    }

    static void pointer_handle_button(void* data, wl_pointer* pointer, uint32_t serial, uint32_t time, uint32_t button, uint32_t state) {
        wl_seat* seat = (wl_seat*)data;
        if(button <= 4 && state == WL_POINTER_BUTTON_STATE_PRESSED) {
            xdg_toplevel_move(xdgTopLevel, seat, serial);
        }
    }

    static const struct wl_pointer_listener pointer_listener = {
        .enter = nullptr,
        .leave = nullptr,
        .motion = nullptr,
        .button = pointer_handle_button,
        .axis = nullptr,
    };

    static void seat_handle_capabilities(void* data, wl_seat* seat, std::uint32_t capabilities) {
        if(capabilities & WL_SEAT_CAPABILITY_POINTER) {
            wl_pointer* pointer = wl_seat_get_pointer(seat);
            wl_pointer_add_listener(pointer, &pointer_listener, seat);
        }
    }

    static const struct wl_seat_listener seat_listener = {
        .capabilities = seat_handle_capabilities,
    };

    void WindowWayland::RegistryHandleGlobal(void* data, wl_registry* registry, std::uint32_t name, const char* interface, std::uint32_t version) {
        if(std::strcmp(interface, wl_shm_interface.name) == 0) {
            shm = (wl_shm*)wl_registry_bind(registry, name, &wl_shm_interface, 1);
        } else if(std::strcmp(interface, wl_seat_interface.name) == 0) {
            wl_seat* seat = (wl_seat*)wl_registry_bind(registry, name, &wl_seat_interface, 1);
            wl_seat_add_listener(seat, &seat_listener, 0);
        } else if(std::strcmp(interface, wl_compositor_interface.name) == 0) {
            compositor = (wl_compositor*)wl_registry_bind(registry, name, &wl_compositor_interface, 1);
        } else if(std::strcmp(interface, xdg_wm_base_interface.name) == 0) {
            xdgWmBase = (xdg_wm_base*)wl_registry_bind(registry, name, &xdg_wm_base_interface, 1);
        }
    }
    
    void WindowWayland::RegistryHandleGlobalRemove(void *data, wl_registry* registry, std::uint32_t name) {
        //no one cares
    }
};