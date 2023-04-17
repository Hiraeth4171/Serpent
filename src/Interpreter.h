#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>

class Interpreter {
public:
	int Interpret(int argc, char* argv[]);
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
private:
	int Process(int argc, char* argv[]);
	void splitLine(std::string* line);
	char* stripString(const char* line, int len);
};

