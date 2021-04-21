#ifndef _LUIGICHARACTER_H_
#define _LUIGICHARACTER_H_
#pragma once

#include "Character.h"

class LuigiCharacter : public Character
{
private:


public:
	LuigiCharacter(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMaps* maps);
	~LuigiCharacter();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void LuigiKeyboard(float deltatime, SDL_Event e);
	void LuigiAnimation(float deltaTime, SDL_Event e);
	void JumpSound(bool play);


};

#endif // !_LUIGICHARACTER_H_