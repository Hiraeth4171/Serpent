#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>

class Interpreter {
public:
	static int Interpret(int argc, char* argv[]);
	static std::vector<std::string> readFile(char* filepath) {
		std::ifstream stream(filepath);
		std::vector<std::string> lines;
		std::string line;
		while (std::getline(stream, line)) lines.push_back(line);
		return lines;
	}
	static std::vector<std::string> split(std::string str, char det) {
		std::vector<std::string> out;
		std::string temp;
		for (unsigned int i = 0; i < str.length(); ++i)
		{
			temp += str[i];
			if (str[i] == det) {
				out.push_back(temp);
				temp = "";
			}
		}
		return out;
	}
	static std::string getContent(const char* string, unsigned int length, char start, char end);
};

class Preprocesser {
private:
	int Process(int argc, char* argv[]);
	void splitLine(std::string* line);
	char* stripString(const char* line, int len);
};
