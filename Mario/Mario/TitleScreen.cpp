#include "TitleScreen.h"
#include "Texture2D.h"
#include <iostream>
using namespace std;
TitleScreen::TitleScreen(SDL_Renderer* renderer) : GameScreen(renderer)
{
	EnableTitleScreen();
}
TitleScreen::~TitleScreen()
{
	title_screen = nullptr;
}

void TitleScreen::Render()
{
	title_screen->Render(Vector2D(),SDL_FLIP_NONE);
}
void TitleScreen::Update(float deltaTime, SDL_Event e)
{

}
bool TitleScreen::EnableTitleScreen()
{
	title_screen = new Texture2D(m_renderer);
	if (!title_screen->LoadFromFile("Images/Test.png"))
	{
		cout << "Title Screen failed to load!" << endl;
		return false;
	}
}