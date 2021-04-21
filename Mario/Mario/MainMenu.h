#pragma once
#include "GameScreen.h"
#include "GameScreenManager.h"
#include <string>
#include <vector>
#include "HighScore.h"
using namespace std;
class MainMenu : GameScreen
{
private:
	Texture2D* menuTexture;
	int screen;
	bool quit;

public:
	MainMenu(SDL_Renderer* renderer);
	~MainMenu();

	void MenuTextLoad();
	void MenuTextRender();
	void MenuTextUpdate(float deltaTime, SDL_Event e);

	void Load();
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);




	SDL_Rect* MainMenuRect[4];
	Text* _menuText[4];

	//void ScreenLoader(SDL_Event e, float deltatime);
};

