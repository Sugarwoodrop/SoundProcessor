#pragma once
#include <vector>
namespace WAVConverters {
	class Converters
	{
	public:
		virtual void Converter(std::vector<int16_t>& samples) = 0;
		virtual ~Converters() = default;
	};



	class Mute :public Converters
	{
	public:
		void Converter(std::vector<int16_t>& samples) override;
	};

	class Mix :public Converters
	{
	private:
		std::vector<int16_t> SecondSamples;
	public:
		void SampleСhanges(std::vector<int16_t>& NewSamples);
		void Converter(std::vector<int16_t>& samples) override;
	};

	class Echo :public Converters //sample длинной в 44100, время эха 0.5 секунд => эхо получится добавить ровно на половину семпла(первые 0.5 обычный семпл а вторые 0.5 с эхо) 
	{
	public:
		void Converter(std::vector<int16_t>& samples) override;
	};



	class Converter
	{
	 public:
		 void Start(Converters* Type, std::vector<int16_t>& samples);
	};
}
//WAV::WAVFILE InputFile, WAV::WAVFILE OutputFile, unsigned int start, unsigned int end

