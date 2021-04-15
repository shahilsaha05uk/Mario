#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Collision.h"


using namespace std;
GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetLevelMap();
	SetUpLevel();
	m_level_map = nullptr;
	timer = 0;
}

GameScreenLevel1::~GameScreenLevel1()
{
	m_background_texture = nullptr;

	_luigi = nullptr;
	delete[] _luigi;

	_mario = nullptr;
	delete[] _mario;

	m_pow_block = nullptr;
	delete[] m_pow_block;

	m_koopas.clear();

	m_coins = nullptr;
	delete[] m_coins;

	_text = nullptr;
	delete[] _text;

	_luigi_healthText = nullptr;
	delete[] _luigi_healthText;
}

void GameScreenLevel1::Render()
{
	_temprect = new SDL_Rect();
	_temprect->x = 225; _temprect->y = 18;
	_temprect->w = 80; _temprect->h = 80;
	_text->Render(*_temprect, m_renderer);


	marioHealthrect = new SDL_Rect();
	marioHealthrect->h = 30.0f; marioHealthrect->w = 100.0f;
	marioHealthrect->x = 10.0f; marioHealthrect->y = 10.0f;

	luigiHealthrect = new SDL_Rect();
	luigiHealthrect->h = 30.0f; luigiHealthrect->w = 100.0f;
	luigiHealthrect->x = 400.0f; luigiHealthrect->y = 10.0f;


	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
	for (int i = 0; i < m_koopas.size(); i++)
	{
		m_koopas.at(i)->Render();
	}
	_luigi->Render();
	_mario->Render();
	m_pow_block->Render();
	for (int i = 0; i < _coins.size(); i++)
	{
		_coins.at(i)->Render();
	}


		//_mario_healthText->Render(*marioHealthrect, m_renderer);
	if (_luigi->GetAlive() != false)
	{
		_luigi_healthText->Render(*luigiHealthrect, m_renderer);
	}
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//scoretext->Update(e, deltaTime);


	if (_mario->GetAlive() != false)
	{
		_mario_healthText->Update(to_string(mario_health));
	}
	if (_luigi->GetAlive() != false)
	{
		_luigi_healthText->Update(to_string(luigi_health));
	}


	UpdateEnemies(deltaTime, e);
	_mario->Update(deltaTime, e);
	_luigi->Update(deltaTime, e);
	UpdatePOWBlock();
	UpdateCoins(deltaTime, e);


	if (Collision::Instance()->Circle(_mario, _luigi))
	{
		//cout << "Circle Hit!" << endl;
	}
	if (Collision::Instance()->Box(_mario->GetCollisionBox(), _luigi->GetCollisionBox()))
	{
		//cout << "Box Hit!" << endl;
	}
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}

}


//Setup
bool GameScreenLevel1::SetUpLevel()
{
	_text = new Text(m_renderer, "Fonts/BASTION_.TTF", "Level 1", MEDIUMTEXTSIZE, { 225,225,225,225 });
	LoadScores();


	_mario_healthText = new Text(m_renderer, "Fonts/BASTION_.TTF", to_string(mario_health), SMALLTEXTSIZE);

	_luigi_healthText = new Text(m_renderer, "Fonts/BASTION_.TTF", to_string(luigi_health), SMALLTEXTSIZE);

	_mario = new MarioCharacter(m_renderer, "Images/Sprite/Mario.png", Vector2D(64, 353), m_level_map);
	_luigi = new LuigiCharacter(m_renderer, "Images/Sprite/Luigi.png", Vector2D(64, 240), m_level_map);
	
	CreateKoopa(Vector2D(256, 360), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(255, 128), FACING_LEFT, KOOPA_SPEED);

	m_pow_block = new PowBlock(m_renderer, m_level_map);

	CoinCreator(Vector2D(380, 350));
	CoinCreator(Vector2D(100, 240));

	m_screenshake = false;
	m_background_yPos = 0.0f;

	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/Level1.png"))
	{
		cout << "Failed to load background texture!" << endl;
		return false;
	}



}
void GameScreenLevel1::SetLevelMap()
{
	ifstream infile;
	infile.open("Levels/Level1.txt", ios::in);
	int map[MAP_HEIGHT][MAP_WIDTH];
	int tempNum;
	if (!infile.is_open())
	{
		cout << "file could not open" << endl;
	}

	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			infile >> tempNum;
			map[i][j] = tempNum;
		}
		cout << endl;
	}
	infile.close();

	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}
	m_level_map = new LevelMaps(map);
}

