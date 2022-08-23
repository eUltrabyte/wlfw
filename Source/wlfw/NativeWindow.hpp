#pragma once
#ifndef WLFW_NATIVE_WINDOW_HEADER
#define WLFW_NATIVE_WINDOW_HEADER

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
        ////////////////////////////////////////////////////////////
        /// \brief Window Props Constructor
        ///
        ////////////////////////////////////////////////////////////
        WindowProps(const std::string_view& title = "wlfw window", unsigned int width = 800, unsigned int height = 500, unsigned int style = Style::Default)
            : m_title(title), m_width(width), m_height(height), m_style(style) { }

        ////////////////////////////////////////////////////////////
        /// \brief Window Props Destructor
        ///
        ////////////////////////////////////////////////////////////
        ~WindowProps() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Window Props Set Title Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetTitle(const std::string_view& title) {
            m_title = title;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Window Props Set Width Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetWidth(unsigned int width) {
            m_width = width;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Window Props Set Height Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetHeight(unsigned int height) {
            m_height = height;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Window Props Set Style Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetStyle(unsigned int style) {
            m_style = style;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Window Props Get Title Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::string& GetTitle() {
            return m_title;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Window Props Get Width Function
        ///
        ////////////////////////////////////////////////////////////
        virtual unsigned int& GetWidth() {
            return m_width;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Window Props Get Height Function
        ///
        ////////////////////////////////////////////////////////////
        virtual unsigned int& GetHeight() {
            return m_height;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Window Props Get Style Function
        ///
        ////////////////////////////////////////////////////////////
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
        ////////////////////////////////////////////////////////////
        /// \brief NativeWindow Constructor
        ///
        ////////////////////////////////////////////////////////////
        NativeWindow(const WindowProps& windowProps = WindowProps());

        ////////////////////////////////////////////////////////////
        /// \brief NativeWindow Constructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~NativeWindow() = default;

        ////////////////////////////////////////////////////////////
        /// \brief NativeWindow Set Window Props Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetWindowProps(const WindowProps& windowProps);
        
        ////////////////////////////////////////////////////////////
        /// \brief NativeWindow Get Window Props Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::shared_ptr<WindowProps>& GetWindowProps();

    protected:
        std::shared_ptr<WindowProps> m_windowProps;

    };
};

#endif