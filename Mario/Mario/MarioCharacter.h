#ifndef _MARIOCHARACTER_H_
#define _MARIOCHARACTER_H_
#pragma once

#include "Character.h"
#include "Sounds.h"

class MarioCharacter : public Character
{
private:
	bool dead_mario;

public:
	MarioCharacter(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMaps* maps);
	~MarioCharacter();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void MarioKeyboard(float deltatime, SDL_Event e);
	//void MarioAnimation(float deltaTime, SDL_Event e, bool jump);
	void MarioAnimation(float deltaTime, SDL_Event e);
	bool deadMario(bool b =false);
	void JumpSound(bool play);
};

#endif // !_MARIOCHARACTER_H_
