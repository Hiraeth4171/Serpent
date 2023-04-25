#pragma once
#include <stdio.h>
#include "utils/types.h"

struct Style {
	Style() : position(vec2()), backgroundColor(vec4<int>()), color(vec4<int>()), rotation(radians(0)) {}
	vec2 position;
	vec2 span; // width and height
	vec4<int> backgroundColor;
	vec4<int> color;
	radians rotation;
	void print() {
		printf("position: %d, %d\n", position.x, position.y);
		printf("span: %d, %d\n", span.x, span.y);
		backgroundColor.print();
		color.print();
		// TODO rotation
	}
};

class Object
{
public:
	float Rect[8] = { -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0, 1.0f };
	unsigned int indices[6] = { 0,1,2,2,3,0 };
	const char* Id;
	Style style;
	Object(const char *ID, Style st) : Id(ID), style(st) {}
};

