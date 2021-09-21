#pragma once
class ObstacleManager
{
public:
	float gDistance = 0.0f;
	float rDistnace = 0.0f;

	float gMaxDistance = 0.0f;
	float rMaxDistance = 0.0f;

	void Init(float gMax, float rMax);
	void Update(float deltaTime);
};

