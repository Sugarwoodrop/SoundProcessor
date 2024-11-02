#include "Converters.h"
using namespace WAVConverters;

void Mute::Converter(std::vector<int16_t>& samples) {
	for (int i = 0; i < 44100; i++) {
		samples[i] = 0;
	}
};

void Mix::SampleСhanges(std::vector<int16_t>& NewSamples) {
	SecondSamples = NewSamples;
}

void Mix::Converter(std::vector<int16_t>& samples) {
	for (int i = 0; i < 44100; i++) {
			samples[i] = (SecondSamples[i]*1.1 + samples[i]) / 2;
	}
};

void Echo::Converter(std::vector<int16_t>& samples) {
	for (int i = 0; i < 38367; i++) {
		int16_t a = samples[i + 5733 - 1];
		samples[i + 5733 - 1] = ((samples[i] * 0.3) + a * 0.7);
	}
};


void Converter::Start(Converters* Type, std::vector<int16_t>& samples) {
	Type->Converter (samples);
};