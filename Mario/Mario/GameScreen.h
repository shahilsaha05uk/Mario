#ifndef _GAMESCREEN_H_
#define _GAMESCREEN_H_

#include "SDL.h"
#include "Texture2D.h"

#pragma once
class GameScreen
{
protected:
	SDL_Renderer* m_renderer;

public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
};



#endif // !_GAMESCREEN_H_