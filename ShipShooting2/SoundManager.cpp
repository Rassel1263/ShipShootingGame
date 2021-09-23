#include "DXUT.h"
#include "SoundManager.h"

Sound::Sound(std::wstring path, int szSound)
{
	static int idx = 0;
	soundIDX = ++idx;
	this->szSound = szSound;

	for (int i = 0; i < szSound; ++i)
	{
		WCHAR buffer[256];
		wsprintf(buffer, TEXT("open %s alias %d_%d"), path.c_str(), soundIDX, i);
		mciSendString(buffer, 0, 0, 0);
		wsprintf(buffer, TEXT("play %d_%d from 0"), soundIDX, i);
		mciSendString(buffer, 0, 0, 0);
		wsprintf(buffer, TEXT("stop %d_%d"), soundIDX, i);
		mciSendString(buffer, 0, 0, 0);
	}
}

Sound::~Sound()
{
	for (int i = 0; i < szSound; ++i)
	{
		WCHAR buffer[256];
		wsprintf(buffer, TEXT("close %d_%d"), soundIDX, i);
		mciSendString(buffer, 0, 0, 0);
	}
}

void Sound::Play(bool loop)
{
	WCHAR buffer[256];
	wsprintf(buffer, L"play %d_%d from 0%s", soundIDX, curSound, (loop) ? L" repeat" : L"");
	mciSendString(buffer, 0, 0, 0);
	if (++curSound >= szSound) curSound = 0;
}

void Sound::Stop()
{
	for (int i = 0; i < szSound; ++i)
	{
		WCHAR buffer[256];
		wsprintf(buffer, L"stop %d_%d", soundIDX, i);
		mciSendString(buffer, 0, 0, 0);
	}
}

void Sound::SetVolume(int volume)
{
	for (int i = 0; i < szSound; ++i)
	{
		WCHAR buffer[256];
		wsprintf(buffer, L"setaudio %d_%d volume to %d", soundIDX, i, volume);
		mciSendString(buffer, 0, 0, 0);
	}
}

void SoundManager::Create(std::wstring name, std::wstring path, int szSound)
{
	auto sf = sounds.find(name);
	if (sf != sounds.end()) 
		return;
	sounds.insert({name, new Sound(path, szSound) });
}

void SoundManager::Play(std::wstring name, bool loop)
{
	auto sf = sounds.find(name);

	if (sf == sounds.end()) return;
	sf->second->Play(loop);
}

void SoundManager::Stop(std::wstring name)
{
	auto sf = sounds.find(name);

	if (sf == sounds.end()) return;
		sf->second->Stop();
}

void SoundManager::StopAll()
{
	for (auto sound : sounds)
		sound.second->Stop();
}

void SoundManager::SetVolume(std::wstring name, int volume)
{
	auto sf = sounds.find(name);

	if (sf == sounds.end()) return;
		sf->second->Stop();
}
