#pragma once
#include "GameScreen.h"
#include <fstream>
#include <iostream>
#include <vector>


#pragma once

class GameOver : public GameScreen
{

private:



public:
	GameOver(SDL_Renderer* renderer);
	~GameOver();

	bool Load();
	void Update(SDL_Event e, float deltatime);
	void Render();


};