#pragma once

#include <string>
#include "types.h"

vec4<int> HEXToRGB(const char* hex) {
	// ignore #
	int hexCode = std::atoi(hex+1);
	vec4<int> Color({ ((hexCode >> 16) & 0xFF) / 255, ((hexCode >> 8) & 0xFF) / 255, ((hexCode) & 0xFF) / 255 });
	return Color;
}