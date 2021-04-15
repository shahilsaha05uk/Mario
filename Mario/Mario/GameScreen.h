#ifndef _GAMESCREEN_H_
#define _GAMESCREEN_H_

#include "SDL.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Commons.h"
#include "LevelMaps.h"
#include <fstream>
#include "Texture2D.h"
#include "CharacterKoopa.h"
#include "Coins.h"
#include "LuigiCharacter.h"
#include "MarioCharacter.h"
#include "PowBlock.h"
#include "Text.h"
#include "Sounds.h"
#pragma once

class HighScore;
class GameScreenManager;

class GameScreen
{
protected:
	SDL_Renderer* m_renderer;

	GameScreenManager* game_manager;

	Texture2D* m_background_texture;
	MarioCharacter* _mario;
	LevelMaps* m_level_map;
	PowBlock* m_pow_block;
	Coins* m_coins;

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	float timer;
	bool quit;
	//Text render variables
	Text* _text;
	SDL_Rect* _temprect;

	//Text * scoretext;
	Text* _mario_healthText;
	Text* _luigi_healthText;
	int health = 100;
	//int mario_health = 100;
	//int luigi_health = 100;
	int healthtimer;
	const int fixed_health_timer = 10.0f;
	SDL_Rect* luigiHealthrect;
	SDL_Rect* marioHealthrect;

	//Score
	void LoadScores();


public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	int ScoreRecord(int score =0);
	void MarioHealth();
	int LuigiHealth();


	int mario_health = 100;
	int luigi_health = 100;

	LuigiCharacter* _luigi;

};



#endif // !_GAMESCREEN_H_