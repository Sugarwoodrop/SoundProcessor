#include "Config.h"
using namespace ConfigFile;

Config::Config(char* Config) : NumberConverter(1), ConfigFile(Config){};

int* Config::SearchConverter() {
	std::ifstream FILE(ConfigFile);
	if (!FILE) {
		throw std::exception("Не найден файл");
	}
	int ConverterParametr[4];
	char Parameter[4];
	int Converter = 0;
	while (!FILE.eof()) {
		FILE.read(Parameter, 4);
		if (Parameter[0] == '#') {
			FILE.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (Parameter[0] == 'm' || Parameter[0] == 'e') {
			Converter++;
			if (Parameter[0] == 'm' && Parameter[1] == 'u' && Parameter[2] == 't' && Parameter[3] == 'e' && Converter == NumberConverter) {
				ConverterParametr[0] = 1;
				ConverterParametr[1] = 0;
				int Oneinterval = -1;
				int NumberInterval = 0;
				while (NumberInterval < 2) {
					NumberInterval++;
					char Check[1];
					FILE.read(Check, 1);
					int interval = Oneinterval;
					FILE >> Oneinterval;
					ConverterParametr[NumberInterval+1] = Oneinterval;
				}
			}
			else if (Parameter[0] == 'm' && Parameter[1] == 'i' && Parameter[2] == 'x' && Parameter[3] == ' ' && Converter == NumberConverter) {
				ConverterParametr[0] = 2;
				char argument[1];
				FILE.read(argument, 1);
				int NumberFileMix = 0;
				FILE >> NumberFileMix;
				ConverterParametr[1] = NumberFileMix;
				NumberFileMix = 0;
				int NumberInterval = 0;
				while (NumberInterval < 2) {
					NumberInterval++;
					char Check[1];
					FILE.read(Check, 1);
					int interval = NumberFileMix;
					FILE >> NumberFileMix;
					ConverterParametr[NumberInterval+1] = NumberFileMix;
				}
			}
			else if (Parameter[0] == 'e' && Parameter[1] == 'c' && Parameter[2] == 'h' && Parameter[3] == 'o' && Converter == NumberConverter) {
				ConverterParametr[0] = 3;
				ConverterParametr[1] = 0;
				int Oneinterval = -1;
				int NumberInterval = 0;
				while (NumberInterval < 2) {
					NumberInterval++;
					char Check[1];
					FILE.read(Check, 1);
					int interval = Oneinterval;
					FILE >> Oneinterval;
					ConverterParametr[NumberInterval +1] = Oneinterval;
				}
			}
			FILE.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	NumberConverter++;
	FILE.close();
	return ConverterParametr;
};

void Config::CountNumberConverter() {
	std::ifstream FILE(ConfigFile);
	if (!FILE) {
		throw std::exception("Не найден файл");
	}
	char Parameter[4];
	while (!FILE.eof()) {
		FILE.read(Parameter, 4);
		if (Parameter[0] == '#') {
			FILE.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (Parameter[0] == 'm' || Parameter[0] == 'e') {
			if (Parameter[0] == 'm' && Parameter[1] == 'u' && Parameter[2] == 't' && Parameter[3] == 'e') {
				QuantityConverter++;
			}
			else if (Parameter[0] == 'm' && Parameter[1] == 'i' && Parameter[2] == 'x' && Parameter[3] == ' ') {
				QuantityConverter++;
			}
			else if (Parameter[0] == 'e' && Parameter[1] == 'c' && Parameter[2] == 'h' && Parameter[3] == 'o') {
				QuantityConverter++;
			}
			FILE.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	FILE.close();
};
int Config::QuantityConverters() {
	return QuantityConverter;
};