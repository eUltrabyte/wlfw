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
        XStoreName(m_display, m_window, GetWindowProps()->GetTitle().c_str());
        XSelectInput(m_display, m_window, ExposureMask | ResizeRedirectMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask);
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
            case ResizeRequest: {
                static XResizeRequestEvent& resizeRequestEvent = (XResizeRequestEvent&)m_event;
                m_handler.Invoke(WindowResizedEvent(resizeRequestEvent.width, resizeRequestEvent.height));
            } break;

            // TODO EVENT WINDOW CLOSE, CURSOR MOVE AND MOUSE SCROLLED

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

            case ButtonPress: {
                switch(m_event.xbutton.button) {
                    case Button1: {
                        m_handler.Invoke(ButtonPressedEvent(Buttons::Left));
                    } break;

                    case Button3: {
                        m_handler.Invoke(ButtonPressedEvent(Buttons::Right));
                    } break;
                }
            } break;

            case ButtonRelease: {
                switch(m_event.xbutton.button) {
                    case Button1: {
                        m_handler.Invoke(ButtonReleasedEvent(Buttons::Left));
                    } break;

                    case Button3: {
                        m_handler.Invoke(ButtonReleasedEvent(Buttons::Right));
                    } break;
                }
            } break;
        }
    }

    void WindowX11::SetEventHandler(const EventHandler& handler) {
        m_handler = handler;
    }

    Display*& WindowX11::GetDisplay() {
        return m_display;
    }
    
    Window& WindowX11::GetHINSTANCE() {
        return m_window;
    }

    EventHandler& WindowX11::GetEventHandler() {
        return m_handler;
    }
};