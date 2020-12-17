#pragma once

#include <SDL_mixer.h>

#include <unordered_map>
#include <string>

class Audio 
{
private:

	std::unordered_map<std::string, Mix_Music*> m_audio;

	static Audio* audio;

protected:
	Audio();
	~Audio();

public:

	static Audio* GetInstance()
	{
		if (audio == nullptr) { audio = new Audio; }
		return audio;
	};

	void LoadAudio(const std::string& idSound);
	void PlayMusic(const std::string& idSound, int repetition);
	void VolumeMusic(const std::string& idSound, int volume);
	bool MusicIsPaused(const std::string& idSound);
	void PauseMusic(const std::string& idSound);
	void ResumeMusic(const std::string& idSound);
};