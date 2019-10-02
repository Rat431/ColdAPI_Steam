#pragma once
#include "../public SDK/ISteamMusic001.h"
#include "../Bridge.h"


class SteamMusicIn001 : public ISteamMusic001
{
public:
	bool BIsEnabled()
	{
		return false;
	}
	bool BIsPlaying()
	{
		return false;
	}

	AudioPlayback_Status GetPlaybackStatus()
	{
		return AudioPlayback_Undefined;
	}

	void Play()
	{
		return;
	}
	void Pause()
	{
		return;
	}
	void PlayPrevious()
	{
		return;
	}
	void PlayNext()
	{
		return;
	}

	void SetVolume(float flVolume)
	{
		return;
	}
	float GetVolume()
	{
		return 0;
	}
};