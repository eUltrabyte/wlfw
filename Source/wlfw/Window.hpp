#pragma once
#ifndef WLFW_WINDOW_HEADER
#define WLFW_WINDOW_HEADER

#include "wlfw.hpp"

namespace wl {
    enum WLFW_API Style {
        None = 0,
        Titlebar = WLFW_BYTE(0),
        Minimize = WLFW_BYTE(1),
        Maximize = WLFW_BYTE(2),
        Fullscreen = WLFW_BYTE(3),
        Close = WLFW_BYTE(4),
        Default = WLFW_BYTE(0) | WLFW_BYTE(2) | WLFW_BYTE(4),
    };

    struct WLFW_API WindowProps {
    public:
        WindowProps(const std::string_view& title = "wlfw window", unsigned int width = 800, unsigned int height = 500, unsigned int style = Style::Default)
            : m_title(title), m_width(width), m_height(height), m_style(style) { }

        ~WindowProps() = default;

        virtual void SetTitle(const std::string_view& title) {
            m_title = title;
        }

        virtual void SetWidth(unsigned int width) {
            m_width = width;
        }

        virtual void SetHeight(unsigned int height) {
            m_height = height;
        }

        virtual void SetStyle(unsigned int style) {
            m_style = style;
        }

        virtual std::string& GetTitle() {
            return m_title;
        }

        virtual unsigned int& GetWidth() {
            return m_width;
        }

        virtual unsigned int& GetHeight() {
            return m_height;
        }

        virtual unsigned int& GetStyle() {
            return m_style;
        }
    
    private:
        std::string m_title;
        unsigned int m_width;
        unsigned int m_height;
        unsigned int m_style;

    };

    class WLFW_API NativeWindow {
    public:
        NativeWindow(const WindowProps& windowProps = WindowProps());
        virtual ~NativeWindow() = default;

        virtual void SetWindowProps(const WindowProps& windowProps);
        
        virtual std::shared_ptr<WindowProps>& GetWindowProps();

    private:
        std::shared_ptr<WindowProps> m_windowProps;

    };
};

#endif