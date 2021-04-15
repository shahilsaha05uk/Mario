#pragma once

#include "Commons.h"
#include "GameScreen.h"
#include "LevelMaps.h"

#include "CharacterKoopa.h"
#include "Coins.h"
#include "LuigiCharacter.h"
#include "MarioCharacter.h"
#include "PowBlock.h"
#include "CharacterGoomba.h"
#include <Windows.h>
#include <vector>
#include <fstream>

class Texture2D;
class Character;
class PowBlock;
class GameScreenLevel2 : GameScreen
{
private:
	void SetLevelMap();

	void DoScreenShake();
	float timer;

	//Enemy variables
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateGoomba(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateGoomba(Vector2D position, FACING direction, float speed);
	vector<CharacterKoopa*> m_koopas;
	vector<CharacterGoomba*> m_goomba;

	vector<Coins*> _coins;

public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock();
	void deadMario();
	void KoopaCreator();
	bool SetUpLevel();

	void CoinCreator(Vector2D position);
	void UpdateCoins(float deltaTime, SDL_Event e);

};