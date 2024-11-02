#include "WAVinterface.h"
using namespace Interface;



void WAVinterface::Start(WAV::WAVFILE Output, ConfigFile::Config& Config, int argc, char* argv[]) {
	std::ofstream FILE(Output.FileName(), std::ios::binary | std::ios::in | std::ios::out);
	int* ConverterParametr = new int[4];
	ConverterParametr = Config.SearchConverter();
	WAVConverters::Converter Convert;
	int Converters = ConverterParametr[0];
	int Firstinterval = ConverterParametr[2];
	Firstinterval++;
	int Secondinterval = ConverterParametr[3];
	int NumberFileMix = ConverterParametr[1];
	if (Converters == 1) {
		WAVConverters::Mute Mute;

		for (int i = Firstinterval; i <= Secondinterval; ++i) {
			std::vector<int16_t> sample = Output.Sample(i);
			Convert.Start(&Mute, sample);
			Output.RecordingSample(sample, i, FILE);
		}
	}
	else if (Converters == 2) {
		WAVConverters::Mix Mix;
		WAV::WAVFILE SecondFile(argv[NumberFileMix+2]);
		for (int i = Firstinterval; i <= Secondinterval; ++i) {
			std::vector<int16_t> sample = SecondFile.Sample(i);
			Mix.SampleСhanges(sample);
			std::vector<int16_t> Secondsample = Output.Sample(i);
			Convert.Start(&Mix, Secondsample);
			Output.RecordingSample(Secondsample, i, FILE);
		}
	}
	else if (Converters == 3) {
		WAVConverters::Echo Echo;
		for (int i = Secondinterval; i >= Firstinterval; --i) {
			std::vector<int16_t> sample = Output.Sample(i);
			Convert.Start(&Echo, sample);
			Output.RecordingSample(sample, i, FILE);
		}
	}
	FILE.close();
}