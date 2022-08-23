#include "WindowWin32.hpp"

namespace wl {
    WindowWin32::WindowWin32() {
        m_hwnd = { };
        m_hinstance = GetModuleHandle(nullptr);

        WNDCLASS windowClassEx { };
        windowClassEx.cbClsExtra = 0;
        windowClassEx.cbWndExtra = 0;
        windowClassEx.style = 0;

        windowClassEx.lpfnWndProc = [](HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) -> LRESULT {
            switch(message) {
                case WM_CREATE: {
                    std::cout << "create window\n";
                    ShowWindow(hwnd, 5);
                    UpdateWindow(hwnd);
                } break;

                case WM_CLOSE: {
                    std::cout << "close window\n";
                } break;

                default: {
                    return DefWindowProc(hwnd, message, wParam, lParam);
                }
            }
        };

        windowClassEx.hInstance = m_hinstance;
        windowClassEx.hIcon = 0;
        windowClassEx.hCursor = LoadCursor(0, IDC_ARROW);
        windowClassEx.hbrBackground  =(HBRUSH)10;
        windowClassEx.lpszMenuName = nullptr;
        windowClassEx.lpszClassName = reinterpret_cast<LPCSTR>("wlfw window win32 class");

        WLFW_CHECK(RegisterClass(&windowClassEx));

        m_hwnd = CreateWindow(windowClassEx.lpszClassName, reinterpret_cast<LPCSTR>("wlfw window win32"), WS_OVERLAPPEDWINDOW, 0, 0, m_windowProps->GetWidth(), m_windowProps->GetHeight(), 0, 0, m_hinstance, nullptr);
        WLFW_CHECK(m_hwnd);
    }
    
    WindowWin32::~WindowWin32() {
        DestroyWindow(m_hwnd);
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