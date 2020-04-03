#pragma once

#include <vector>
#include "Target.h"
#include "MathUtils.h"

using namespace std;

class TrainingData
{
public:
	TrainingData() {};
	TrainingData(vector<double> inputs, vector<double> output);
	~TrainingData();

	vector<double> inputs;
	vector<double> output;

	static vector<TrainingData> generateTrainingData(int x, int y, int trainingSize, int minAngle, int maxAngle, int angleStep, int minPower, int maxPower, int powerStep, float velocity, double gravity, int screenWidth, int screenHeight);
	static bool checkIfTargetIsOnTrajectory(int x, int y, double power, float velocity, float angle, double gravity, Target *target, int width);
	static vector<double> getCorrectData(int x, int y, int minAngle, int maxAngle, int angleStep, int minPower, int maxPower, int powerStep, float velocity, double gravity, int screenWidth, int screenHeight);

private:

};

inline TrainingData::TrainingData(vector<double> inputs, vector<double> output)
{
	this->inputs = inputs;
	this->output = output;
}

inline TrainingData::~TrainingData()
{
}

inline vector<TrainingData> TrainingData::generateTrainingData(int x, int y, int trainingSize, int minAngle, int maxAngle, int angleStep, int minPower, int maxPower, int powerStep, float velocity, double gravity, int screenWidth, int screenHeight)
{
	vector<TrainingData> dataSet;
	Target target;
	target.createNew();

	for (int i = 0; i < trainingSize; i++)
	{
		target.createNew();
		int angle = minAngle;
		bool targetFound = false;
		for (angle; angle <= maxAngle; angle += angleStep)
		{
			if(!targetFound)
			{
				for (int power = minPower; power <= maxPower; power += powerStep)
				{
					if (checkIfTargetIsOnTrajectory(x, y, power, velocity, (angle * PI) / 180, gravity, &target, screenWidth))
					{
						TrainingData trainingData;

						vector<double> inputs;
						inputs.push_back(MathUtils::normalize(x, screenWidth));
						inputs.push_back(MathUtils::normalize(y, screenHeight));
						inputs.push_back(MathUtils::normalize(target.getX(), screenWidth));
						inputs.push_back(MathUtils::normalize(target.getY(), screenHeight));
						inputs.push_back(MathUtils::normalize(target.getHeight(), screenHeight));
						inputs.push_back(MathUtils::normalize(gravity, 100.f));

						vector<double> outputs;
						outputs.push_back(MathUtils::normalize(angle, maxAngle));
						outputs.push_back(MathUtils::normalize(power, maxPower));

						trainingData.inputs = inputs;
						trainingData.output = outputs;

						dataSet.push_back(trainingData);
						targetFound = true;
						break;
					}
				}
			}
		}
	}
	return dataSet;
}

inline bool TrainingData::checkIfTargetIsOnTrajectory(int x, int y, double power, float velocity, float angle, double gravity, Target * target, int width)
{
	bool wasTargetReached = false;
	int posY;

	int j = 0;
	for (int i = x; i < width; i++)
	{
		posY = y - (j*tan(angle)) + (gravity*j*j) / (2 * (power*velocity)* (power*velocity)*cos(angle)*cos(angle));
		j++;

		if (target->getX() == i && (target->getY() < posY && (target->getHeight() + target->getY()) > posY))
		{
			wasTargetReached = true;
			break;
		}
	}

	return wasTargetReached;
}

inline vector<double> TrainingData::getCorrectData(int x, int y, int minAngle, int maxAngle, int angleStep, int minPower, int maxPower, int powerStep, float velocity, double gravity, int screenWidth, int screenHeight)
{
	vector<double> outputs;
	Target target;
	target.createNew();
	bool targetFound = false;
	for (int angle = minAngle; angle <= maxAngle; angle += angleStep)
	{
		if (!targetFound)
		{
			for (int power = minPower; power <= maxPower; power += powerStep)
			{
				if (checkIfTargetIsOnTrajectory(x, y, power, velocity, (angle * PI) / 180, gravity, &target, screenWidth))
				{
					outputs.push_back(MathUtils::normalize(angle, maxAngle));
					outputs.push_back(MathUtils::normalize(power, maxPower));
					targetFound = true;
					break;
				}
			}
		}
	}
	return outputs;
}




