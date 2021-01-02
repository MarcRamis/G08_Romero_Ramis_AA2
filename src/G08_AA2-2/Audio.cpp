
#include "Audio.h"

Audio::Audio()
{
	//-->SDL_Mix
	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!(Mix_Init(mixFlags) & mixFlags)) throw "Error: SDL_Mixer init";
}
Audio::~Audio()
{
	Mix_CloseAudio();
	Mix_Quit();
}

Audio* Audio::audio = nullptr;

void Audio::LoadAudio(const std::string& idSound, const std::string& path)
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		throw "Error: SDL_Mixer init";
	}
	
	m_audio[idSound] = { Mix_LoadMUS(path.c_str()) };
}
void Audio::VolumeMusic(const std::string& idSound, int volume){ Mix_VolumeMusic(MIX_MAX_VOLUME / volume); }
void Audio::PlayMusic(const std::string& idSound, int repetition){ Mix_PlayMusic(m_audio[idSound], repetition); }
bool Audio::MusicIsPaused(const std::string& idSound) { return Mix_PausedMusic(); }
void Audio::PauseMusic(const std::string& idSound) { Mix_PauseMusic(); }
void Audio::ResumeMusic(const std::string& idSound) { Mix_ResumeMusic(); }