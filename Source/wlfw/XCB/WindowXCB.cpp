#include "WindowXCB.hpp"
 
namespace wl {
    WindowXCB::WindowXCB(const WindowProps& windowProps)
        : NativeWindow(windowProps) {
        m_connection = nullptr;
        m_window = { };
        m_event = nullptr;
        m_wmDeleteWindow = nullptr;
        m_handler = { };
 
        m_connection = xcb_connect(0, 0);
        xcb_screen_t* screen = xcb_setup_roots_iterator(xcb_get_setup(m_connection)).data;
 
        unsigned int flags[2] = { screen->black_pixel, XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_STRUCTURE_NOTIFY | XCB_EVENT_MASK_FOCUS_CHANGE  | XCB_EVENT_MASK_POINTER_MOTION | XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE };
 
        m_window = xcb_generate_id(m_connection);
        xcb_void_cookie_t cookie = xcb_create_window(m_connection, XCB_COPY_FROM_PARENT, m_window, screen->root, 0, 0, GetWindowProps()->GetWidth(), GetWindowProps()->GetHeight(), 0, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK, flags);
        WLFW_CHECK(m_window);
        
        xcb_change_property(m_connection, XCB_PROP_MODE_REPLACE, m_window, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, GetWindowProps()->GetTitle().size(), GetWindowProps()->GetTitle().data());
 
        xcb_intern_atom_cookie_t atomCookieProtocols = xcb_intern_atom(m_connection, 1, 12, "WM_PROTOCOLS");
        xcb_intern_atom_reply_t* atomReplyProtocols = xcb_intern_atom_reply(m_connection, atomCookieProtocols, 0);
 
        xcb_intern_atom_cookie_t atomCookieDeleteWindow = xcb_intern_atom(m_connection, 0, 16, "WM_DELETE_WINDOW");
        m_wmDeleteWindow = xcb_intern_atom_reply(m_connection, atomCookieDeleteWindow, 0);
 
        xcb_change_property(m_connection, XCB_PROP_MODE_REPLACE, m_window, atomReplyProtocols->atom, 4, 32, 1, &m_wmDeleteWindow->atom);
 
        xcb_map_window(m_connection, m_window);
        xcb_flush(m_connection);
    }
 
    WindowXCB::~WindowXCB() {
        xcb_destroy_window(m_connection, m_window);
        xcb_disconnect(m_connection);
    }
 
    void WindowXCB::Update() {
        static unsigned int key;
 
        m_event = xcb_wait_for_event(m_connection);
        switch(m_event->response_type & ~0x80) {
            case XCB_CLIENT_MESSAGE: {
                xcb_client_message_event_t* clientMessageEvent = (xcb_client_message_event_t*)m_event;
                if(clientMessageEvent->data.data32[0] == m_wmDeleteWindow->atom) {
                    m_handler.Invoke(WindowClosedEvent());
                }
            } break;
 
            case XCB_CONFIGURE_NOTIFY: {
                xcb_configure_notify_event_t* configureNotifyEvent = (xcb_configure_notify_event_t*)m_event;
                if(configureNotifyEvent->width != GetWindowProps()->GetWidth() || configureNotifyEvent->height != GetWindowProps()->GetHeight()) {
                    GetWindowProps()->SetWidth(configureNotifyEvent->width);
                    GetWindowProps()->SetHeight(configureNotifyEvent->height);
                    m_handler.Invoke(WindowResizedEvent(configureNotifyEvent->width, configureNotifyEvent->height));
                }

                m_handler.Invoke(WindowMovedEvent(configureNotifyEvent->x, configureNotifyEvent->y));
            } break;
 
            case XCB_FOCUS_IN: {
                m_handler.Invoke(WindowGainedFocusEvent());
            } break;
 
            case XCB_FOCUS_OUT: {
                m_handler.Invoke(WindowLostFocusEvent());
            } break;
 
            case XCB_MOTION_NOTIFY: {
                xcb_motion_notify_event_t* motionNotifyEvent = (xcb_motion_notify_event_t*)m_event;
                m_handler.Invoke(MouseMovedEvent(motionNotifyEvent->event_x, motionNotifyEvent->event_y));
            } break;
 
            case XCB_BUTTON_PRESS: {
                xcb_button_press_event_t* buttonPressEvent = (xcb_button_press_event_t*)m_event;
 
                switch(buttonPressEvent->detail) {
                    case 1: {
                        m_handler.Invoke(ButtonPressedEvent(Buttons::Left));
                    } break;
 
                    case 2: {
                        m_handler.Invoke(ButtonPressedEvent(Buttons::Middle));
                    } break;
 
                    case 3: {
                        m_handler.Invoke(ButtonPressedEvent(Buttons::Right));
                    } break;
 
                    case 4: {
                        m_handler.Invoke(MouseScrolledEvent(true, 1));
                    } break;
 
                    case 5: {
                        m_handler.Invoke(MouseScrolledEvent(true, -1));
                    } break;
                }
            } break;
 
            case XCB_BUTTON_RELEASE: {
                xcb_button_release_event_t* buttonReleaseEvent = (xcb_button_release_event_t*)m_event;
 
                switch(buttonReleaseEvent->detail) {
                    case 1: {
                        m_handler.Invoke(ButtonReleasedEvent(Buttons::Left));
                    } break;
 
                    case 2: {
                        m_handler.Invoke(ButtonReleasedEvent(Buttons::Middle));
                    } break;
 
                    case 3: {
                        m_handler.Invoke(ButtonReleasedEvent(Buttons::Right));
                    } break;
 
                    case 4: {
                        m_handler.Invoke(MouseScrolledEvent(false, 1));
                    } break;
 
                    case 5: {
                        m_handler.Invoke(MouseScrolledEvent(false, -1));
                    } break;
                }
            } break;
 
            case XCB_KEY_PRESS: {
                xcb_key_press_event_t* keyPressEvent = (xcb_key_press_event_t*)m_event;
 
                if(key != keyPressEvent->detail) {
                    m_handler.Invoke(KeyPressedEvent(keyPressEvent->detail));
                } else {
                    m_handler.Invoke(KeyRepeatedEvent(keyPressEvent->detail));
                    // TODO Fix Key Repeating
                }
 
                key = keyPressEvent->detail;
            } break;
 
            case XCB_KEY_RELEASE: {
                key = 0;
                xcb_key_release_event_t* keyReleaseEvent = (xcb_key_release_event_t*)m_event;
                m_handler.Invoke(KeyReleasedEvent(keyReleaseEvent->detail));
            } break;
        }
 
        free(m_event);
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