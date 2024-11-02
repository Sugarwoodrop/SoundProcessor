#include <iostream>
#include "Preparation.h"
#include "WAVinterface.h"

int main(int argc, char* argv[])
{
	char c;

	std::cout<<"Для продолжения работы файла нажмите Enter" << std::endl;
	std::cout << "Для вывода info введите h" << std::endl;
	c = std::getchar();
	if (c == 'h') {
		system("cls");
		std::cout << "В конфиге конверторы пишутся с маленькой буквы" << std::endl;
		std::cout << "После конверторов echo и mute через один пробел пишутся два интервала. Между этими интервалами пробел" << std::endl;
		std::cout << "После конвертора mix через одни пробел пишется $ и сразу после него номер файла. После опять два интервала через пробел" << std::endl;
		std::cout << "В конце конфиг файла не должно быть пустой строки" << std::endl << std::endl;
		std::cout << "WAV Файлы должны находится в директории программы" << std::endl;
		std::cout << "WAV Файлы 16 bit, Mono, 44100Hz" << std::endl;
		return 3;
	};
	system("cls");
	int FirstWAV;
	std::cout << "Введите номер начального файла" << std::endl;
	std::cin >> FirstWAV;
	if (FirstWAV <= 0 || FirstWAV > argc - 2) {
		std::cout << "Файла под таким номером нету" << std::endl;
		return -1;
	}
	system("cls");
	std::cout << "Ожидайте окончания" << std::endl;
	

		try {
			Checking::Preparation Cheack;
			Cheack.CheckingFileFormat(argc, argv);
			Cheack.CheckingConfig(argv[1], argc);
		}
		catch (std::exception& Error) {
			system("cls");
			std::cout << Error.what() << std::endl;
			return 1;
		}
		try {
			WAV::WAVFILE Output;
			WAV::WAVFILE First(argv[FirstWAV+2]);
			ConfigFile::Config Config(argv[1]);
			Output.CreatingFile(argv[2], First);
			Interface::WAVinterface A;
			Config.CountNumberConverter();
			int QuantityConverter = Config.QuantityConverters();
			for (int i = 1; i <= QuantityConverter; ++i) {
				A.Start(Output, Config, argc, argv);
			}
		}
		catch (std::exception& Error) {
			std::cout << Error.what() << std::endl;
			return 2;
		}
		system("cls");
		std::cout << "Готова" << std::endl;
}