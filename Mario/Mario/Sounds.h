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
public:
	Sounds();
	~Sounds();

	void LoadMusic(string path);
	void Play(int counts);
	void Stop();
};

