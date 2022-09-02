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
        KeyPressed = WLFW_BYTE(7),
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
        Event(const std::string_view& name, const EventType& eventType) : m_eventType(eventType), m_name(name), m_data() { }

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

        ////////////////////////////////////////////////////////////
        /// \brief Get Event Data Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::stringstream& GetData() const = 0;

    protected:
        EventType m_eventType;
        std::string m_name;
        std::stringstream m_data;

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

        ////////////////////////////////////////////////////////////
        /// \brief Get Data Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::stringstream& GetData() const override {
            return (std::stringstream&)m_data;
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

        ////////////////////////////////////////////////////////////
        /// \brief Get Data Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::stringstream& GetData() const override {
            std::stringstream& data = (std::stringstream&)m_data;
            data << m_width << ':' << m_height;
            return data;
        }

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

        ////////////////////////////////////////////////////////////
        /// \brief Get Data Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::stringstream& GetData() const override {
            std::stringstream& data = (std::stringstream&)m_data;
            data << m_x << ':' << m_y;
            return data;
        }

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

        ////////////////////////////////////////////////////////////
        /// \brief Get Data Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::stringstream& GetData() const override {
            std::stringstream& data = (std::stringstream&)m_data;
            data << m_pressed << ':' << m_direction;
            return data;
        }

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

        ////////////////////////////////////////////////////////////
        /// \brief Get Data Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::stringstream& GetData() const override {
            std::stringstream& data = (std::stringstream&)m_data;
            data << m_x << ':' << m_y;
            return data;
        }

    private:
        int m_x;
        int m_y;

    };

    enum WLFW_API Buttons {
        Left = 0,
        Middle = 1,
        Right = 2,
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

        ////////////////////////////////////////////////////////////
        /// \brief Get Data Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::stringstream& GetData() const override {
            std::stringstream& data = (std::stringstream&)m_data;
            data << m_button;
            return data;
        }

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

        ////////////////////////////////////////////////////////////
        /// \brief Get Data Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::stringstream& GetData() const override {
            std::stringstream& data = (std::stringstream&)m_data;
            data << m_button;
            return data;
        }

    private:
        int m_button;

    };

    enum WLFW_API Keys {
        Q = 0,
        W = 1,
        E = 2,
        R = 3,
        T = 4,
        Y = 5,
        U = 6,
        I = 7,
        O = 8,
        P = 9,
        A = 10,
        S = 11,
        D = 12,
        F = 13,
        G = 14,
        H = 15,
        J = 16,
        K = 17,
        L = 18,
        Z = 19,
        X = 20,
        C = 21,
        V = 22,
        B = 23,
        N = 24,
        M = 25,

        Escape = 26,
        GraveAccent = 27,
        Tab = 28,
        CapsLock = 29,
        Shift = 30,
        RightControl = 31,

        Zero = 32,
        One = 33,
        Two = 34,
        Three = 35,
        Four = 36,
        Five = 37,
        Six = 38,
        Seven = 39,
        Eight = 40,
        Nine = 41,
    };

    // TODO OTHER KEYS

    class WLFW_API KeyPressedEvent : public Event {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Key Pressed Event Class Constructor
        ///
        ////////////////////////////////////////////////////////////
        KeyPressedEvent(int key = 0) : Event("Key Pressed Event", EventType::KeyPressed), m_key(key) { }
        
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

        ////////////////////////////////////////////////////////////
        /// \brief Get Data Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::stringstream& GetData() const override {
            std::stringstream& data = (std::stringstream&)m_data;
            data << m_key;
            return data;
        }

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

        ////////////////////////////////////////////////////////////
        /// \brief Get Data Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::stringstream& GetData() const override {
            std::stringstream& data = (std::stringstream&)m_data;
            data << m_key;
            return data;
        }

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

        ////////////////////////////////////////////////////////////
        /// \brief Get Data Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::stringstream& GetData() const override {
            std::stringstream& data = (std::stringstream&)m_data;
            data << m_key;
            return data;
        }

    private:
        int m_key;

    };
};

#endif