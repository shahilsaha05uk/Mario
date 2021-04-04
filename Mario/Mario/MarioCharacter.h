#ifndef _MARIOCHARACTER_H_
#define _MARIOCHARACTER_H_
#pragma once

#include "Character.h"

class MarioCharacter : public Character
{
private:
	Sounds* _jumpSound;


public:
	MarioCharacter(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMaps* maps);
	~MarioCharacter();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

	void JumpSound(bool play);
};

#endif // !_MARIOCHARACTER_H_
