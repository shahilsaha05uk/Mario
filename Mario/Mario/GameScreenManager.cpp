#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "TitleScreen.h"
GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;
	ChangeScreen(startScreen);
}
GameScreenManager::~GameScreenManager()
{
	m_renderer = nullptr;
	delete m_current_screen;
}
void GameScreenManager::Render()
{
	m_current_screen->Render();
}
void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	m_current_screen->Update(deltaTime,e);
}
void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	if (m_current_screen != nullptr)
	{
		delete m_current_screen;
	}

	//Defining pointers to the screens
	GameScreenLevel1* tempScreen;
	TitleScreen* tempTitleScreen;

	switch (new_screen)
	{
	case SCREEN_INTRO:
		tempTitleScreen = new TitleScreen(m_renderer);
		m_current_screen = (GameScreen*)tempTitleScreen;
		tempTitleScreen = nullptr;
		break;
	case SCREEN_MENU:
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(m_renderer);
		m_current_screen = (GameScreen*) tempScreen;
		tempScreen = nullptr;
		break;
	case SCREEN_LEVEL2:
		break;
	case SCREEN_GAMEOVER:
		break;
	case SCREEN_HIGHSCORES:
		break;
	default:
		break;
	}
}