#pragma once
#include "../Renderer.h"
#include "Object.h"
#include <vector>

struct ObjectTree {
	std::vector<Object> Children = {};
	int size() {
		return Children.size();
	}
};

struct Preset {
	Preset(Style* st) : style(*st) {}
	Preset() : style(Style()) {}
	Style style;
	void print(void) {
		printf("%d", style.backgroundColor[0]);
	}
};
class Page
{
private:
	Renderer *m_Renderer;
	ObjectTree m_Objects;
public:
	vec4<int> m_BackgroundColor;
	int m_width;
	int m_height;
	char* m_title;
	Page(Renderer* Renderer, vec4<int> BGColor, int width, int height, char* title);
	Page(Renderer* Renderer) : m_BackgroundColor({0,0,0,255}), m_width(640), m_height(480), m_title((char*)"Serpent") {};
	~Page();
	void setRenderer(Renderer* renderer) {
		m_Renderer = renderer;
	}
	void Draw();
};