#pragma once

class Sound
{
private:
	int soundIDX = 0;
	int curSound = 0;
	int szSound = 0;

public:
	Sound(std::wstring pathWithName, int szSound);
	~Sound();

	void Play(bool loop);
	void Stop();
	void SetVolume(int volume);
};

class SoundManager : public Singleton<SoundManager>
{
private:
	std::map<std::wstring, Sound*> sounds;

public:
	void Create(std::wstring path, int szSound);
	void Play(std::wstring path, bool loop = false);
	void Stop(std::wstring path);
	void StopAll();

	void SetVolume(std::wstring path, int volume);
	void Reset();
};

