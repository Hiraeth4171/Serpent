#pragma once

#define PI 3.14159265 // double
#define MAX_RAD 6.2831853 // double

typedef struct vec2 {
	int operator[](int i) { return i == 0 ? x : y; }
	int x = 0;
	int y = 0;
} vec2;

typedef struct vec4 {
	int operator[](int i) { return i == 0 ? R : i == 1 ? G : B; }
	int R = 0;
	int G = 0;
	int B = 0;
	int A = 255;
} vec4;

typedef struct radians {
	double val = 0.0f;
	//constructor
	radians(double v) {
		if ((0 <= v) && (v <= MAX_RAD)) {
			val = v; 
		}
		else {
			while (v <= 0) v += MAX_RAD;
			while (v >= MAX_RAD) v -= MAX_RAD;
			val = v;
		}
	}
	//operators
	radians operator+(const radians &rad) const {
		return radians(rad + val);
	}
	radians operator=(double v) {
		val = v;
		return *this;
	}
	radians operator==(const radians& rad) const {
		return val == rad.val;
	}

} radians;