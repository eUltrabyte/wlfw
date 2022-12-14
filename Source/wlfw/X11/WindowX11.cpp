#include "WindowX11.hpp"

namespace wl {
    WindowX11::WindowX11(const WindowProps& windowProps)
        : NativeWindow(windowProps) {
        m_display = nullptr;
        m_window = { };
        m_event = { };
        m_handler = { };

        m_display = XOpenDisplay(nullptr);
        m_window = XCreateSimpleWindow(m_display, RootWindow(m_display, DefaultScreen(m_display)), 0, 0, GetWindowProps()->GetWidth(), GetWindowProps()->GetHeight(), 0, 0, 0);
        WLFW_CHECK(m_window);
        
        XStoreName(m_display, m_window, GetWindowProps()->GetTitle().c_str());
        XSelectInput(m_display, m_window, ExposureMask | ResizeRedirectMask | FocusChangeMask | StructureNotifyMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask);
        
        m_wmDeleteMessage = XInternAtom(m_display, "WM_DELETE_WINDOW", false);
        XSetWMProtocols(m_display, m_window, &m_wmDeleteMessage, 1);

        XMapWindow(m_display, m_window);
    }

    WindowX11::~WindowX11() {
        XDestroyWindow(m_display, m_window);
        XCloseDisplay(m_display);
    }

    void WindowX11::Update() {
        static unsigned int key;

        XNextEvent(m_display, &m_event);
        switch(m_event.type) {
            case ClientMessage: {
                if(m_event.xclient.data.l[0] == m_wmDeleteMessage) {
                    m_handler.Invoke(WindowClosedEvent());
                }
            } break;
            
            case ConfigureNotify: {
                XConfigureEvent& configureEvent = (XConfigureEvent&)m_event;
                if(configureEvent.width != GetWindowProps()->GetWidth() || configureEvent.height != GetWindowProps()->GetHeight()) {
                    GetWindowProps()->SetWidth(configureEvent.width);
                    GetWindowProps()->SetHeight(configureEvent.height);
                    m_handler.Invoke(WindowResizedEvent(configureEvent.width, configureEvent.height));
                }

                m_handler.Invoke(WindowMovedEvent(configureEvent.x, configureEvent.y));
            } break;
        
            case FocusIn: {
                m_handler.Invoke(WindowGainedFocusEvent());
            } break;
        
            case FocusOut: {
                m_handler.Invoke(WindowLostFocusEvent());
            } break;

            case MotionNotify: {
                XMotionEvent& motionEvent = (XMotionEvent&)m_event;
                m_handler.Invoke(MouseMovedEvent(motionEvent.x, motionEvent.y));
            } break;

            case ButtonPress: {
                switch(m_event.xbutton.button) {
                    case Button1: {
                        m_handler.Invoke(ButtonPressedEvent(Buttons::Left));
                    } break;

                    case Button2: {
                        m_handler.Invoke(ButtonPressedEvent(Buttons::Middle));
                    } break;

                    case Button3: {
                        m_handler.Invoke(ButtonPressedEvent(Buttons::Right));
                    } break;

                    case Button4: {
                        m_handler.Invoke(MouseScrolledEvent(true, 1));
                    } break;

                    case Button5: {
                        m_handler.Invoke(MouseScrolledEvent(true, 0));
                    } break;
                }
            } break;

            case ButtonRelease: {
                switch(m_event.xbutton.button) {
                    case Button1: {
                        m_handler.Invoke(ButtonReleasedEvent(Buttons::Left));
                    } break;

                    case Button2: {
                        m_handler.Invoke(ButtonReleasedEvent(Buttons::Middle));
                    } break;

                    case Button3: {
                        m_handler.Invoke(ButtonReleasedEvent(Buttons::Right));
                    } break;

                    case Button4: {
                        m_handler.Invoke(MouseScrolledEvent(false, 1));
                    } break;

                    case Button5: {
                        m_handler.Invoke(MouseScrolledEvent(false, 0));
                    } break;
                }
            } break;

            case KeyPress: {
                if(key != m_event.xkey.keycode) {
                    m_handler.Invoke(KeyPressedEvent(m_event.xkey.keycode));
                } else {
                    m_handler.Invoke(KeyRepeatedEvent(m_event.xkey.keycode));
                }

                key = m_event.xkey.keycode;
            } break;

            case KeyRelease: {
                key = 0;
                m_handler.Invoke(KeyReleasedEvent(m_event.xkey.keycode));
            } break;
        }
    }

    void WindowX11::SetEventHandler(const EventHandler& handler) {
        m_handler = handler;
    }

    Display*& WindowX11::GetDisplay() {
        return m_display;
    }
    
    ::Window& WindowX11::GetWindow() {
        return m_window;
    }

    EventHandler& WindowX11::GetEventHandler() {
        return m_handler;
    }
};