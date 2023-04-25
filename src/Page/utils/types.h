#pragma once

#define PI 3.14159265 // double
#define MAX_RAD 6.2831853 // double

typedef struct vec2 {
	vec2() {
		x = 0;
		y = 0;
	};
	vec2(int _x, int _y) {
		x = _x;
		y = _y;
	}
	int operator[](int i) { return i == 0 ? x : y; }
	vec2 operator+ (const vec2& other) { return vec2(x + other.x, y + other.y); }
	int x = 0;
	int y = 0;
} vec2;

typedef struct vec2f {
	float operator[](int i) { return i == 0 ? x : y; }
	float x = 0.0;
	float y = 0.0;
} vec2f;

template<typename T>
struct vec4 {
	T operator[](int i) { return i == 0 ? R : i == 1 ? G : B; }
	T R;
	T G;
	T B;
	T A;
	void print() {
		printf("R:%d, G:%d, B:%d\n", R, G, B);
	}
};

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