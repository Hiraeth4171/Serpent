#include "Generator.h"
#include "Page/utils/functions.h"

void getKeyValue(std::string str, std::string *key, std::string *value) {
	int i = 0;
	while (str[i] != '=');
	*key = str.substr(0, i);
	*value = str.substr(i);
}


void Generator::GeneratePreset(std::string presetName, std::vector<std::string> presetBody)
{
	Style S;
	for (int i = 0; i <= presetBody.size(); ++i) {
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
	for (int i = 0; i <= objectBody.size(); ++i) {
		std::string key, val;
		getKeyValue(objectBody[i], &key, &val);
		if (key == "background-color") S.backgroundColor = HEXToRGB(val.c_str());
		else if (key == "color") S.color = HEXToRGB(val.c_str());
		// else if (key == "position") S.position = ; // split
		else if (key == "rotate") S.rotation = std::atof(val.c_str()); // probably enough precision
	}
	Object out(ID.c_str(), &S);
}

void Generator::GeneratePage(std::vector<std::string> Body)
{
	printf(Body[0].c_str());
	for (int i = 0; i <= Body.size(); ++i) {
		std::string key, val;
		getKeyValue(Body[i], &key, &val);
		if (key == "background-color") m_Page->m_BackgroundColor = HEXToRGB(val.c_str());
		//else if (key == "color") S.color = HEXToRGB(val.c_str());
		// else if (key == "position") S.position = ; // split
		//else if (key == "rotate") S.rotation = std::atof(val.c_str()); // probably enough precision
	}
}

