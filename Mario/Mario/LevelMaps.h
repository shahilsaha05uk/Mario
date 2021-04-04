#ifndef _LEVELMAP_H_
#define _LEVELMAP_H_

#pragma once

#include "constants.h"
//#include "GameScreenLevel1.h"
//#include "Character.h"
//#include "Collision.h"

class GameScreenLevel1;
class LevelMaps
{
private:
	int** m_map;
public:
	LevelMaps(int map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMaps();

	//Collision* _collision;
	GameScreenLevel1* _level;

	int GetTileAt(unsigned int h, unsigned int w);
	void ChangeTileAt(unsigned int row, unsigned int column, unsigned int new_value);

};

#endif // !_LEVELMAP_H_
