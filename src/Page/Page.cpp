#include "Page.h"

Page::Page(Renderer* renderer, vec4<int> BGColor, int width = 640, int height = 480, char* title = (char*)"Untitled") {
	m_Renderer = renderer;
	m_BackgroundColor = BGColor;
	m_width = width;
	m_height = height;
	m_title = title;
}

Page::~Page()
{
}

void Page::Draw()
{
	m_Renderer->ColorClear(m_BackgroundColor);
	for (unsigned int i = 0; i < m_Objects.size(); ++i)
	{
		// draw backdrop
		// draw per layer
	}
}
