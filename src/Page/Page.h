#pragma once
#include "../Renderer.h"
#include "Object.h"
#include <vector>

class Page
{
private:
	Renderer *m_Renderer;
	std::vector<Object> m_Objects;
public:
	void Draw();
};