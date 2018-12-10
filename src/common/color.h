#pragma once
#if !defined(COLOR_H)

class Color {
public:
	Color(int inR, int inG, int inB, int inA) : r(inR), g(inG), b(inB), a(inA) {}
	int r, g, b, a;
	int ToBit();
	Color Blend(Color other, double percent);
	Color operator-(const Color &other) {
		return Color(r - other.r, g - other.g, b - other.b, a - other.a);
	}
};

#define COLOR_H
#endif