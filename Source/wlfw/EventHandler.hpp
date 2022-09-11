#pragma once
#ifndef WLFW_EVENT_HANDLER_HEADER
#define WLFW_EVENT_HANDLER_HEADER

#include "wlfw.hpp"
#include "Event.hpp"

namespace wl {
    ////////////////////////////////////////////////////////////
    /// \brief Event Handler Class Which Can Invoke Every Event
    ///
    ////////////////////////////////////////////////////////////
    class WLFW_API EventHandler {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Constructor
        ///
        ////////////////////////////////////////////////////////////
        EventHandler() {
            m_windowClosedEventCallback = []() {
                std::cout << "Window Closed Event" << '\n';
            };

            m_windowResizedEventCallback = [](std::stringstream& data) {
                char junk = '0';
                int width = 0;
                int height = 0;
                data >> width >> junk >> height;
                std::cout << "Window Resized Event : " << width << " : " << height << '\n'; 
            };

            m_windowMovedEventCallback = [](std::stringstream& data) {
                char junk = '0';
                int x = 0;
                int y = 0;
                data >> x >> junk >> y;
                std::cout << "Window Moved Event : " << x << " : " << y << '\n'; 
            };

            m_windowGainedFocusEventCallback = []() {
                std::cout << "Window Gained Focus Event" << '\n';
            };

            m_windowLostFocusEventCallback = []() {
                std::cout << "Window Lost Focus Event" << '\n';
            };

            m_mouseScrolledEventCallback = [](std::stringstream& data) {
                char junk = '0';
                bool pressed = false;
                int direction = 0;
                data >> pressed >> junk >> direction;
                std::cout << "Mouse Scrolled Event : " << pressed << " : " << direction << '\n'; 
            };

            m_mouseMovedEventCallback = [](std::stringstream& data) {
                char junk = '0';
                int x = 0;
                int y = 0;
                data >> x >> junk >> y;
                std::cout << "Mouse Moved Event : " << x << " : " << y << '\n'; 
            };

            m_buttonPressedEventCallback = [](std::stringstream& data) {
                int button = 0;
                data >> button;
                std::cout << "Button Pressed Event : " << button << '\n'; 
            };

            m_buttonReleasedEventCallback = [](std::stringstream& data) {
                int button = 0;
                data >> button;
                std::cout << "Button Released Event : " << button << '\n'; 
            };

            m_keyPressedEventCallback = [](std::stringstream& data) {
                int key = 0;
                data >> key;
                std::cout << "Key Pressed Event : " << key << '\n'; 
            };

            m_keyReleasedEventCallback = [](std::stringstream& data) {
                int key = 0;
                data >> key;
                std::cout << "Key Released Event : " << key << '\n'; 
            };

            m_keyRepeatedEventCallback = [](std::stringstream& data) {
                int key = 0;
                data >> key;
                std::cout << "Key Repeated Event : " << key << '\n'; 
            };
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~EventHandler() = default;
        
        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Invoke Event Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void Invoke(const Event& event) {
            switch(event.GetEventType()) {
                case EventType::WindowClosed: { m_windowClosedEventCallback(); } break;
                case EventType::WindowResized: { m_windowResizedEventCallback(event.GetData()); } break;
                case EventType::WindowMoved: { m_windowMovedEventCallback(event.GetData()); } break;
                case EventType::WindowGainedFocus: { m_windowGainedFocusEventCallback(); } break;
                case EventType::WindowLostFocus: { m_windowLostFocusEventCallback(); } break;
                case EventType::MouseScrolled: { m_mouseScrolledEventCallback(event.GetData()); } break;
                case EventType::MouseMoved: { m_mouseMovedEventCallback(event.GetData()); } break;
                case EventType::ButtonPressed: { m_buttonPressedEventCallback(event.GetData()); } break;
                case EventType::ButtonReleased: { m_buttonReleasedEventCallback(event.GetData()); } break;
                case EventType::KeyPressed: { m_keyPressedEventCallback(event.GetData()); } break;
                case EventType::KeyReleased: { m_keyReleasedEventCallback(event.GetData()); } break;
                case EventType::KeyRepeated: { m_keyRepeatedEventCallback(event.GetData()); } break;
            }
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Set Window Closed Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetWindowClosedCallback(const std::function<void()>& windowClosedCallback) {
            m_windowClosedEventCallback = windowClosedCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Set Window Resized Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetWindowResizedCallback(const std::function<void(std::stringstream&)>& windowResizedCallback) {
            m_windowResizedEventCallback = windowResizedCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Set Window Moved Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetWindowMovedCallback(const std::function<void(std::stringstream&)>& windowMovedCallback) {
            m_windowMovedEventCallback = windowMovedCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Set Window Gained Focus Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetWindowGainedFocusCallback(const std::function<void()>& windowGainedFocusCallback) {
            m_windowGainedFocusEventCallback = windowGainedFocusCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Set Window Lost Focus Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetWindowLostFocusCallback(const std::function<void()>& windowLostFocusCallback) {
            m_windowLostFocusEventCallback = windowLostFocusCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Set Mouse Scrolled Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetMouseScrolledCallback(const std::function<void(std::stringstream&)>& mouseScrolledCallback) {
            m_mouseScrolledEventCallback = mouseScrolledCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Set Mouse Moved Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetMouseMovedCallback(const std::function<void(std::stringstream&)>& mouseMovedCallback) {
            m_mouseMovedEventCallback = mouseMovedCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Set Button Pressed Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetButtonPressedCallback(const std::function<void(std::stringstream&)>& buttonPressedCallback) {
            m_buttonPressedEventCallback = buttonPressedCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Set Button Released Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetButtonReleasedCallback(const std::function<void(std::stringstream&)>& buttonReleasedCallback) {
            m_buttonReleasedEventCallback = buttonReleasedCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Set Key Pressed Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetKeyPressedCallback(const std::function<void(std::stringstream&)>& keyPressedCallback) {
            m_keyPressedEventCallback = keyPressedCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Set Key Released Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetKeyReleasedCallback(const std::function<void(std::stringstream&)>& keyReleasedCallback) {
            m_keyReleasedEventCallback = keyReleasedCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Set Key Repeated Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetKeyRepeatedCallback(const std::function<void(std::stringstream&)>& keyRepeatedCallback) {
            m_keyRepeatedEventCallback = keyRepeatedCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Get Window Closed Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::function<void()>& GetWindowClosedCallback() {
            return m_windowClosedEventCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Get Window Resized Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::function<void(std::stringstream&)>& GetWindowResizedCallback() {
            return m_windowResizedEventCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Get Window Moved Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::function<void(std::stringstream&)>& GetWindowMovedCallback() {
            return m_windowMovedEventCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Get Window Gained Focus Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::function<void()>& GetWindowGainedFocusCallback() {
            return m_windowGainedFocusEventCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Get Window Lost Focus Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::function<void()>& GetWindowLostFocusCallback() {
            return m_windowLostFocusEventCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Get Mouse Scrolled Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::function<void(std::stringstream&)>& GetMouseScrolledCallback() {
            return m_mouseScrolledEventCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Get Mouse Moved Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::function<void(std::stringstream&)>& GetMouseMovedCallback() {
            return m_mouseMovedEventCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Get Button Pressed Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::function<void(std::stringstream&)>& GetButtonPressedCallback() {
            return m_buttonPressedEventCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Get Button Released Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::function<void(std::stringstream&)>& GetButtonReleasedCallback() {
            return m_buttonReleasedEventCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Get Key Pressed Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::function<void(std::stringstream&)>& GetKeyPressedCallback() {
            return m_keyPressedEventCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Get Key Released Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::function<void(std::stringstream&)>& GetKeyReleasedCallback() {
            return m_keyReleasedEventCallback;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Event Handler Get Key Repeated Event Callback Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::function<void(std::stringstream&)>& GetKeyRepeatedCallback() {
            return m_keyRepeatedEventCallback;
        }

    private:
        std::function<void()> m_windowClosedEventCallback;
        std::function<void(std::stringstream&)> m_windowResizedEventCallback;
        std::function<void(std::stringstream&)> m_windowMovedEventCallback;
        std::function<void()> m_windowGainedFocusEventCallback;
        std::function<void()> m_windowLostFocusEventCallback;
        std::function<void(std::stringstream&)> m_mouseScrolledEventCallback;
        std::function<void(std::stringstream&)> m_mouseMovedEventCallback;
        std::function<void(std::stringstream&)> m_buttonPressedEventCallback;
        std::function<void(std::stringstream&)> m_buttonReleasedEventCallback;
        std::function<void(std::stringstream&)> m_keyPressedEventCallback;
        std::function<void(std::stringstream&)> m_keyReleasedEventCallback;
        std::function<void(std::stringstream&)> m_keyRepeatedEventCallback;

    };
};

#endif