#pragma once

#include <SerialInterface.hpp>

namespace halvoeHandheld
{
	static const size_t c_serializerBufferSize = 1024;
	static const size_t c_deserializerBufferSize = 1024;

	class SerialAudioController : public halvoe::SerialInterface<c_serializerBufferSize, c_deserializerBufferSize>
	{
		public:
			SerialAudioController(HardwareSerial& in_serial);
			bool setup();
			bool playFile(const String& in_filename);
			bool endPlayback();

		private:
			bool doHandleData(halvoe::Deserializer<c_deserializerBufferSize>& io_deserializer, halvoe::SerialDataCode in_code);
			bool doHandleCommand(halvoe::Deserializer<c_deserializerBufferSize>& io_deserializer, halvoe::SerialCommandCode in_code);
	};
}
