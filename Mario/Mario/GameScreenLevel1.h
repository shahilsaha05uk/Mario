#pragma once

#include "GameScreen.h"
#include "GameScreenManager.h"
#include <Windows.h>
#include <vector>
#include "HighScore.h"
using namespace std;

class Texture2D;
class Character;
class PowBlock;
class HealthBar;
class GameScreenLevel1 : GameScreen
{
private:

	HighScore* _score;
	vector<CharacterKoopa*> m_koopas;
	vector<Coins*> _coins;

public:

	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	bool SetUpLevel();
	void SetLevelMap();



	//Create
	void CoinCreator(Vector2D position);
	void CreateKoopa(Vector2D position, FACING direction, float speed);



	//Update
	void UpdatePOWBlock();
	void UpdateCoins(float deltaTime, SDL_Event e);
	void UpdatePlayers();
	void UpdateEnemies(float deltaTime, SDL_Event e);

	//Extras
	void DoScreenShake();

};