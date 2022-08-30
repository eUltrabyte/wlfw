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

        RECT windowFixedSize;
        windowFixedSize.left = 50;
        windowFixedSize.top = 50;
        windowFixedSize.right = 50 + GetWindowProps()->GetWidth();
        windowFixedSize.bottom = 50 + GetWindowProps()->GetHeight();

        AdjustWindowRect(&windowFixedSize, GetWindowProps()->GetStyle(), 0);

        m_hwnd = CreateWindow(m_windowClass.lpszClassName, reinterpret_cast<LPCSTR>(GetWindowProps()->GetTitle().c_str()), GetWindowProps()->GetStyle(), windowFixedSize.left, windowFixedSize.top, windowFixedSize.right - windowFixedSize.left, windowFixedSize.bottom - windowFixedSize.top, 0, 0, m_hinstance, nullptr);
        WLFW_CHECK(m_hwnd);
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