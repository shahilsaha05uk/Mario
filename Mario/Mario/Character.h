#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#pragma once

using namespace std;


#include "SDL.h"
#include <iostream>
#include <SDL_mixer.h>
#include "Commons.h"
#include "LevelMaps.h"
#include "Texture2D.h"
#include "Constants.h"
#include "Sounds.h"
#include "Text.h"


class Texture2D;
class CharacterKoopa;
class GameScreen;
class Character
{
private:


protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	FACING m_facing_direction;
	GameScreen* _screen;
	LevelMaps* m_current_level_map;

	//collision
	float m_collision_radius;

	bool m_alive;

	//movement members
	bool m_moving_right;
	bool m_moving_left;

	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;

	//sprite members
	float m_single_sprite_w;
	float m_single_sprite_h;

	//animation members
	int TotalframesCount;
	int currentFrameCount;
	float mtimer;
	const float fixedtimer = 10.0f;
	int setframe;

	//Sounds members
	Sounds* _jumpSound;

public:
	Character(SDL_Renderer* renderer, string imagepath, Vector2D start_position, LevelMaps* maps);
	~Character();

	Character();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();

	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

	float GetCollisionRadius();
	Rect2D GetCollisionBox();

	bool Isjumping() { return m_jumping; }
	virtual void CancelJump() { m_jumping = false; }

	void SetAlive(bool isAlive) { m_alive = isAlive; }
	bool GetAlive() { return m_alive; }

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void AddGravity(float deltaTime);
	virtual void Jump();

};

#endif // !_CHARACTER