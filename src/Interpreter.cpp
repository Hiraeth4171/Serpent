#include "Interpreter.h"

int Interpreter::Interpret(int argc, char** argv) {
	char* filepath = argv[1];
	std::string line = "";
	std::vector<std::string> lines = Preprocesser::Process(argc, argv, &line);

	for (unsigned int i = 0; i < lines.size(); ++i) {
		printf("%c", lines[i].c_str()[0]);
		// this will be pre-processed, every line is either an object or a preset.
		if (lines[i][0] == '(') { //no id - so it's a preset
			std::string presetName = Interpreter::getContent(lines[i].c_str(), lines[i].length(), '(', ')');
			std::string presetBody = Interpreter::getContent(lines[i].c_str(), lines[i].length(), '{', '}');
			m_Generator.GeneratePreset(presetName, split(presetBody, ';'));
		}
		else if (lines[i].c_str()[0] == '[') { //id - known or not
			printf("somethin");
			std::string content = Interpreter::getContent(lines[i].c_str(), lines[i].length(), '[', ']');
			std::string body = Interpreter::getContent(lines[i].c_str(), lines[i].length(), '{', '}');

			printf("\n\n%s, %s\n\n", content.c_str(), body.c_str());

			if (content == "body") {
				m_Generator.GeneratePage(split(body, ';'));
				printf("Finished Generating Page");
			}
			else {
				printf("Object Generation Started.");
				m_Generator.GenerateObject(content, split(body, ';'));
			}
		}
		else {
			printf("%d", lines[i].c_str()[0]);
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
		if (foundFlag && ch != start && ch != end) out += ch;
	}
	return out;
}

std::vector<std::string> Preprocesser::Process(int argc, char* argv[], std::string *out) {
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
		;
		return splitLine(&outLine);
}

std::vector<std::string> Preprocesser::splitLine(std::string* line)
{
	std::vector<std::string> out;
	bool foundFlag = false;
	int counter = 0;
	std::string temp = "";
	for (unsigned int i = 0; i < line->length(); ++i) {
		if (counter == 0 && foundFlag) {
			if (temp != "") out.push_back(temp);
			temp = "";
			foundFlag = false;
		}
		if (line->c_str()[i] == '{') {
			counter++; foundFlag = true;
		}
		if (line->c_str()[i] == '}') counter--;
		temp += line->c_str()[i];
	}
	printf(line->c_str());
	return out;
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
	while (*line != '\0') {
		if (*line > 33) {
			*ptr++ = *line;
		}
		line++;
	}
	*ptr = '\0';
	return out;
}
