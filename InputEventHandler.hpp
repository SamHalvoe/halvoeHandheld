#pragma once

#include <vector>
#include <memory>
#include <variant>
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

// ---- CLASS: InputSource

class InputSource
{
  private:
    std::vector<Event>& m_eventList;

  protected:
    // should be called in a run/update method, which is called in loop()
    void addEvents(std::vector<Event>& in_eventList);

  public:
    InputSource(std::vector<Event>& out_eventList);
};

// ---- CLASS: InputTarget
// Input element, which is a target for events, e.g. a button

class InputTarget
{
  public:
    virtual bool handleEvent(const Event& in_event) = 0;
};

// ---- CLASS: InputEventHandler

class InputEventHandler
{
  private:
    std::vector<std::shared_ptr<InputSource>> m_sourceList;
    std::vector<std::shared_ptr<InputTarget>> m_targetList;
    std::vector<Event> m_eventList;

  public:
    InputEventHandler() = default;
    std::vector<Event>& getEventList();
    bool run(); // has to be called in loop()
    bool addSource(std::shared_ptr<InputSource> in_source);
    //bool removeSource(std::shared_ptr<InputSource> in_source);
    bool addTarget(std::shared_ptr<InputTarget> in_target);
    //bool removeTarget(std::shared_ptr<InputTarget> in_target);
};
