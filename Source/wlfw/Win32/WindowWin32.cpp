#include "WindowWin32.hpp"

namespace wl {
    int ConvertWin32KeyToFixedKey(int key) {
        static unsigned int fixedKey = key;

        switch(key) {
            case 81: { fixedKey = Keys::Q; } break;
            case 87: { fixedKey = Keys::W; } break;
            case 69: { fixedKey = Keys::E; } break;
            case 82: { fixedKey = Keys::R; } break;
            case 84: { fixedKey = Keys::T; } break;
            case 89: { fixedKey = Keys::Y; } break;
            case 85: { fixedKey = Keys::U; } break;
            case 73: { fixedKey = Keys::I; } break;
            case 79: { fixedKey = Keys::O; } break;
            case 80: { fixedKey = Keys::P; } break;
            case 65: { fixedKey = Keys::A; } break;
            case 83: { fixedKey = Keys::S; } break;
            case 68: { fixedKey = Keys::D; } break;
            case 70: { fixedKey = Keys::F; } break;
            case 71: { fixedKey = Keys::G; } break;
            case 72: { fixedKey = Keys::H; } break;
            case 74: { fixedKey = Keys::J; } break;
            case 75: { fixedKey = Keys::K; } break;
            case 76: { fixedKey = Keys::L; } break;
            case 90: { fixedKey = Keys::Z; } break;
            case 88: { fixedKey = Keys::X; } break;
            case 67: { fixedKey = Keys::C; } break;
            case 86: { fixedKey = Keys::V; } break;
            case 66: { fixedKey = Keys::B; } break;
            case 78: { fixedKey = Keys::N; } break;
            case 77: { fixedKey = Keys::M; } break;

            case 27: { fixedKey = Keys::Escape; } break;
            case 192: { fixedKey = Keys::GraveAccent; } break;
            case 9: { fixedKey = Keys::Tab; } break;
            case 20: { fixedKey = Keys::CapsLock; } break;
            case 16: { fixedKey = Keys::Shift; } break;
            case 17: { fixedKey = Keys::RightControl; } break;

            case 48: { fixedKey = Keys::Zero; } break;
            case 49: { fixedKey = Keys::One; } break;
            case 50: { fixedKey = Keys::Two; } break;
            case 51: { fixedKey = Keys::Three; } break;
            case 52: { fixedKey = Keys::Four; } break;
            case 53: { fixedKey = Keys::Five; } break;
            case 54: { fixedKey = Keys::Six; } break;
            case 55: { fixedKey = Keys::Seven; } break;
            case 56: { fixedKey = Keys::Eight; } break;
            case 57: { fixedKey = Keys::Nine; } break;

            default: { fixedKey = key; } break;
        }

        // TODO OTHER KEYS

        return fixedKey;
    }

