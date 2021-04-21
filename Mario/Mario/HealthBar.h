#pragma once
#include <string>
#include <iostream>
#include "Character.h"
#include "constants.h"
#include "Commons.h"


using namespace std;

class HealthBar : public Character
{
private:

	int framescount;
	float frame_delay;
	int currentFrame;
	
	int healthValue = 100;

public:

	HealthBar(SDL_Renderer* renderer, Vector2D start_position, LevelMaps* maps, string imagePath);
	~HealthBar();

	void Render();

	int Update(float deltatime, Character* c1);
};

