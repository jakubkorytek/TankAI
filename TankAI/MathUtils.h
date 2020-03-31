#pragma once

#include <math.h>
using namespace std;

static class MathUtils
{
public:
	static double sigmoid(double x) { return (1.0f / (1.0f + exp(-x))); }

	static double deriverateSigmoid(double y) { return y * (1 - y); }

private:

};
