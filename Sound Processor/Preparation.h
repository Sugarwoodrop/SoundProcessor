#pragma once
#include <fstream>
#include <iostream>
namespace Checking {
	class Preparation
	{
	private:
		bool WAVFormat(char* File,int SizeNameFile);
		bool TXTFormat(char* File, int SizeNameFile);
	public:
		void CheckingFileFormat(int argc, char* File[]);
		void CheckingConfig(char* ConfigFile, int argc);
	};
}

