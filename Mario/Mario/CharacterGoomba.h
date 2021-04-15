#pragma once

#include "Character.h"

class CharacterGoomba : public Character
{
private:

	bool m_injured;
	float m_injured_time;
	float m_movement_speed;

	void FlipRightWayUp();

public:
	CharacterGoomba(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMaps* maps, FACING start_facing, float movement_speed);
	~CharacterGoomba();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void TakeDamage();
	bool GetInjured() { return m_injured; }

	void GoombaAnimation(float deltaTime, SDL_Event e);
};

