#pragma once

#include <string>
#include <iostream>

#include "SDL.h"
#include <SDL_mixer.h>
using namespace std;
class Sounds
{
private:

	Mix_Chunk* _music;
	Mix_Music* _mixMusic;
public:
	Sounds();
	~Sounds();

	void LoadMusic(string path);
	void Play(int counts);
	void Pause();
	void Resume();
	void Stop();
};

