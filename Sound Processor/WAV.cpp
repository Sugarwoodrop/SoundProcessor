#include "WAV.h"
using namespace WAV;


WAVFILE::WAVFILE() : byteRate(88200), blockAlign(2) , subchunk2Size(0){};

WAVFILE::WAVFILE(char* argv) :byteRate(88200), blockAlign(2) {
	Filename = argv;
	std::ifstream FILE(argv, std::ios::binary);
	if (!FILE) {
		throw std::exception("Не найден файл");
	}
	char riff[4];
	FILE.read(riff, 4);
	if (riff[0] != 'R' || riff[1] != 'I' || riff[2] != 'F' || riff[3] != 'F') {
		FILE.close();
		throw std::exception("WAV ERROR");
	}
	FILE.read(reinterpret_cast<char*>(&subchunk2Size), sizeof(uint32_t));
	data = subchunk2Size+4;

	FILE.read(riff, 4);
	if (riff[0] != 'W' || riff[1] != 'A' || riff[2] != 'V' || riff[3] != 'E') {
		FILE.close();
		throw std::exception("WAV ERROR");
	}

	char fmt[4];
	FILE.read(fmt, 4);
	if (fmt[0] != 'f' || fmt[1] != 'm' || fmt[2] != 't') {
		FILE.close();
		throw std::exception("WAV ERROR");
	}

	FILE.seekg(20, std::ios_base::cur);

	FILE.read(riff, 4);

	if (riff[0] != 'd' || riff[1] != 'a' || riff[2] != 't'|| riff[3] != 'a') {
		FILE.read(reinterpret_cast<char*>(&subchunk2Size), sizeof(uint32_t));
		FILE.seekg(subchunk2Size, std::ios_base::cur);
		FILE.read(riff, 4);
		if (riff[0] != 'd' || riff[1] != 'a' || riff[2] != 't' || riff[3] != 'a') {
			FILE.close();
			throw std::exception("WAV ERROR");
		}
	}
	FILE.read(reinterpret_cast<char*>(&subchunk2Size), sizeof(uint32_t));
	data -= subchunk2Size;
	FILE.close();
};

void WAVFILE::CreatingFile(char* Output, WAVFILE FirstFile) {
	Filename = Output;
	std::ofstream FILE(Output, std::ios::binary);
	FILE.clear();
	std::ifstream FirstFILE(FirstFile.Filename, std::ios::binary);
	FirstFILE.seekg(4, std::ios_base::beg);
	uint32_t chunkSize;
	FirstFILE.read(reinterpret_cast<char*>(&chunkSize), sizeof(uint32_t));
	FirstFILE.seekg(FirstFile.data, std::ios_base::beg);
	FirstFILE.read(reinterpret_cast<char*>(&subchunk2Size), sizeof(uint32_t));
	int Time = std::ceil(subchunk2Size / 88200);
	data = 40;
	FirstFILE.close();
	char riff[] = "RIFF";
	char wave[] = "WAVE";
	char fmt[] = "fmt ";
	uint32_t subchunk1Size = 16;
	uint16_t audioFormat = 1;
	uint16_t numChannels = 1;
	uint32_t sampleRate = 44100;
	uint16_t bitsPerSample = 16;
	char datafile[] = "data";
	FILE << riff;
	FILE.write((char*)&chunkSize, sizeof(chunkSize));
	FILE << wave;
	FILE << fmt;
	FILE.write((char*)&subchunk1Size, sizeof(subchunk1Size));
	FILE.write((char*)&audioFormat, sizeof(audioFormat));
	FILE.write((char*)&numChannels, sizeof(numChannels));
	FILE.write((char*)&sampleRate, sizeof(sampleRate));
	FILE.write((char*)&byteRate, sizeof(byteRate));
	FILE.write((char*)&blockAlign, sizeof(blockAlign));
	FILE.write((char*)&bitsPerSample, sizeof(bitsPerSample));
	FILE << datafile;
	FILE.write((char*)&subchunk2Size, sizeof(subchunk2Size));
	for (int i = 1; i <= Time; ++i) {
		std::vector<int16_t> sample(44100);
		sample = FirstFile.Sample(i);
		RecordingSample(sample, i, FILE);
	}
	FILE.close();
};

std::vector<int16_t> WAVFILE::Sample(int time) {
	std::ifstream FILE(Filename, std::ios::binary);
	if (!FILE) {
		throw std::exception("Не найден файл");
	}
	std::vector<int16_t> sample(44100);
	FILE.seekg(data, std::ios_base::beg);
	FILE.seekg((time-1) * byteRate, std::ios_base::cur);
	for (int i = 0; i < 44100; ++i) {
		FILE.read(reinterpret_cast<char*>(&sample[i]), sizeof(int16_t));
	}
	FILE.close();
	return sample;
}

void WAVFILE::RecordingSample(std::vector<int16_t>& samples, int time, std::ofstream& FILE) {
	FILE.seekp(data + ((time - 1) * byteRate), std::ios_base::beg);
	for (int j = 0; j < 44100; ++j) {
		FILE.write(reinterpret_cast<char*>(&samples[j]), sizeof(int16_t));
	}
}

std::string WAVFILE::FileName() {
	return Filename;
}