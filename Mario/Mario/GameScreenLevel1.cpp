#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>
#include "SDL.h"
#include "PowBlock.h"
#include "Coins.h"
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
	_mario = nullptr;
	_luigi = nullptr;
	delete[] _mario;
	delete[] _luigi;
	delete[] m_pow_block;
	m_pow_block = nullptr;
	m_koopas.clear();
	delete[] m_coins;
}

void GameScreenLevel1::Render()
{

	m_background_texture->Render(Vector2D(0,m_background_yPos), SDL_FLIP_NONE);
	for (int i = 0; i < m_koopas.size(); i++)
	{
		m_koopas.at(i)->Render();
	}
	_luigi->Render();
	_mario->Render();
	m_coins->Render();
	m_pow_block->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{

	UpdateEnemies(deltaTime, e);
	_mario->Update(deltaTime, e);
	_luigi->Update(deltaTime, e);
	
	UpdatePOWBlock();
	m_coins->Update(deltaTime, e);

	if (Collision::Instance()->Circle(_mario, _luigi))
	{
		/*cout << "Circle Hit!" << endl;*/
	}
	if (Collision::Instance()->Box(_mario->GetCollisionBox(), _luigi->GetCollisionBox()))
	{
		/*cout << "Box Hit!" << endl;*/
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
void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_koopas.empty())
	{
		int enemyToDelete = -1;
		for (unsigned int i = 0; i < m_koopas.size(); i++)
		{
			//check if the enemy is on the bottom row of the tile
			if (m_koopas.at(i)->GetPosition().y > 300.0f)
			{
				//is the enemy off screen to the left/ right?
				if (m_koopas.at(i)->GetPosition().x < (float)(m_koopas.at(i)->GetCollisionBox().width * 0.5f) ||
					m_koopas.at(i)->GetPosition().x > SCREEN_WIDTH - (float)(m_koopas[i]->GetCollisionBox().width * 0.55f))
				{
					//if both the conditions meet then set the koopas to false
					m_koopas.at(i)->SetAlive(false);
					m_koopas.at(i)->Jump();
				}
			}
			//Update the koopa position
			m_koopas.at(i)->Update(deltaTime, e);

			//check if the enemy collides with the player
			if ((m_koopas.at(i)->GetPosition().y > 300.0f || m_koopas.at(i)->GetPosition().y <= 64.0f) &&
				(m_koopas.at(i)->GetPosition().x<64.0f || m_koopas.at(i)->GetPosition().x>SCREEN_WIDTH - 96.0f))
			{
				//ignore the collisions with the player if behind the pipe

				if (Collision::Instance()->Circle(m_koopas[i], _mario))
				{
					m_koopas.at(i)->SetAlive(true);
					_mario->SetAlive(true);
				}
			}
			else //if not beyond the bounds then set the collisions to true
			{
				if (Collision::Instance()->Circle(m_koopas[i], _mario))
				{
					cout << "Collided" << endl;

					if (m_koopas.at(i)->GetInjured())
					{
						m_koopas.at(i)->SetAlive(false);
					}
					else
					{
						//kill mario
						_mario->SetAlive(false);
					}
				}
			}
			//if the enemy is no longer alive then schedule it for deletion
			if (!m_koopas[i]->GetAlive())
			{
				enemyToDelete = i;
			}
			if (enemyToDelete != -1)
			{
				m_koopas.erase(m_koopas.begin() + enemyToDelete);

			}

			for (unsigned int i = 0; i < m_koopas.size(); i++)
			{
				/*Update(deltaTime, e);*/
				for (unsigned int i = 0; i < m_koopas.size(); i++)
				{
					/*Update(deltaTime, e);*/
					m_koopas.at(i)->KoopaMovements(deltaTime);
				}

			}
		}
	}
}
void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* _koopa;
	_koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", position, m_level_map, direction, speed);
	m_koopas.push_back(_koopa);
}

bool GameScreenLevel1::SetUpLevel()
{
	_mario = new MarioCharacter(m_renderer, "Images/Mario.png", Vector2D(64, 240), m_level_map);
	_luigi = new LuigiCharacter(m_renderer, "Images/Luigi.png", Vector2D(64, 240), m_level_map);
	
	
	CreateKoopa(Vector2D(300, 325), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(350, 353), FACING_LEFT, KOOPA_SPEED);

	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_coins = new Coins(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;

	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/Level1.png"))
	{
		cout << "Failed to load background texture!" << endl;
		return false;
	}
}
void GameScreenLevel1::KoopaCreator()
{
	CreateKoopa(Vector2D(150, 353), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 353), FACING_LEFT, KOOPA_SPEED);
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
												  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
												  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
												  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
												  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
												  { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
												  { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
												  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
												  { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
												  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
												  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
												  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
												  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}
	m_level_map = new LevelMaps(map);
}

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

//if (!m_koopas.empty())
//{
//	int enemyToDelete = -1;
//	for (unsigned int i = 0; i < m_koopas.size(); i++)
//	{
//		//check if the enemy is on the bottom row of tiles
//		if (m_koopas.at(i)->GetPosition().y > 300.0f)
//		{
//			if (m_koopas.at(i)->GetPosition().x < (float)(m_koopas.at(i)->GetCollisionBox().width * 0.5f) ||
//				m_koopas.at(i)->GetPosition().x > SCREEN_WIDTH - (float)(m_koopas[i]->GetCollisionBox().width * 0.55f))
//			{
//				m_koopas.at(i)->SetAlive(false);
//			}
//		}
//		m_koopas.at(i)->Update(deltaTime, e);
//
//		//check to see if enemy collides with player
//		if ((m_koopas.at(i)->GetPosition().y > 300.0f || m_koopas.at(i)->GetPosition().y <= 64.0f) &&
//			(m_koopas.at(i)->GetPosition().x<64.0f || m_koopas.at(i)->GetPosition().x>SCREEN_WIDTH - 96.0f))
//		{
//			//ignore the collisions
//		}
//		else
//		{
//			if (Collision::Instance()->Circle(m_koopas[i], _mario))
//			{
//				cout << "Collided" << endl;
//				if (m_koopas.at(i)->GetInjured())
//				{
//					m_koopas.at(i)->SetAlive(false);
//				}
//				else
//				{
//					//kill mario
//					_mario->SetAlive(false);
//					_mario = nullptr;
//					delete[] _mario;
//				}
//			}
//		}
//		//if the enemy is no longer alive then schedule it for deletion
//		if (!m_koopas[i]->GetAlive())
//		{
//			enemyToDelete = i;
//		}
//	}