    WindowWin32::WindowWin32(const WindowProps& windowProps)
        : NativeWindow(windowProps) {
        m_windowClass = { };
        m_hinstance = GetModuleHandle(nullptr);
        m_hwnd = { };
        m_handler = { };

        m_windowClass.cbClsExtra = 0;
        m_windowClass.cbWndExtra = 0;
        m_windowClass.style = 0;

        m_windowClass.lpfnWndProc = [](HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) -> LRESULT {
            WindowWin32* window;
            if(message == WM_NCCREATE) {
                LPCREATESTRUCT createStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
                window = static_cast<WindowWin32*>(createStruct->lpCreateParams);
                window->GetHWND() = hwnd;
                SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
            } else {
                window = reinterpret_cast<WindowWin32*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            }

            if(window) {
                return window->GetWindowProc(hwnd, message, wParam, lParam);
            }

            return DefWindowProc(hwnd, message, wParam, lParam);
        };

        m_windowClass.hInstance = m_hinstance;
        m_windowClass.hIcon = 0;
        m_windowClass.hCursor = LoadCursor(0, IDC_ARROW);
        m_windowClass.hbrBackground = (HBRUSH)10;
        m_windowClass.lpszMenuName = nullptr;
        m_windowClass.lpszClassName = reinterpret_cast<LPCSTR>("wlfw window win32 class");

        RegisterClass(&m_windowClass);

        unsigned long windowStyles = WS_VISIBLE;
        if(GetWindowProps()->GetStyle() == Style::Null) {
            windowStyles |= WS_POPUP;
        } else {
            if(GetWindowProps()->GetStyle() & Style::Titlebar) {
                windowStyles |= WS_CAPTION;
            }

            if(GetWindowProps()->GetStyle() & Style::Minimize) {
                windowStyles |= WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU;
            }

            if(GetWindowProps()->GetStyle() & Style::Maximize) {
                windowStyles |= WS_THICKFRAME | WS_MAXIMIZEBOX | WS_SYSMENU;
            }

            if(GetWindowProps()->GetStyle() & Style::Close) {
                windowStyles |= WS_SYSMENU;
            }
        }

        RECT windowFixedSize;
        windowFixedSize.left = 50;
        windowFixedSize.top = 50;
        windowFixedSize.right = 50 + GetWindowProps()->GetWidth();
        windowFixedSize.bottom = 50 + GetWindowProps()->GetHeight();

        AdjustWindowRect(&windowFixedSize, windowStyles, 0);

        m_hwnd = CreateWindow(m_windowClass.lpszClassName, reinterpret_cast<LPCSTR>(GetWindowProps()->GetTitle().c_str()), windowStyles, windowFixedSize.left, windowFixedSize.top, windowFixedSize.right - windowFixedSize.left, windowFixedSize.bottom - windowFixedSize.top, 0, 0, m_hinstance, this);
        WLFW_CHECK(m_hwnd);

        if(GetWindowProps()->GetStyle() & Style::Fullscreen) {
            DEVMODE devMode { };
            devMode.dmSize = sizeof(devMode);
            devMode.dmPelsWidth = GetWindowProps()->GetWidth();
            devMode.dmPelsHeight = GetWindowProps()->GetHeight();
            devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

            ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);

            SetWindowLongPtr(m_hwnd, GWL_STYLE, static_cast<LONG_PTR>(WS_POPUP) | static_cast<LONG_PTR>(WS_CLIPCHILDREN) | static_cast<LONG_PTR>(WS_CLIPSIBLINGS));
            SetWindowLongPtr(m_hwnd, GWL_EXSTYLE, WS_EX_APPWINDOW);
            SetWindowPos(m_hwnd, HWND_TOP, 0, 0, devMode.dmPelsWidth, devMode.dmPelsHeight, SWP_FRAMECHANGED);
            ShowWindow(m_hwnd, 5);
        }
    }
    
    WindowWin32::~WindowWin32() {
        DestroyWindow(m_hwnd);
        UnregisterClass(m_windowClass.lpszClassName, m_hinstance);
    }

    void WindowWin32::Update() {
        MSG message;
        if(PeekMessage(&message, 0, 0, 0, 0)) {
            GetMessage(&message, 0, 0, 0);
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }

    void WindowWin32::SetEventHandler(const EventHandler& handler) {
        m_handler = handler;
    }

    LRESULT WindowWin32::GetWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
        static unsigned int key;

        switch(message) {
            case WM_CREATE: {
                ShowWindow(hwnd, 5);
                UpdateWindow(hwnd);
            } break;

            case WM_DESTROY: {
                PostQuitMessage(0);
                DestroyWindow(hwnd);
            } break;

            case WM_CLOSE: {
                m_handler.Invoke(WindowClosedEvent());
                PostQuitMessage(0);
                DestroyWindow(hwnd);
            } break;

            case WM_SIZE: {
                GetWindowProps()->SetWidth(LOWORD(lParam));
                GetWindowProps()->SetHeight(HIWORD(lParam));
                m_handler.Invoke(WindowResizedEvent(LOWORD(lParam), HIWORD(lParam)));
            } break;

            case WM_MOVE: {
                m_handler.Invoke(WindowMovedEvent(LOWORD(lParam), HIWORD(lParam)));
            } break;

            case WM_SETFOCUS: {
                m_handler.Invoke(WindowGainedFocusEvent());
            } break;

            case WM_KILLFOCUS: {
                m_handler.Invoke(WindowLostFocusEvent());
            } break;

            case WM_MOUSEWHEEL: {
                m_handler.Invoke(MouseScrolledEvent(((GET_KEYSTATE_WPARAM(wParam) == 16) ? true : false), ((GET_WHEEL_DELTA_WPARAM(wParam) < 0) ? -1 : 1)));
            } break;

            case WM_MOUSEMOVE: {
                m_handler.Invoke(MouseMovedEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
            } break;

            case WM_LBUTTONDOWN: {
                m_handler.Invoke(ButtonPressedEvent(Buttons::Left));
            } break;

            case WM_MBUTTONDOWN: {
                m_handler.Invoke(ButtonPressedEvent(Buttons::Middle));
            } break;

            case WM_RBUTTONDOWN: {
                m_handler.Invoke(ButtonPressedEvent(Buttons::Right));
            } break;

            case WM_LBUTTONUP: {
                m_handler.Invoke(ButtonReleasedEvent(Buttons::Left));
            } break;

            case WM_MBUTTONUP: {
                m_handler.Invoke(ButtonReleasedEvent(Buttons::Middle));
            } break;

            case WM_RBUTTONUP: {
                m_handler.Invoke(ButtonReleasedEvent(Buttons::Right));
            } break;

            case WM_KEYDOWN: {
                if(key != wParam) {
                    m_handler.Invoke(KeyPressedEvent(ConvertWin32KeyToFixedKey(wParam)));
                } else {
                    m_handler.Invoke(KeyRepeatedEvent(ConvertWin32KeyToFixedKey(wParam)));
                }
                key = wParam;
            } break;

            case WM_KEYUP: {
                key = 0;
                m_handler.Invoke(KeyReleasedEvent(ConvertWin32KeyToFixedKey(wParam)));
            } break;

            default: {
                return DefWindowProc(hwnd, message, wParam, lParam);
            }
        }
    }
    
    HWND& WindowWin32::GetHWND() {
        return m_hwnd;
    }
    
    HINSTANCE& WindowWin32::GetHINSTANCE() {
        return m_hinstance;
    }

    EventHandler& WindowWin32::GetEventHandler() {
        return m_handler;
    }
};