#pragma once
#include "utils/types.h"

struct Style {
	Style() : position(vec2()), backgroundColor(vec4<int>()), color(vec4<int>()), rotation(radians(0)) {}
	vec2 position;
	vec4<int> backgroundColor;
	vec4<int> color;
	radians rotation;
};

class Object
{
private:
	const char* Id;
	Style style;
public:
	Object(const char *ID, Style *st) : Id(ID), style(*st) {}
};

