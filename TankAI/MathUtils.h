#pragma once

#include <math.h>
using namespace std;

static class MathUtils
{
public:
	static double sigmoid(double x) { return 1 / 1 + exp(-x); }
private:

};
