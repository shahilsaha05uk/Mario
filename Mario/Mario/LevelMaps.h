#ifndef _LEVELMAP_H_
#define _LEVELMAP_H_

#pragma once

#include "constants.h"

class LevelMaps
{
private:
	int** m_map;
public:
	LevelMaps(int map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMaps();


	int GetTileAt(unsigned int h, unsigned int w);
	void ChangeTileAt(unsigned int row, unsigned int column, unsigned int new_value);

};

#endif // !_LEVELMAP_H_
