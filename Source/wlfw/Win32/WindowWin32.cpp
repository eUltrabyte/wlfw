#include "WindowWin32.hpp"

namespace wl {
    WindowWin32::WindowWin32(const WindowProps& windowProps)
        : NativeWindow(windowProps) {
        m_windowClass = { };
        m_hwnd = { };
        m_hinstance = GetModuleHandle(nullptr);

        m_windowClass.cbClsExtra = 0;
        m_windowClass.cbWndExtra = 0;
        m_windowClass.style = 0;

        m_windowClass.lpfnWndProc = [](HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) -> LRESULT {
            switch(message) {
                case WM_CREATE: {
                    std::cout << "create window\n";
                    ShowWindow(hwnd, 5);
                    UpdateWindow(hwnd);
                } break;

                case WM_CLOSE: {
                    std::cout << "close window\n";
                    PostQuitMessage(0);
                    DestroyWindow(hwnd);
                } break;

                default: {
                    return DefWindowProc(hwnd, message, wParam, lParam);
                }
            }
        };

        m_windowClass.hInstance = m_hinstance;
        m_windowClass.hIcon = 0;
        m_windowClass.hCursor = LoadCursor(0, IDC_ARROW);
        m_windowClass.hbrBackground = (HBRUSH)10;
        m_windowClass.lpszMenuName = nullptr;
        m_windowClass.lpszClassName = reinterpret_cast<LPCSTR>("wlfw window win32 class");

        RegisterClass(&m_windowClass);

        unsigned long windowStyles = WS_VISIBLE;
        if(GetWindowProps()->GetStyle() == Style::None) {
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

        m_hwnd = CreateWindow(m_windowClass.lpszClassName, reinterpret_cast<LPCSTR>(GetWindowProps()->GetTitle().c_str()), windowStyles, windowFixedSize.left, windowFixedSize.top, windowFixedSize.right - windowFixedSize.left, windowFixedSize.bottom - windowFixedSize.top, 0, 0, m_hinstance, nullptr);
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

    HWND& WindowWin32::GetHWND() {
        return m_hwnd;
    }
    
    HINSTANCE& WindowWin32::GetHINSTANCE() {
        return m_hinstance;
    }
};