#pragma once

#include <vector>
#include <string>
#include "types.h"

vec4<int> HEXToRGB(const char* hex) {
	int hexCode = strtol(++hex, NULL, 16); // ++ to remove #
	vec4<int> Color({ ((hexCode >> 16) & 0xFF), ((hexCode >> 8) & 0xFF), ((hexCode) & 0xFF)});
	return Color;
}

std::vector<std::string> split(std::string str, char det) {
	std::vector<std::string> out;
	std::string temp;
	for (unsigned int i = 0; i < str.length(); ++i)
	{
		if (str[i] == det) {
			printf("\n\t\t\t%c: %d\n", str.c_str()[i], str.c_str()[i]);
			if (temp != "" && temp != "\n") out.push_back(temp);
			temp = "";
		}
		else {
			temp += str[i];
		}
	}
	if (temp != "" && temp != "\n") out.push_back(temp);
	return out;
}