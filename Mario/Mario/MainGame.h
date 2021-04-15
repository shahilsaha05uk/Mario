#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Commons.h"
#include "GameScreenManager.h"
#include "Sounds.h"
#include "constants.h"
#include "Texture2D.h"
//#include "GameScreen.h"
#include "MainMenu.h"
#include "HighScore.h"
class MainGame
{
private:
	SDL_Window* g_window = nullptr;
	SDL_Renderer* g_renderer = nullptr;
	GameScreenManager* game_screen_manager;
	Sounds* _sounds;
	MainMenu* _menu;
	SCREENS _screen;
	Uint32 g_old_time;
	float angle = 0.0f;
	bool quit;
	SDL_Event e;

	//File stream
	ofstream outfile;
	int health;
	HighScore* score;
protected:
	//GameScreen* _score;
	int _scores;
public:
	MainGame();
	~MainGame();

	bool InitSDL();
	void Render();
	bool Update();

	void trial(SDL_Event e);

	void CloseSDL();
	void PlayBackgroundMusic();

	bool DefaultScreen();
	void UpdateScoreFile(bool b=false);



};

