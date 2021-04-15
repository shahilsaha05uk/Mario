#pragma once

#include "GameScreen.h"
#include "GameScreenManager.h"
#include <Windows.h>
#include <vector>
using namespace std;

class Texture2D;
class Character;
class PowBlock;
class GameScreenLevel1 : GameScreen
{
private:


	GameScreenManager* game_manager;
	void SetLevelMap();

	void DoScreenShake();

	//Enemy variables
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	vector<CharacterKoopa*> m_koopas;
	vector<Coins*> _coins;

public:

	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock();
	bool SetUpLevel();

	void CoinCreator(Vector2D position);
	void UpdateCoins(float deltaTime, SDL_Event e);
	void MarioDead();
};