#pragma once
#ifndef WLFW_WINDOW_WIN32_HEADER
#define WLFW_WINDOW_WIN32_HEADER

#include "../NativeWindow.hpp"

namespace wl {
    using WindowProc = std::function<LRESULT(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)>;

    class WLFW_API WindowWin32 : public NativeWindow {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief WindowWin32 Constructor
        ///
        ////////////////////////////////////////////////////////////
        WindowWin32();

        ////////////////////////////////////////////////////////////
        /// \brief WindowWin32 Destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~WindowWin32();

        ////////////////////////////////////////////////////////////
        /// \brief WindowWin32 Update Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void Update();

        ////////////////////////////////////////////////////////////
        /// \brief WindowWin32 GetHWND Function
        ///
        ////////////////////////////////////////////////////////////
        virtual HWND& GetHWND();

        ////////////////////////////////////////////////////////////
        /// \brief WindowWin32 GetHINSTANCE Function
        ///
        ////////////////////////////////////////////////////////////
        virtual HINSTANCE& GetHINSTANCE();

    private:
        HWND m_hwnd;
        HINSTANCE m_hinstance;

    };

    using Window = WindowWin32;
};

#endif