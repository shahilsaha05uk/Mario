#pragma once

#include "GameScreen.h"
#include "Commons.h"
#include "SDL.h"
#include "MarioCharacter.h"
#include "LuigiCharacter.h"
#include "CharacterKoopa.h"
#include "Collision.h"
#include "LevelMaps.h"
#include <vector>

class Texture2D;
class MarioCharacter;
class LuigiCharfacter;
class PowBlock;
class Coins;
class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* m_background_texture;
	MarioCharacter* _mario;
	LuigiCharacter* _luigi;
	LevelMaps* m_level_map;
	PowBlock* m_pow_block;
	Coins* m_coins;
	void SetLevelMap();

	//Shaking variables
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	void DoScreenShake();
	float timer;

	//Enemy variables
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	vector<CharacterKoopa*> m_koopas;
	
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock();
	void deadMario();
	void KoopaCreator();
	bool SetUpLevel();

};