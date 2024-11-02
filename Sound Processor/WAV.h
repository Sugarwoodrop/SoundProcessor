#pragma once
#include <iostream>
#include <cstdint>
#include <fstream>
#include <vector>
#include <cmath>

namespace WAV {
    class WAVFILE
    {
    private:
        std::string Filename;
        uint32_t byteRate; // Количество байт, воспроизводимых в секунду (рассчитывается как Sample Rate(44100) * Number of Channels(1) * Bits Per Sample(16) / 8).
        uint16_t blockAlign; // Количество байт для одного сэмпла, включая все каналы (рассчитывается как Number of Channels(1) * Bits Per Sample(16) / 8).
        uint32_t subchunk2Size;//Количество байт в области данных.
        uint32_t data;
        //и сама облость данных(тоесть сам звук)
    public:
        WAVFILE();
        WAVFILE(char* argv);
        void RecordingSample(std::vector<int16_t>& samples, int time, std::ofstream& FILE);
        std::vector<int16_t> Sample(int time);
        void CreatingFile(char* Output, WAVFILE FirstFile);
        std::string FileName();
    };
}