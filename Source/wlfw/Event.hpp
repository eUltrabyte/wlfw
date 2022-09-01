#pragma once
#ifndef WLFW_EVENT_HEADER
#define WLFW_EVENT_HEADER

#include "wlfw.hpp"

namespace wl {
    ////////////////////////////////////////////////////////////
    /// \brief Event Type Enum With Our Events Which Can Be Invoked
    ///
    ////////////////////////////////////////////////////////////
    enum WLFW_API EventType {
        WindowClosed = WLFW_BYTE(0),
        WindowResized = WLFW_BYTE(1),
        WindowMoved = WLFW_BYTE(2),
        MouseScrolled = WLFW_BYTE(3),
        MouseMoved = WLFW_BYTE(4),
        ButtonPressed = WLFW_BYTE(5),
        ButtonReleased = WLFW_BYTE(6),
        KeyPresssed = WLFW_BYTE(7),
        KeyReleased = WLFW_BYTE(8),
        KeyRepeated = WLFW_BYTE(9),
    };

    ////////////////////////////////////////////////////////////
    /// \brief Event Class Which Is Base For Every Event
    ///
    ////////////////////////////////////////////////////////////
    class WLFW_API Event {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Event Class Constructor
        ///
        ////////////////////////////////////////////////////////////
        Event(const std::string_view& name, const EventType& eventType) : m_eventType(eventType), m_name(name) { }

        ////////////////////////////////////////////////////////////
        /// \brief Event Class Destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~Event() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get Event Type Function
        ///
        ////////////////////////////////////////////////////////////
        inline EventType& GetEventType() const { return (EventType&)m_eventType; }

        ////////////////////////////////////////////////////////////
        /// \brief Get Event Name Function
        ///
        ////////////////////////////////////////////////////////////
        inline std::string& GetName() const { return (std::string&)m_name; }
        
        ////////////////////////////////////////////////////////////
        /// \brief Get Event Format Message Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::string GetFormat() const = 0;

    protected:
        EventType m_eventType;
        std::string m_name;

    };

    class WLFW_API WindowClosedEvent : public Event {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Window Closed Event Class Constructor
        ///
        ////////////////////////////////////////////////////////////
        WindowClosedEvent() : Event("Window Closed Event", EventType::WindowClosed) { }