//Updates
void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_koopas.empty())
	{
		for (int i = 0; i < m_koopas.size(); i++)
		{
			m_koopas.at(i)->Update(deltaTime, e);
			if (m_koopas.at(i)->GetPosition().x + m_koopas[i]->GetCollisionBox().width >= 500.0f || m_koopas.at(i)->GetPosition().x <= 80.0f &&
				m_koopas.at(i)->GetPosition().y + m_koopas[i]->GetCollisionBox().height >= 400.0f || m_koopas.at(i)->GetPosition().y <= 0.0f)
			{
				//cout << "Ignore Collisions" << endl;
			}
			else if (_mario->GetCollisionBox().x + _mario->GetCollisionBox().width >= m_koopas.at(i)->GetCollisionBox().x && _mario->GetCollisionBox().x <= m_koopas.at(i)->GetCollisionBox().x && _mario->GetCollisionBox().y + _mario->GetCollisionBox().height >= m_koopas.at(i)->GetCollisionBox().y && _mario->GetCollisionBox().y <= m_koopas.at(i)->GetCollisionBox().y)
			{

				if (_mario->Isjumping())
				{
					m_koopas.at(i)->TakeDamage();
				}
				else
				{
					MarioHealth();
				}
			}

			//luigi
			else if (_luigi->GetCollisionBox().x + _luigi->GetCollisionBox().width >= m_koopas.at(i)->GetCollisionBox().x && _luigi->GetCollisionBox().x <= m_koopas.at(i)->GetCollisionBox().x && _luigi->GetCollisionBox().y + _luigi->GetCollisionBox().height >= m_koopas.at(i)->GetCollisionBox().y && _luigi->GetCollisionBox().y <= m_koopas.at(i)->GetCollisionBox().y)
			{
				if (_luigi->Isjumping())
				{
					m_koopas.at(i)->TakeDamage();
				}
				else
				{
					LuigiHealth();
				}
			}



			//	Moving Koopas
			if (i == 1)
			{
				if (m_koopas.at(i)->GetPosition().x <= 128)
				{
					m_koopas.at(i)->Update(deltaTime, e);
					m_koopas.at(i)->MoveRight(deltaTime);
				}
				if (m_koopas.at(i)->GetPosition().x + m_koopas.at(i)->GetCollisionBox().width >= 380)
				{
					m_koopas.at(i)->Update(deltaTime, e);
					m_koopas.at(i)->MoveLeft(deltaTime);
				}
			}
			else
			{
				if (m_koopas.at(i)->GetPosition().x <= 80)
				{
					//cout << "Koopas out of frame" << endl;
					m_koopas.at(i)->Update(deltaTime, e);
					m_koopas.at(i)->MoveRight(deltaTime);
				}
				if (m_koopas.at(i)->GetPosition().x + m_koopas.at(i)->GetCollisionBox().width >= 500)
				{
					m_koopas.at(i)->Update(deltaTime, e);
					m_koopas.at(i)->MoveLeft(deltaTime);
				}
			}
		}
	}

}
void GameScreenLevel1::UpdatePOWBlock()
{
	if (Collision::Instance()->Box(_mario->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			if (_mario->Isjumping())
			{
				DoScreenShake();

				m_pow_block->TakeHit();
				_mario->CancelJump();
			}
		}
	}
}
void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (!_coins.empty())
	{
		for (int i = 0; i < _coins.size(); i++)
		{
			_coins.at(i)->Update(deltaTime, e);

			if (Collision::Instance()->Circle(_mario, _coins.at(i)))
			{
				ScoreRecord(10);
				_coins.at(i)->CoinSound(true);
				cout << "Coint at " << i << " collided" << endl;
				_coins.erase(_coins.begin() + i);
			}
			else if (Collision::Instance()->Circle(_luigi, _coins.at(i)))
			{
				ScoreRecord(10);
				_coins.at(i)->CoinSound(true);
				cout << "Coint at " << i << " collided" << endl;
				_coins.erase(_coins.begin() + i);
			}

		}
	}
}

void GameScreenLevel1::MarioDead()
{

}
//Create
void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* _koopa;
	_koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", position, m_level_map, direction, speed);
	m_koopas.push_back(_koopa);
}
void GameScreenLevel1::CoinCreator(Vector2D position)
{
	Coins* coins;
	coins = new Coins(m_renderer, "Images/Coin.png", position, m_level_map);
	_coins.push_back(coins);
}

//Extras

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (int i = 0; i < m_koopas.size(); i++)
	{
		m_koopas.at(i)->TakeDamage();
	}
}
