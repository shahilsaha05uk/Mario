#pragma once


#include "SDL.h"
#include "Commons.h"
#include "GameScreenManager.h"
#include "GameScreen.h"
#include "SDL.h"

class Texture2D;
class GameScreenManager;
class TitleScreen : GameScreen
{
private:
	Texture2D* title_screen;
	GameScreenManager* titleScreenChange;
	

public:

	TitleScreen(SDL_Renderer* renderer);
	~TitleScreen();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	bool EnableTitleScreen();
};

