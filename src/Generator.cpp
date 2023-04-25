#include "Generator.h"

void getKeyValue(std::string str, std::string *key, std::string *value) {
	int i = 0;
	while (str[i++] != ':');
	*key = str.substr(0, i-1);
	*value = str.substr(i);
}


void Generator::GeneratePreset(std::string presetName, std::vector<std::string> presetBody)
{
	Style S;
	for (size_t i = 0; i <= presetBody.size(); ++i) {
		std::string key, val;
		getKeyValue(presetBody[i], &key, &val);
		if (key == "background-color") S.backgroundColor = HEXToRGB(val.c_str());
		else if (key == "color") S.color = HEXToRGB(val.c_str());
		// else if (key == "position") S.position = ; // split
		else if (key == "rotate") S.rotation = std::atof(val.c_str()); // probably enough precision
	}
	Preset out(&S);
	out.print();
}

void Generator::GenerateObject(std::string ID, std::vector<std::string> objectBody)
{
	Style S;
	printf("proof");
	for (size_t i = 0; i < objectBody.size(); ++i) {
		printf(objectBody[i].c_str());
		std::string key, val;
		getKeyValue(objectBody[i], &key, &val);
		if (key == "background-color") S.backgroundColor = HEXToRGB(val.c_str());
		else if (key == "color") S.color = HEXToRGB(val.c_str());
		// else if (key == "position") S.position = ; // split
		else if (key == "rotate") S.rotation = std::atof(val.c_str()); // probably enough precision
		else if (key == "position") {
			std::vector<std::string> info = split(val, ',');
			S.position.x = std::atoi(info[0].c_str());
			S.position.y = std::atoi(info[1].c_str());
		}
		else if (key == "span") {
			std::vector<std::string> info = split(val, ',');
			S.span.x = std::atoi(info[0].c_str());
			S.span.y = std::atoi(info[1].c_str());
		}
	}
	Object out(ID.c_str(), S);
	printf("Object [%s] Added.\n\n", ID.c_str());
	out.style.print();
	m_Page->AddObject(&out);
}

void Generator::GeneratePage(std::vector<std::string> Body)
{
	for (size_t i = 0; i < Body.size(); ++i) {
		printf("run");
		std::string key, val;
		getKeyValue(Body[i], &key, &val);
		printf("\n%s\n", key.c_str());
		if (key == "background-color") m_Page->m_BackgroundColor = HEXToRGB(val.c_str());
		//else if (key == "color") S.color = HEXToRGB(val.c_str());
		// else if (key == "position") S.position = ; // split
		//else if (key == "rotate") S.rotation = std::atof(val.c_str()); // probably enough precision
	}
}

