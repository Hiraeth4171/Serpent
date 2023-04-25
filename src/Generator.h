#pragma once

#include "Page/Page.h"

class Generator
{
private:
	static std::vector<Preset>* m_Presets;
public:
	static Page *m_Page;
	//static void setPage(Page* page) { m_Page = page; };
	//static Page *getPage() { return m_Page; }
	static void GeneratePreset(std::string presetName, std::vector<std::string> presetBody);
	static void GenerateObject(std::string ID, std::vector<std::string> objectBody);
	static void GeneratePage(std::vector<std::string> Body);
};

