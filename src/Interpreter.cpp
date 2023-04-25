#include "Interpreter.h"
#include "Generator.h"

int Interpreter::Interpret(int argc, char* argv[]) {
	char* filepath = argv[1];
	printf("%s\n", filepath);
	std::vector<std::string> lines = readFile(filepath);
	for (unsigned int i = 0; i < lines.size(); ++i) {
		// this will be pre-processed, every line is either an object or a preset.
		if (lines[i][0] == '(') { //no id - so it's a preset
			std::string presetName = Interpreter::getContent(lines[i].c_str(), lines[i].length(), '(', ')');
			std::string presetBody = Interpreter::getContent(lines[i].c_str(), lines[i].length(), '{', '}');
			Generator::GeneratePreset(presetName, Interpreter::split(presetBody, ';'));
		}
		else if (lines[i][0] == '[') { //id - known or not
			if (Interpreter::getContent(lines[i].c_str(), lines[i].length(), '[', ']') == "body") {
				std::string body = Interpreter::getContent(lines[i].c_str(), lines[i].length(), '{', '}');
				Generator::GeneratePage(Interpreter::split(body, ';'));
			}
		}
	}
	return 0;
}

std::string Interpreter::getContent(const char* string, unsigned int length, char start, char end) {
	bool foundFlag = false;
	int count = 0;
	std::string out = "";
	for (unsigned int i = 0; i < length; i++) {
		if (count == 0 && foundFlag) break;
		char ch = string[i];
		if (ch == start) { count += 1; foundFlag = true; }
		if (ch == end) { count -= 1; }
		if (foundFlag) out += ch;
	}
	return out;
}

int Preprocesser::Process(int argc, char* argv[]) {
		char* filepath = argv[1];
		std::string outLine;
		std::vector<std::string> lines = Interpreter::readFile(filepath);
		char goBack = 0;
		for (unsigned int i = 0; i < lines.size(); i++) {
			std::string line = std::string(stripString(lines[i].c_str(), lines[i].length()));
			if (line == "") continue;
			if (line[0] == '#') continue; // consider these comments for now
			outLine += line;
		}
		splitLine(&outLine);
		printf(outLine.c_str());
		return 0;
}

void Preprocesser::splitLine(std::string* line)
{
	bool foundFlag = false;
	int counter = 0;
	for (unsigned int i = 0; i < line->length(); i++) {
		if (counter == 0 && foundFlag) {
			line->insert(i, "\n");
			foundFlag = false;
		}
		if (line->c_str()[i] == '{') {
			counter++; foundFlag = true;
		}
		if (line->c_str()[i] == '}') counter--;
	}
}

char* Preprocesser::stripString(const char* line, int len)
{
	char* out = (char*)calloc(len, sizeof(char));
	if (out == NULL) {
		//ERR
		free(out);
		return NULL;
	}
	char* ptr = out;
	int i = 0;
	while (*line != '\0') {
		if (*line != ' ' && *line != '\t' && *line != '\n') {
			*ptr++ = *line;
		}
		line++;
	}
	*ptr = '\0';
	return out;
}
