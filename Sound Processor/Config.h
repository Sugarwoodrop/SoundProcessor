#pragma once
#include <fstream>
#include <iostream>

namespace ConfigFile {
	class Config
	{
	private:
		int NumberConverter;
		int QuantityConverter;
		char* ConfigFile;
	public:
		Config(char* Config);
		int QuantityConverters();
		void CountNumberConverter();
		int* SearchConverter();
	};
}

