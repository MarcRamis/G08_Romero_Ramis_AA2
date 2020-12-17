#pragma once
#include <math.h>

#include <stdlib.h>
#include <string>

struct VEC2 {
	int x, y;

	VEC2() : x(0), y(0) {};
	VEC2(int _xy) : x(_xy), y(_xy) {};
	VEC2(int _x, int _y) : x(_x), y(_y) {};

	//Magnitude
	//float mod() { return sqrt(x * x + y * y); }
};

struct RECT {
	int x, y, w, h;

	RECT() : x(0), y(0), w(0), h(0) {};
	RECT(int _x, int _y) : x(_x), y(_y), w(0), h(0) {};
	RECT(VEC2 pos, int _w, int _h) : x(pos.x), y(pos.y), w(_w), h(_h) {};
	RECT(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {};
};

enum class GameState { GAME, EXIT, MENU };

struct Font {
	const std::string id;
	std::string path;
	int size;

};

struct Color {
	uint8_t r, g, b, a;
};

struct Text {
	std::string id;
	std::string text;
	Color color;
	int w;
	int h;
};