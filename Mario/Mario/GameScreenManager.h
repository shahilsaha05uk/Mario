#pragma once
#include "SDL.h"
#include "Commons.h"
#include <vector>
#include <SDL_ttf.h>

class GameScreen;
class Character;
class GameScreenManager
{
private:
	bool quit;
protected:
	SDL_Renderer* m_renderer;
	SCREENS m_screen;
	Character* _character;

public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();
	GameScreenManager(SDL_Renderer* renderer);

	TTF_Font* fontLoad[3];
	GameScreen* m_current_screen;


	void Render();
	void Update(float deltaTime, SDL_Event e);
	void ChangeScreen(SCREENS new_screen);


	SCREENS GetCurrentScreen() { return m_screen; }

	int MariofetchHealth();
	int LuigifetchHealth();

	void ScoreUpdate();
	bool FetchPlayerPosition();
};

