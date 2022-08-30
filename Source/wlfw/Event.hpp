#pragma once
#ifndef WLFW_EVENT_HEADER
#define WLFW_EVENT_HEADER

#include "wlfw.hpp"

namespace wl {
    ////////////////////////////////////////////////////////////
    /// \brief Event Type Enum With Our Events Which Can Be Invoked
    ///
    ////////////////////////////////////////////////////////////
    enum WL_API EventType {
        None = 0,
        WindowClosed = WLFW_BYTE(0),
        WindowResized = WLFW_BYTE(1),
        WindowMoved = WLFW_BYTE(2),
        MouseMoved = WLFW_BYTE(3),
        MouseScrolled = WLFW_BYTE(4),
        MouseButtonPresssed = WLFW_BYTE(5),
        MouseButtonReleased = WLFW_BYTE(6),
        KeyPresssed = WLFW_BYTE(7),
        KeyReleased = WLFW_BYTE(8),
        KeyRepeated = WLFW_BYTE(9),
    };

    ////////////////////////////////////////////////////////////
    /// \brief Event Class Which Is Base For Every Event
    ///
    ////////////////////////////////////////////////////////////
    class WL_API Event {
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
        inline EventType& GetEventType() const { return m_eventType; }

        ////////////////////////////////////////////////////////////
        /// \brief Get Event Name Function
        ///
        ////////////////////////////////////////////////////////////
        inline std::string& GetName() const { return m_name; }
        
        ////////////////////////////////////////////////////////////
        /// \brief Get Event Format Message Function
        ///
        ////////////////////////////////////////////////////////////
        virtual std::string GetFormat() const = 0;

    protected:
        EventType m_eventType;
        std::string m_name;

    };

    
};

#endif