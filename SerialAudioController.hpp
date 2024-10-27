#pragma once

#include <SerialInterface.hpp>

namespace halvoe
{
	static const size_t c_serializerBufferSize = 1024;
	static const size_t c_deserializerBufferSize = 1024;

	class SerialAudioController : public SerialInterface<c_serializerBufferSize, c_deserializerBufferSize>
	{
		public:
			SerialAudioController(HardwareSerial& in_serial);
			bool setup();
			bool playFile(const String& in_filename);
			bool endPlayback();

		private:
			bool doHandleData(Deserializer<c_deserializerBufferSize>& io_deserializer, SerialDataCode in_code);
			bool doHandleCommand(Deserializer<c_deserializerBufferSize>& io_deserializer, SerialCommandCode in_code);
	};
}
