#include "WindowXCB.hpp"

namespace wl {
    WindowXCB::WindowXCB(const WindowProps& windowProps)
        : NativeWindow(windowProps) {
        m_connection = nullptr;
        m_window = { };
        m_event = nullptr;
        m_handler = { };

        m_connection = xcb_connect(0, 0);
        const xcb_setup_t* setup = xcb_get_setup(m_connection);
        xcb_screen_iterator_t screenIterator = xcb_setup_roots_iterator(setup);
        xcb_screen_t* screen = screenIterator.data;

        unsigned int flags[2] = { screen->black_pixel, XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION | XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_LEAVE_WINDOW | XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE };

        m_window = xcb_generate_id(m_connection);
        xcb_create_window(m_connection, XCB_COPY_FROM_PARENT, m_window, screen->root, 0, 0, GetWindowProps()->GetWidth(), GetWindowProps()->GetHeight(), 10, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, XCB_CW_EVENT_MASK, flags);
        xcb_change_property(m_connection, XCB_PROP_MODE_REPLACE, m_window, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, GetWindowProps()->GetTitle().size(), GetWindowProps()->GetTitle().data());
        xcb_map_window(m_connection, m_window);
        xcb_flush(m_connection);
    }

    WindowXCB::~WindowXCB() {
        xcb_disconnect(m_connection);
    }

    void WindowXCB::Update() {
        static unsigned int key;

        m_event = xcb_wait_for_event(m_connection);
        switch(event->response_type & ~0x80) {
            // Window Closed

            // Window Resized

            // Window Moved

            // Window Gained Focus

            // Window Lost Focus

            case XCB_MOTION_NOTIFY: {
                xcb_motion_notify_event_t& motionNotifyEvent = (xcb_motion_notify_event_t&)m_event;
                m_handler.Invoke(MouseMovedEvent(motionNotifyEvent.event_x, motionNotifyEvent.event_y));
            } break;

            case XCB_BUTTON_PRESS: {
                xcb_button_press_event_t& buttonPressEvent = (xcb_button_press_event_t&)m_event;
                
                switch(buttonPressEvent.detail) {
                    case 4: { m_handler.Invoke(MouseScrolledEvent(true, 1)); } break;
                    case 5: { m_handler.Invoke(MouseScrolledEvent(true, -1)); } break;
                    default: { m_handler.Invoke(ButtonPressedEvent(buttonPressEvent.detail)); } break;
                }
            } break;

            case XCB_BUTTON_RELEASE: {
                xcb_button_release_event_t& buttonReleaseEvent = (xcb_button_release_event_t&)m_event;
                
                switch(buttonPressEvent.detail) {
                    case 4: { m_handler.Invoke(MouseScrolledEvent(false, 1)); } break;
                    case 5: { m_handler.Invoke(MouseScrolledEvent(false, -1)); } break;
                    default: { m_handler.Invoke(ButtonReleasedEvent(buttonPressEvent.detail)); } break;
                }
            } break;

            case XCB_KEY_PRESS: {
                xcb_key_press_event_t& keyPressEvent = (xcb_key_press_event_t&)m_event;
                
                if(key != keyPressEvent.detail) {
                    m_handler.Invoke(KeyPressedEvent(keyPressEvent.detail));
                } else {
                    m_handler.Invoke(KeyRepeatedEvent(keyPressEvent.detail));
                }

                key = keyPressEvent.detail;
            } break;

            case XCB_KEY_RELEASE: {
                key = 0;
                xcb_key_release_event_t& keyReleaseEvent = (xcb_key_release_event_t&)m_event;
                m_handler.Invoke(KeyReleasedEvent(keyReleaseEvent.detail));
            } break;
        }
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