#pragma once

#include "GameScreen.h"
#include "GameScreenManager.h"
#include <Windows.h>
#include <vector>
#include "HighScore.h"

class Texture2D;
class Character;
class PowBlock;
class GameScreenLevel2 : GameScreen
{
private:

	float timer;
	vector<CharacterGoomba*> m_goomba;
	vector<Coins*> _coins;

public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	bool SetUpLevel();
	void SetLevelMap();



	//Update
	void UpdateCoins(float deltaTime, SDL_Event e);
	void UpdatePOWBlock();
	void UpdateGoomba(float deltaTime, SDL_Event e);

	//Create
	void CoinCreator(Vector2D position);
	void CreateGoomba(Vector2D position, FACING direction, float speed);

	//Extras
	void DoScreenShake();


};