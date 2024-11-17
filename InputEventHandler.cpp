#include "InputEventHandler.hpp"

// ---- CLASS: EventSource

void EventSource::dispatchEvent(Event&& in_event)
{
  auto range = m_eventHandlerMap.equal_range(in_event.m_type);
  
  for (auto iterator = range.first; iterator != range.second; ++iterator)
  {
    iterator->second(in_event); // call callback with in_event
  }
}

void EventSource::addEventCallback(Event::Type in_type, EventCallback in_callback)
{
  m_eventHandlerMap.emplace(in_type, in_callback);
}
