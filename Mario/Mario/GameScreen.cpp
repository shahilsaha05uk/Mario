#include "GameScreen.h"
#include "HighScore.h"
#include "GameScreenManager.h"
GameScreen::GameScreen(SDL_Renderer* renderer)
{
	m_renderer= renderer;
}
GameScreen::~GameScreen()
{
	m_renderer = nullptr;
	//scoretext = nullptr;

	_mario_healthText = nullptr;
	delete[] _mario_healthText;

	_luigi_healthText = nullptr;
	delete[] _luigi_healthText;

	luigiHealthrect = nullptr;
	delete[] luigiHealthrect;

	marioHealthrect = nullptr;
	delete[]marioHealthrect;
}

void GameScreen::Render()
{

}
void GameScreen::Update(float deltaTime, SDL_Event e)
{

}

int GameScreen::ScoreRecord(int score)
{
	int totalpoint;
	totalpoint = score;

	return totalpoint;
}

void GameScreen::LoadScores()
{

}
int GameScreen::LuigiHealth()
{
	if (luigi_health >= 0)
	{
		healthtimer += fixed_health_timer * 0.2;
		if (healthtimer > fixed_health_timer)
		{
			healthtimer = 0;

			luigi_health -= 1;
			if (luigi_health == -2)
			{
				_luigi->SetAlive(false);
			}

		}
		//_luigi_healthText = nullptr;
		//if (luigi_health > 70)
		//{
			/*_luigi_healthText = new Text(m_renderer, "Fonts/BASTION_.ttf", to_string(luigi_health), SMALLTEXTSIZE);*/

			_luigi_healthText->Update(to_string(luigi_health),GREEN_COLOR);
		//}
		//else if (luigi_health >= 50 && luigi_health <= 70)
		//{
		//	_luigi_healthText = new Text(m_renderer, "Fonts/BASTION_.ttf", to_string(luigi_health), SMALLTEXTSIZE);
		//	_luigi_healthText->Update(to_string(luigi_health), YELLOW_COLOR);
		//}
		//else if (luigi_health < 50)
		//{
		//	_luigi_healthText = new Text(m_renderer, "Fonts/BASTION_.ttf", to_string(luigi_health), SMALLTEXTSIZE);
		//	_luigi_healthText->Update(to_string(luigi_health));
		//}
	}
	return luigi_health;

}
void GameScreen::MarioHealth()
{
	if (mario_health >= 0)
	{
		healthtimer += fixed_health_timer * 0.2;
		if (healthtimer > fixed_health_timer)
		{
			healthtimer = 0;

			mario_health -= 1;
			if (mario_health == -2)
			{
				cout << "Mario dead" << endl;
				_mario->SetAlive(false);
			}
		}

		_mario_healthText = nullptr;
		if (mario_health > 70)
		{
			_mario_healthText = new Text(m_renderer, "Fonts/BASTION_.TTF", to_string(mario_health), SMALLTEXTSIZE);
			_mario_healthText->Update(to_string(mario_health));
		}
		else if (mario_health >= 50 && mario_health <= 70)
		{
			_mario_healthText = new Text(m_renderer, "Fonts/BASTION_.TTF", to_string(mario_health), SMALLTEXTSIZE);
			_mario_healthText->Update(to_string(mario_health));
		}
		else if (mario_health < 50)
		{
			_mario_healthText = new Text(m_renderer, "Fonts/BASTION_.TTF", to_string(mario_health), SMALLTEXTSIZE);
			_mario_healthText->Update(to_string(mario_health));
		}
	}

}
