#include "InputEventHandler.hpp"

// ---- CLASS: InputSource

void InputSource::addEvents(std::vector<Event>& in_eventList)
{
  m_eventList.insert(m_eventList.end(), in_eventList.begin(), in_eventList.end());
}

InputSource::InputSource(std::vector<Event>& out_eventList) : m_eventList(out_eventList)
{}

// ---- CLASS: InputEventHandler

std::vector<Event>& InputEventHandler::getEventList()
{
  return m_eventList;
}

bool InputEventHandler::run()
{
  for (auto& target : m_targetList)
  {
    auto iterator = m_eventList.cend();
    for (;iterator != m_eventList.cend(); ++iterator)
    {
      if (target->handleEvent(m_eventList[0])) { break; }
    }

    if (iterator != m_eventList.cend())
    {
      m_eventList.erase(iterator);
    }
  }

  return true;
}

bool InputEventHandler::addSource(std::shared_ptr<InputSource> in_source)
{
  m_sourceList.emplace_back(in_source);
  return true;
}

bool InputEventHandler::addTarget(std::shared_ptr<InputTarget> in_target)
{
  m_targetList.emplace_back(in_target);
  return true;
}
