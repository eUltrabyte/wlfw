#include "WindowXCB.hpp"

namespace wl {
    WindowXCB::WindowXCB(const WindowProps& windowProps)
        : NativeWindow(windowProps) {
        m_connection = nullptr;
        m_window = { };
        m_handler = { };

        m_connection = xcb_connect(0, 0);
        xcb_setup_t* setup = xcb_get_setup(m_connection);
        xcb_screen_iterator_t screenIterator = xcb_setup_roots_iterator(setup);
        xcb_screen_t* screen = screenIterator.data;

        m_window = xcb_generate_id(m_connection);
        xcb_create_window(m_connection, XCB_COPY_FROM_PARENT, m_window, screen->root, 0, 0, GetWindowProps()->GetWidth(), GetWindowProps()->GetHeight(), 10, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, 0, 0);
        xcb_change_property(m_connection, XCB_PROP_MODE_REPLACE, m_window, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, GetWindowProps()->GetTitle().size(), GetWindowProps()->GetTitle().data());
        xcb_map_window(m_connection, m_window);
        xcb_flush(m_connection);
    }

    WindowXCB::~WindowXCB() {
        xcb_disconnect(m_connection);
    }

    void WindowXCB::Update() {
        static unsigned int key;

        // TODO Implement Events
    }

    void WindowXCB::SetEventHandler(const EventHandler& handler) {
        m_handler = handler;
    }

    xcb_connection_t*& WindowXCB::GetConnection() {
        return m_connection;
    }
    
    xcb_window_t& WindowXCB::GetWindow() {
        return m_window;
    }

    EventHandler& WindowXCB::GetEventHandler() {
        return m_handler;
    }
};