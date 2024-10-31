#include "SerialAudioController.hpp"
#include "halvoeLog.hpp"

namespace halvoe
{
	SerialAudioController::SerialAudioController(HardwareSerial& in_serial) :
		SerialInterface<c_serializerBufferSize, c_deserializerBufferSize>(in_serial)
	{}

	bool SerialAudioController::setup()
	{
		m_serial.begin(19200);
		return m_serial;
	}

	bool SerialAudioController::playFile(const String& in_filename)
	{
		LOG_TRACE("playFile()");
		auto message = beginMessage(SerialMessageType::command);
		message.m_serializer.writeEnum<SerialCommandCode>(SerialCommandCode::playFile);
		message.m_serializer.write<SerialStringSizeType>(in_filename.c_str(), in_filename.length());
		return sendMessage(message);
	}

	bool SerialAudioController::endPlayback()
	{
		LOG_TRACE("endPlayback()");
		auto message = beginMessage(SerialMessageType::command);
		message.m_serializer.writeEnum<SerialCommandCode>(SerialCommandCode::endPlayback);
		return sendMessage(message);
	}

	bool SerialAudioController::doHandleData(Deserializer<c_deserializerBufferSize>& io_deserializer, SerialDataCode in_code)
	{
		return false;
	}

	bool SerialAudioController::doHandleCommand(Deserializer<c_deserializerBufferSize>& io_deserializer, SerialCommandCode in_code)
	{
		return false;
	}
}
