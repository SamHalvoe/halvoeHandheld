#pragma once

#include <SerialInterface.hpp>

namespace halvoe
{
	static constexpr const size_t c_serializerBufferSize = 1024;
	static constexpr const size_t c_deserializerBufferSize = 1024;

	class SerialAudioController : public SerialInterface<c_serializerBufferSize, c_deserializerBufferSize>
	{
	public:
		SerialAudioController(HardwareSerial& in_serial) : SerialInterface<c_serializerBufferSize, c_deserializerBufferSize>(in_serial)
		{}

		bool setup()
		{
			m_serial.begin(19200);

			return m_serial;
		}

		bool playFile(const String& in_filename)
		{
			Serial.println("playFile()");

			auto message = beginMessage(SerialMessageType::command);
			message.m_serializer.writeEnum<SerialCommandCode>(SerialCommandCode::playFile);
			message.m_serializer.write<SerialStringSizeType>(in_filename.c_str(), in_filename.length());

			size_t bytesWritten = message.m_serializer.getBytesWritten();
			return sendMessage(message) == bytesWritten;
		}

		bool endPlayback()
		{
			Serial.println("endPlayback()");

			auto message = beginMessage(SerialMessageType::command);
			message.m_serializer.writeEnum<SerialCommandCode>(SerialCommandCode::endPlayback);

			size_t bytesWritten = message.m_serializer.getBytesWritten();
			return sendMessage(message) == bytesWritten;
		}

	private:
		bool doHandleData(Deserializer<c_deserializerBufferSize>&& in_deserializer, SerialDataCode in_code)
		{
			return false;
		}

		bool doHandleCommand(Deserializer<c_deserializerBufferSize>&& in_deserializer, SerialCommandCode in_code)
		{
			return false;
		}
	};
}
