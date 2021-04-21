#include "Sounds.h"


Sounds::Sounds()
{

}
Sounds::~Sounds()
{

}
void Sounds::LoadMusic(string path)
{
	//_music = Mix_LoadWAV(path.c_str());
	_mixMusic = Mix_LoadMUS(path.c_str());
}
void Sounds::Play(int counts)
{
	//Mix_PlayChannel(-1, _music, counts);
	Mix_PlayMusic(_mixMusic, counts);
}
void Sounds::Pause()
{
	Mix_PauseMusic();
}
void Sounds::Resume()
{
	Mix_ResumeMusic();
}
void Sounds::Stop()
{
	Mix_HaltMusic();
}

