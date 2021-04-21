#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "MainMenu.h"
#include "HighScore.h"
#include "GameOver.h"

//#include "Character.h"
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
GameScreenManager::GameScreenManager(SDL_Renderer* renderer)
{
	m_renderer = renderer;
	string path = "Fonts/BASTION_.TTF";
	fontLoad[0] = TTF_OpenFont(path.c_str(), SMALLTEXTSIZE);
	fontLoad[1] = TTF_OpenFont(path.c_str(), MEDIUMTEXTSIZE);
	fontLoad[2] = TTF_OpenFont(path.c_str(), LARGETEXTSIZE);
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


int GameScreenManager::LuigifetchHealth()
{
	return m_current_screen->luigihealthValue;
}
int GameScreenManager::MariofetchHealth()
{
	return m_current_screen->mariohealthValue;
}

void GameScreenManager::ScoreUpdate()
{
	m_current_screen->WriteToScoreFile();
}
bool GameScreenManager::FetchPlayerPosition()
{
	return m_current_screen->playerPositionStatus;
}

