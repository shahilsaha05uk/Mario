#ifndef _CHARACTERKOOPA_H_
#define _CHARACTERKOOPA_H_

#pragma once
#include "Character.h"

class CharacterKoopa : public Character
{
private:

	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;
	float m_movement_speed;

	void FlipRightWayUp();

public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMaps* maps, FACING start_facing, float movement_speed);
	~CharacterKoopa();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void TakeDamage();
	void Jump();
	bool GetInjured() { return m_injured; }
	void KoopaMovements(float deltaTime);
};

#endif // !_CHARACTERKOOPA