#pragma once
#ifndef UNIVERSE_SPACE_SMATH
#define UNIVERSE_SPACE_SMATH
#define SPi  3.141592653578
#define SPRECI  0.000001
#define SMAX(val1, val2) (val1 > val2) ? val1 : val2
#define SMIN(val1, val2) (val1 < val2) ? val1 : val2
#define SEqual(val1, val2, preci) ((1 + preci >= (val1 / val2) && (val1 / val2) >= 1 - preci)) ? true : false
#define SEqual(val1, val2, preci) ((1 + preci >= (val1 / val2) && (val1 / val2) >= 1 - preci)) ? true : false
#define SEqualDouble(val1, val2) Equal(val1, val2, SPRECI)
#include <cmath>
#include <vector>
struct SEquation {
	double a;
	double b;
	double c;
	double d;
	SEquation(double _a = 0, double _b = 0, double _c = 0, double _d = 0) { a = _a; b = _b; c = _c; d = _d; }
	// 0 = a*x + b*y + c*z + d
};
struct SRGB {
	int R;
	int G;
	int B;
	SRGB(int r = 255, int g = 255, int b = 255) { R = r; G = g; B = b; }
};
typedef std::vector<SEquation> SEquationS;
#endif // !UNIVERSE_SPACE_SMATH
