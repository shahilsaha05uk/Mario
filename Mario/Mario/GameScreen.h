#ifndef _GAMESCREEN_H_
#define _GAMESCREEN_H_

#include "SDL.h"
#include <SDL_image.h>
#include <vector>
#include <fstream>


#include "CharacterKoopa.h"
#include "Coins.h"
#include "LuigiCharacter.h"
#include "MarioCharacter.h"
#include "CharacterGoomba.h"
#include "PowBlock.h"
#include "Text.h"
#include "Sounds.h"
#include "HealthBar.h"

#pragma once
class HighScore;
class GameScreenManager;
class GameScreen
{
protected:
	SDL_Renderer* m_renderer;
	SDL_Rect* _temprect;

	GameScreenManager* game_manager;
	Texture2D* m_background_texture;
	LevelMaps* m_level_map;
	Text* _text;
	std::vector<int> ScoresVector;
	HealthBar* health[2];

	PowBlock* m_pow_block;
	LuigiCharacter* _luigi;
	MarioCharacter* _mario;

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	float timer;
	bool quit;


public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	int ScoreRecord(int score =0);
	void WriteToScoreFile();

	int mariohealthValue=100;
	int luigihealthValue = 100;
	bool playerPositionStatus;
	Sounds* _sound;

};



#endif // !_GAMESCREEN_H_