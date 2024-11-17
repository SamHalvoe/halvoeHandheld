#pragma once

#include <map>
#include <variant>
#include <functional>
#include <tgx.h>

// ---- STRUCT: Event

struct Event
{
  public:
    enum class Type : uint8_t
    {
      moved = 0,
      pressed,
      released,
      clicked
    };

  public:
    Type m_type;
    std::variant<tgx::iVec2> m_data;
};

// ---- FUNCTION POINTER: EventCallback

using EventCallback = std::function<void(const Event& in_event)>;

// ---- CLASS: EventSource

class EventSource
{
  protected:
    std::multimap<Event::Type, EventCallback> m_eventHandlerMap;

  protected:
    void dispatchEvent(Event&& in_event);

  public:
    void addEventCallback(Event::Type in_type, EventCallback in_callback);
};
