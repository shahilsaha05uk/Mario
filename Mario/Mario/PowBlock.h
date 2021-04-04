#ifndef _POWBLOCK_H_
#define _POWBLOCK_H_
#pragma once

#include "Commons.h"
#include "SDL.h"
#include "Texture2D.h"
#include "LevelMaps.h"
#include <iostream>
#include <string>

class PowBlock
{
private:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	LevelMaps* m_level_map;

	float m_single_sprite_w;
	float m_single_sprite_h;
	int m_num_hits_left;
public:
	
	PowBlock(SDL_Renderer* renderer, LevelMaps* maps);
	~PowBlock();

	virtual void Render();
	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y ,m_single_sprite_w, m_single_sprite_h); }
	void TakeHit();
	bool IsAvailable() { return m_num_hits_left > 0; }
};

#endif // !_POWBLOCK_H_