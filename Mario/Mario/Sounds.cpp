#include "Sounds.h"


Sounds::Sounds()
{

}
Sounds::~Sounds()
{

}
void Sounds::LoadMusic(string path)
{
	_music = Mix_LoadWAV(path.c_str());
	cout << "Loaded" << endl;
}
void Sounds::Play(int counts)
{
	Mix_PlayChannel(-1, _music, counts);
}
void Sounds::Stop()
{
	Mix_HaltMusic();
}
