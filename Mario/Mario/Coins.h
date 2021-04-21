#ifndef _COINS_H_
#define _COINS_H_


#pragma once

#include "constants.h"
#include <string>
#include <iostream>
#include "Character.h"
using namespace std;
class Coins : public Character
{
private:
	int m_total_coin_frames;
	float frame_delay;
	int currentFrame;
	Sounds* _coinSound;

public:
	Coins(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMaps* maps);
	~Coins();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void CoinSound(bool play);
};

#endif // !_COINS_H_