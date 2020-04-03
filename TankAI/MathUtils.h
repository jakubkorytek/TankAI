#pragma once

#include <math.h>

#define PI 3.14159265358979323846

using namespace std;

static class MathUtils
{
public:
	static double sigmoid(double x) { return (1.0f / (1.0f + exp(-x))); }

	static double derivativeSigmoid(double y) { return sigmoid(y) * (1 - sigmoid(y)); }

	static double derivativeTanh(double x) { return 1 - (x * x);}

	static double degreesToRad(double x) { return (x * PI) / 180; }

	static double radToDegrees(double x) { return (x * 180) / PI; }

	static int projectileMotionFunction(int x, int y, float velocity, float angle, double gravity) {
		return y - (x*tan(angle)) + (gravity*x*x) / (2 * velocity* velocity*cos(angle)*cos(angle));
	}
	static double normalize(int value, int maxValue)
	{
		return (value * 1.0f / maxValue) * 1.0f;
	}

	static double normalize(double value, double maxValue)
	{
		return (value / maxValue);
	}
	
	static double denormalize(double value, int maxValue)
	{
		return value * maxValue;
	}

	static double denormalize(double value, double maxValue)
	{
		return value * maxValue;
	}


private:

};
