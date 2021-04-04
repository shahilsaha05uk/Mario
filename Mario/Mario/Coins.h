#pragma once

#include "Texture2D.h"
#include "constants.h"
#include <string>
#include <iostream>
#include "LevelMaps.h"
using namespace std;
class Coins
{
private:
	Texture2D* _texture;
	LevelMaps* m_level_maps;
	SDL_Renderer* m_renderer;
	Vector2D m_position;

	int m_total_coin_frames;
	float m_single_sprite_width; 
	float  m_single_sprite_height;
public:
	Coins(SDL_Renderer* renderer, LevelMaps* maps);
	~Coins();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	string LoadFile();

};

