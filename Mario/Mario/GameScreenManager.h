#pragma once
#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
class GameScreen;
class Character;
class GameScreenManager : public GameScreen
{
private:
	bool quit;
protected:
	SDL_Renderer* m_renderer;
	GameScreen* m_current_screen;
	SCREENS m_screen;

	//Character* _character;

	int score = 0;
	int health = 0;
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void ChangeScreen(SCREENS new_screen);
	SCREENS trialScreen() { return m_screen; }
	int trial();

	int Scores();
};