        ////////////////////////////////////////////////////////////
        /// \brief Window Closed Event Class Destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~WindowClosedEvent() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get Format Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::string GetFormat() const override {
            return GetName();
        }

    };

    class WLFW_API WindowResizedEvent : public Event {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Window Resized Event Class Constructor
        ///
        ////////////////////////////////////////////////////////////
        WindowResizedEvent(int width = 0, int height = 0) : Event("Window Resized Event", EventType::WindowResized), m_width(width), m_height(height) { }

        ////////////////////////////////////////////////////////////
        /// \brief Window Resized Event Class Destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~WindowResizedEvent() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get Format Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::string GetFormat() const override {
            return GetName() + " : Width : " + std::to_string(m_width) + " : Height : " + std::to_string(m_height);
        }

        ////////////////////////////////////////////////////////////
        /// \brief Get Width Function
        ///
        ////////////////////////////////////////////////////////////
        virtual int& GetWidth() { return m_width; }

        ////////////////////////////////////////////////////////////
        /// \brief Get Height Function
        ///
        ////////////////////////////////////////////////////////////
        virtual int& GetHeight() { return m_height; }

    private:
        int m_width;
        int m_height;

    };

    class WLFW_API WindowMovedEvent : public Event {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Window Moved Event Class Constructor
        ///
        ////////////////////////////////////////////////////////////
        WindowMovedEvent(int x = 0, int y = 0) : Event("Window Moved Event", EventType::WindowMoved), m_x(x), m_y(y) { }
        
        ////////////////////////////////////////////////////////////
        /// \brief Window Moved Event Class Destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~WindowMovedEvent() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get Format Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::string GetFormat() const override {
            return GetName() + " : X : " + std::to_string(m_x) + " : Y : " + std::to_string(m_y);
        }

        ////////////////////////////////////////////////////////////
        /// \brief Get X Coordinate Function
        ///
        ////////////////////////////////////////////////////////////
        virtual int& GetX() { return m_x; }

        ////////////////////////////////////////////////////////////
        /// \brief Get Y Coordinate Function
        ///
        ////////////////////////////////////////////////////////////
        virtual int& GetY() { return m_y; }

    private:
        int m_x;
        int m_y;

    };

    class WLFW_API MouseScrolledEvent : public Event {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Mouse Scrolled Event Class Constructor
        ///
        ////////////////////////////////////////////////////////////
        MouseScrolledEvent(bool pressed = false, int direction = 0) : Event("Mouse Scrolled Event", EventType::MouseScrolled), m_pressed(pressed), m_direction(direction) { }
        
        ////////////////////////////////////////////////////////////
        /// \brief Mouse Scrolled Event Class Destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~MouseScrolledEvent() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get Format Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::string GetFormat() const override {
            return GetName() + " : Pressed : " + std::to_string(m_pressed) + " : Direction : " + std::to_string(m_direction);
        }

        ////////////////////////////////////////////////////////////
        /// \brief Get Scroll Pressed Bool Function
        ///
        ////////////////////////////////////////////////////////////
        virtual bool& GetPressed() { return m_pressed; }

        ////////////////////////////////////////////////////////////
        /// \brief Get Scroll Direction Function
        ///
        ////////////////////////////////////////////////////////////
        virtual int& GetDirection() { return m_direction; }

    private:
        bool m_pressed;
        int m_direction;

    };

    class WLFW_API MouseMovedEvent : public Event {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Mouse Moved Event Class Constructor
        ///
        ////////////////////////////////////////////////////////////
        MouseMovedEvent(int x = 0, int y = 0) : Event("Mouse Moved Event", EventType::MouseMoved), m_x(x), m_y(y) { }
        
        ////////////////////////////////////////////////////////////
        /// \brief Mouse Moved Event Class Destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~MouseMovedEvent() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get Format Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::string GetFormat() const override {
            return GetName() + " : X : " + std::to_string(m_x) + " : Y : " + std::to_string(m_y);
        }

        ////////////////////////////////////////////////////////////
        /// \brief Get Mouse X Coordinate Function
        ///
        ////////////////////////////////////////////////////////////
        virtual int& GetX() { return m_x; }

        ////////////////////////////////////////////////////////////
        /// \brief Get Mouse Y Coordinate Function
        ///
        ////////////////////////////////////////////////////////////
        virtual int& GetY() { return m_y; }

    private:
        int m_x;
        int m_y;

    };

    enum WLFW_API Buttons {
        Left = WLFW_BYTE(0),
        Middle = WLFW_BYTE(1),
        Right = WLFW_BYTE(2),
    };

    class WLFW_API ButtonPressedEvent : public Event {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Button Pressed Event Class Constructor
        ///
        ////////////////////////////////////////////////////////////
        ButtonPressedEvent(int button = 0) : Event("Button Pressed Event", EventType::ButtonPressed), m_button(button) { }
        
        ////////////////////////////////////////////////////////////
        /// \brief Button Pressed Event Class Destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~ButtonPressedEvent() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get Format Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::string GetFormat() const override {
            return GetName() + " : Button : " + std::to_string(m_button);
        }

        ////////////////////////////////////////////////////////////
        /// \brief Get Pressed Button Function
        ///
        ////////////////////////////////////////////////////////////
        virtual int& GetButton() { return m_button; }

    private:
        int m_button;

    };

    class WLFW_API ButtonReleasedEvent : public Event {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Button Released Event Class Constructor
        ///
        ////////////////////////////////////////////////////////////
        ButtonReleasedEvent(int button = 0) : Event("Button Released Event", EventType::ButtonReleased), m_button(button) { }
        
        ////////////////////////////////////////////////////////////
        /// \brief Button Released Event Class Destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~ButtonReleasedEvent() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get Format Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::string GetFormat() const override {
            return GetName() + " : Button : " + std::to_string(m_button);
        }

        ////////////////////////////////////////////////////////////
        /// \brief Get Released Button Function
        ///
        ////////////////////////////////////////////////////////////
        virtual int& GetButton() { return m_button; }

    private:
        int m_button;

    };

    enum WLFW_API Keys {
        Q = WLFW_BYTE(0),
        W = WLFW_BYTE(1),
        E = WLFW_BYTE(2),
        R = WLFW_BYTE(3),
        T = WLFW_BYTE(4),
        Y = WLFW_BYTE(5),
        U = WLFW_BYTE(6),
        I = WLFW_BYTE(7),
        O = WLFW_BYTE(8),
        P = WLFW_BYTE(9),
        A = WLFW_BYTE(10),
        S = WLFW_BYTE(11),
        D = WLFW_BYTE(12),
        F = WLFW_BYTE(13),
        G = WLFW_BYTE(14),
        H = WLFW_BYTE(15),
        J = WLFW_BYTE(16),
        K = WLFW_BYTE(17),
        L = WLFW_BYTE(18),
        Z = WLFW_BYTE(19),
        X = WLFW_BYTE(20),
        C = WLFW_BYTE(21),
        V = WLFW_BYTE(22),
        B = WLFW_BYTE(23),
        N = WLFW_BYTE(24),
        M = WLFW_BYTE(25),
    };

    // TODO OTHER KEYS

    class WLFW_API KeyPressedEvent : public Event {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Key Pressed Event Class Constructor
        ///
        ////////////////////////////////////////////////////////////
        KeyPressedEvent(int key = 0) : Event("Key Pressed Event", EventType::KeyPresssed), m_key(key) { }
        
        ////////////////////////////////////////////////////////////
        /// \brief Key Pressed Event Class Destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~KeyPressedEvent() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get Format Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::string GetFormat() const override {
            return GetName() + " : Key : " + std::to_string(m_key);
        }

        ////////////////////////////////////////////////////////////
        /// \brief Get Pressed Key Function
        ///
        ////////////////////////////////////////////////////////////
        virtual int& GetKey() { return m_key; }

    private:
        int m_key;

    };

    class WLFW_API KeyReleasedEvent : public Event {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Key Released Event Class Constructor
        ///
        ////////////////////////////////////////////////////////////
        KeyReleasedEvent(int key = 0) : Event("Key Released Event", EventType::KeyReleased), m_key(key) { }
        
        ////////////////////////////////////////////////////////////
        /// \brief Key Released Event Class Destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~KeyReleasedEvent() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get Format Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::string GetFormat() const override {
            return GetName() + " : Key : " + std::to_string(m_key);
        }

        ////////////////////////////////////////////////////////////
        /// \brief Get Released Key Function
        ///
        ////////////////////////////////////////////////////////////
        virtual int& GetKey() { return m_key; }

    private:
        int m_key;

    };

    class WLFW_API KeyRepeatedEvent : public Event {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Key Repeated Event Class Constructor
        ///
        ////////////////////////////////////////////////////////////
        KeyRepeatedEvent(int key = 0) : Event("Key Repeated Event", EventType::KeyRepeated), m_key(key) { }
        
        ////////////////////////////////////////////////////////////
        /// \brief Key Repeated Event Class Destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~KeyRepeatedEvent() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get Format Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::string GetFormat() const override {
            return GetName() + " : Key : " + std::to_string(m_key);
        }

        ////////////////////////////////////////////////////////////
        /// \brief Get Repeated Key Function
        ///
        ////////////////////////////////////////////////////////////
        virtual int& GetKey() { return m_key; }

    private:
        int m_key;

    };
};

#endif