#pragma once
#include "WAV.h"
#include "Converters.h"
#include "Config.h"
namespace Interface {
	class WAVinterface
	{
	public:
		void Start(WAV::WAVFILE Output, ConfigFile::Config& Config, int argc, char* argv[]);
	};
}

