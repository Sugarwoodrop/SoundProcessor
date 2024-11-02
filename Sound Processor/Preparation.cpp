#include "Preparation.h"
using namespace Checking;

bool Preparation::WAVFormat(char* File,int SizeNameFile) {
	if (File[SizeNameFile - 4] == '.' && File[SizeNameFile - 3] == 'w' && File[SizeNameFile - 2] == 'a' && File[SizeNameFile - 1] == 'v') {
		return true;
	}
	else {
		return false;
	}
};

bool Preparation::TXTFormat(char* File, int SizeNameFile) {
	if (File[SizeNameFile - 4] == '.' && File[SizeNameFile - 3] == 't' && File[SizeNameFile - 2] == 'x' && File[SizeNameFile - 1] == 't') {
		return true;
	}
	else {
		return false;
	}
}

void Preparation::CheckingConfig(char* ConfigFile, int argc) {


	std::ifstream FILE(ConfigFile);
	if (!FILE) {
		throw std::exception("Не найден файл конфига");
	}
	char Parameter[4];
	while (!FILE.eof()) {
		FILE.read(Parameter, 4);
		if (Parameter[0] == '#') {
			FILE.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}
		else if (Parameter[0] == 'm' || Parameter[0] == 'e') {
			if (Parameter[0] == 'm' && Parameter[1] == 'u'&& Parameter[2] == 't'&& Parameter[3] == 'e') {
				int Oneinterval = -1;
				int NumberInterval = 0;
				while (NumberInterval < 2) {
					char Check[1];
					FILE.read(Check, 1);
					if (Check[0] != ' ') {
						throw std::exception("Неверное заполнение конфига. Можно написать -h для детальной информации");
					}
					int interval = Oneinterval;
					FILE >> Oneinterval;
					if (Oneinterval < 0) {
						throw std::exception("Неверное заполнение конфига. Можно написать -h для детальной информации");
					}
					NumberInterval++;
					if (NumberInterval == 2 && interval > Oneinterval) {
						throw std::exception("Неверное заполнение конфига. Можно написать -h для детальной информации");
					}
					if (NumberInterval == 2) {
						FILE.read(Check, 1);
						if (Check[0] != '\n') {
							throw std::exception("Неверное заполнение конфига. Можно написать -h для детальной информации");
						}
					}
				}
			}
			else if (Parameter[0] == 'm' && Parameter[1] == 'i' && Parameter[2] == 'x' && Parameter[3] == ' ') {
				char argument[1];
				FILE.read(argument, 1);
				int NumberFileMix = 0;
				FILE >> NumberFileMix;
				if (argument[0] != '$' || NumberFileMix < 1 || NumberFileMix > argc-2) {
					throw std::exception("Неверное заполнение конфига. Можно написать -h для детальной информации");
				}
				NumberFileMix = 0;
				int NumberInterval = 0;
				while (NumberInterval < 2) {
					char Check[1];
					FILE.read(Check, 1);
					if (Check[0] != ' ') {
						throw std::exception("Неверное заполнение конфига. Можно написать -h для детальной информации");
					}
					int interval = NumberFileMix;
					FILE >> NumberFileMix;
					if (NumberFileMix < 0) {
						throw std::exception("Неверное заполнение конфига. Можно написать -h для детальной информации");
					}
					NumberInterval++;
					if (NumberInterval == 2 && interval > NumberFileMix) {
						throw std::exception("Неверное заполнение конфига. Можно написать -h для детальной информации");
					}
					if (NumberInterval == 2) {
						FILE.read(Check, 1);
						if (Check[0] != '\n') {
							throw std::exception("Неверное заполнение конфига. Можно написать -h для детальной информации");
						}
					}
				}
			}
			else if (Parameter[0] == 'e' && Parameter[1] == 'c' && Parameter[2] == 'h' && Parameter[3] == 'o') {
				int Oneinterval = -1;
				int NumberInterval = 0;
				while (NumberInterval < 2) {
					char Check[1];
					FILE.read(Check, 1);
					if (Check[0] != ' ') {
						throw std::exception("Неверное заполнение конфига. Можно написать -h для детальной информации");
					}
					int interval = Oneinterval;
					FILE >> Oneinterval;
					if (Oneinterval < 0) {
						throw std::exception("Неверное заполнение конфига. Можно написать -h для детальной информации");
					}
					NumberInterval++;
					if (NumberInterval == 2 && interval > Oneinterval) {
						throw std::exception("Неверное заполнение конфига. Можно написать -h для детальной информации");
					}
					if (NumberInterval == 2) {
						FILE.read(Check, 1);
						if (Check[0] != '\n') {
							throw std::exception("Неверное заполнение конфига. Можно написать -h для детальной информации");
						}
					}
				}
			}
			else {
				throw std::exception("Неверное заполнение конфига. Можно написать -h для детальной информации");
			}
			FILE.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			throw std::exception("Неверное заполнение конфига. Можно написать -h для детальной информации");
		}
	}
	FILE.close();
};

void Preparation::CheckingFileFormat(int argc, char* File[]) {
	if (argc <= 2) {
		throw std::exception("Неверное количество файлов");
	}
	std::string FileName = File[1];
	int SizeNameFile = FileName.length();
	if (SizeNameFile >= 5 && !TXTFormat(File[1], SizeNameFile)) {
		throw std::exception("Неверный формат конфига должен быть .txt. Конфиг должен находится в начале");
	}

	for (int i = 2; i < argc; i++) {
		FileName = File[i];
		int SizeNameFile = FileName.length();
		if (SizeNameFile >= 5 && !WAVFormat(File[i], SizeNameFile)) {
			throw std::exception("Неверный формат wav файла должен быть .wav");;
		}
	}	
};