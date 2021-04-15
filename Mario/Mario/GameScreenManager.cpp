#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "MainMenu.h"
#include "HighScore.h"
#include "GameOver.h"

//#include "Character.h"
GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen): GameScreen(renderer)
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
	//trial();
	m_current_screen->Update(deltaTime,e);
}
void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	if (m_current_screen != nullptr)
	{
		delete m_current_screen;
	}

	//Defining pointers to the screens
	MainMenu* main_menu;
	GameScreenLevel1* level1;
	GameScreenLevel2* level2;
	HighScore* highscore;
	GameOver* gameover;
	switch (new_screen)
	{
	case SCREEN_MENU:
		main_menu = new MainMenu(m_renderer);
		m_current_screen = (GameScreen*)main_menu;
		main_menu = nullptr;
		break;
	case SCREEN_LEVEL1:
		level1 = new GameScreenLevel1(m_renderer);
		m_current_screen = (GameScreen*) level1;
		level1 = nullptr;
		break;
	case SCREEN_LEVEL2:
		level2 = new GameScreenLevel2(m_renderer);
		m_current_screen = (GameScreen*)level2;
		level2 = nullptr;
		break;
	case SCREEN_GAMEOVER:
		gameover = new GameOver(m_renderer);
		m_current_screen = (GameScreen*)gameover;
		gameover = nullptr;

		break;
	case SCREEN_HIGHSCORES:
		highscore = new HighScore(m_renderer, true);
		m_current_screen = (GameScreen*)highscore;
		highscore = nullptr;
		break;
	default:
		break;
	}

	m_screen = new_screen;
}

int GameScreenManager::trial()
{
	return m_current_screen->luigi_health;
}

int GameScreenManager::Scores()
{
	score = m_current_screen->ScoreRecord();
	return score;
}
