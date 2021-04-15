#include "GameScreenLevel2.h"
#include <iostream>
#include "Texture2D.h"
#include "Collision.h"

using namespace std;
GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetLevelMap();
	SetUpLevel();
	m_level_map = nullptr;
	timer = 0;
}

GameScreenLevel2::~GameScreenLevel2()
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
}

void GameScreenLevel2::Render()
{
	_temprect = new SDL_Rect();
	_temprect->x = 225; _temprect->y = 80;
	_temprect->w = 80; _temprect->h = 80;
	_text->Render(*_temprect, m_renderer);

	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
		for (int i = 0; i < m_goomba.size(); i++)
	{
		m_goomba.at(i)->Render();
	}

	_luigi->Render();
	_mario->Render();
	for (int i = 0; i < _coins.size(); i++)
	{
		_coins.at(i)->Render();
	}
}
void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{

	//_text->Update(e, deltaTime);
	UpdateGoomba(deltaTime, e);

	_mario->Update(deltaTime, e);
	_luigi->Update(deltaTime, e);
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


//SetUp
void GameScreenLevel2::SetLevelMap()
{
	ifstream infile;
	infile.open("Levels/Level2.txt", ios::in);
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
bool GameScreenLevel2::SetUpLevel()
{
	_text = new Text(m_renderer, "Fonts/BASTION_.TTF", "Level 2", MEDIUMTEXTSIZE, { 225,225,225,225 });

	_mario = new MarioCharacter(m_renderer, "Images/Sprite/Mario.png", Vector2D(64, 20), m_level_map);
	_luigi = new LuigiCharacter(m_renderer, "Images/Sprite/Luigi.png", Vector2D(412, 20), m_level_map);

	CreateGoomba(Vector2D(300, 360), FACING_RIGHT, GOOMBA_SPEED);
	CreateGoomba(Vector2D(412, 80), FACING_LEFT, GOOMBA_SPEED);

	//CoinCreator(Vector2D(325, 350));
	//CoinCreator(Vector2D(90, 240));

	m_screenshake = false;
	m_background_yPos = 0.0f;

	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/Level2.png"))
	{
		cout << "Failed to load background texture!" << endl;
		return false;
	}
}

//Create
void GameScreenLevel2::CreateGoomba(Vector2D position, FACING direction, float speed)
{
	CharacterGoomba* _goomba;
	_goomba = new CharacterGoomba(m_renderer, "Images/Goomba.png", position, m_level_map, direction, speed);
	m_goomba.push_back(_goomba);
}
void GameScreenLevel2::CoinCreator(Vector2D position)
{
	Coins* coins;
	coins = new Coins(m_renderer, "Images/Coin.png", position, m_level_map);
	_coins.push_back(coins);
}

//Update
void GameScreenLevel2::UpdatePOWBlock()
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
void GameScreenLevel2::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (!_coins.empty())
	{
		for (int i = 0; i < _coins.size(); i++)
		{
			_coins.at(i)->Update(deltaTime, e);

			if (Collision::Instance()->Circle(_mario, _coins.at(i)))
			{
				_coins.at(i)->CoinSound(true);
				cout << "Coint at " << i << " collided" << endl;
				_coins.erase(_coins.begin() + i);
			}
		}
	}
}
void GameScreenLevel2::UpdateGoomba(float deltaTime, SDL_Event e)
{

	if (!m_goomba.empty())
	{
		for (int i = 0; i < m_goomba.size(); i++)
		{
			m_goomba.at(i)->Update(deltaTime, e);
			if (m_goomba.at(i)->GetPosition().x + m_goomba[i]->GetCollisionBox().width >= 500.0f || m_goomba.at(i)->GetPosition().x <= 80.0f &&
				m_goomba.at(i)->GetPosition().y + m_goomba[i]->GetCollisionBox().height >= 400.0f || m_goomba.at(i)->GetPosition().y <= 0.0f)
			{
				//cout << "Ignore Collisions" << endl;
			}
			else
			{
				if (Collision::Instance()->Circle(_mario, m_goomba.at(i)))
				{
					_mario->SetAlive(false);
				}
			}





			//	Moving Koopas
			if (i == 1)
			{
				if (m_goomba.at(i)->GetPosition().x <= 128)
				{
					m_goomba.at(i)->Update(deltaTime, e);
					m_goomba.at(i)->MoveRight(deltaTime);
				}
				if (m_goomba.at(i)->GetPosition().x + m_goomba.at(i)->GetCollisionBox().width >= 380)
				{
					m_goomba.at(i)->Update(deltaTime, e);
					m_goomba.at(i)->MoveLeft(deltaTime);
				}
			}
			else
			{
				if (m_goomba.at(i)->GetPosition().x <= 80)
				{
					m_goomba.at(i)->Update(deltaTime, e);
					m_goomba.at(i)->MoveRight(deltaTime);
				}
				if (m_goomba.at(i)->GetPosition().x + m_goomba.at(i)->GetCollisionBox().width >= 500)
				{
					m_goomba.at(i)->Update(deltaTime, e);
					m_goomba.at(i)->MoveLeft(deltaTime);
				}
			}
		}
	}

}

//Extras
void GameScreenLevel2::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (int i = 0; i < m_goomba.size(); i++)
	{
		m_goomba.at(i)->TakeDamage();
	}
}
