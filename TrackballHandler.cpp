#include "TrackballHandler.hpp"
#include "halvoeLog.hpp"

TrackballHandler::TrackballHandler()
{}

bool TrackballHandler::begin(TwoWire& io_wire, const uint8_t in_address)
{
  m_trackball.begin(in_address, io_wire);
  m_trackball.setRGBW(0, 0, 0, 255);

  return true;
}

bool TrackballHandler::update()
{
  bool wasChanged = false;

  if (m_timeSinceUpdate >= UPDATE_INTERVAL)
  {
    wasChanged = m_trackball.read();

    if (wasChanged)
    {
      LOG_TRACE(" ", m_trackball.up(), "\n",
                m_trackball.left(), "+", m_trackball.right(), "\n",
                " ", m_trackball.down(), "\n");
    }

    m_timeSinceUpdate = 0;
  }

  return wasChanged;
}

uint8_t TrackballHandler::up()
{
  return m_trackball.up();
}

uint8_t TrackballHandler::left()
{
  return m_trackball.left();
}

uint8_t TrackballHandler::right()
{
  return m_trackball.right();
}

uint8_t TrackballHandler::down()
{
  return m_trackball.down();
}

bool TrackballHandler::clicked()
{
  return m_trackball.click();
}

bool TrackballHandler::released()
{
  return m_trackball.release();
}
