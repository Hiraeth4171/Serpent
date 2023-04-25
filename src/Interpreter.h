#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include "Generator.h"

class Interpreter {
public:
	Generator m_Generator;
	Interpreter(Generator gen) : m_Generator(gen) {}
	int Interpret(int argc, char** argv);
	static std::vector<std::string> readFile(char* filepath) {
		std::ifstream stream(filepath);
		std::vector<std::string> lines;
		std::string line;
		while (std::getline(stream, line)) lines.push_back(line);
		return lines;
	}
	std::string getContent(const char* string, unsigned int length, char start, char end);
};

class Preprocesser {
public:
	static std::vector<std::string> Process(int argc, char* argv[], std::string *out);
	static std::vector<std::string> splitLine(std::string* line);
	static char* stripString(const char* line, int len);
};
