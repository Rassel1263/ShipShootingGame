#pragma once

class Time : public Singleton<Time>
{
public:
	long currentTime = 0;
	long lastTime = 0;
	long deltaTime = 0;
	float fdeltaTime = currentTime;
	float timeScale = 1.0f;
	float unscaleTime = 0.0f;

public:
	Time()
	{
		currentTime = GetTickCount64();
		lastTime = currentTime;
	}
	~Time() {};

	void Update()
	{
		currentTime = GetTickCount();
		deltaTime = currentTime - lastTime;
		fdeltaTime = (float)deltaTime / 1000.0f;
		unscaleTime = fdeltaTime;
		lastTime = currentTime;
	}
};

