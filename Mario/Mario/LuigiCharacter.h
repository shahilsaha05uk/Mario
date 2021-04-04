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

	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();
};

#endif // !_LUIGICHARACTER_H_