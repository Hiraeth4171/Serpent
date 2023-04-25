#pragma once

#include "Page/Page.h"
#include "Page/utils/functions.h"

class Generator
{
private:
	static std::vector<Preset>* m_Presets;
public:
	Page *m_Page;
	Generator(Page *p): m_Page(p) {}
	//static void setPage(Page* page) { m_Page = page; };
	//static Page *getPage() { return m_Page; }
	void GeneratePreset(std::string presetName, std::vector<std::string> presetBody);
	void GenerateObject(std::string ID, std::vector<std::string> objectBody);
	void GeneratePage(std::vector<std::string> Body);
};

