#include "LevelMaps.h"
#include "GameScreenLevel1.h"

LevelMaps::LevelMaps(int map[MAP_HEIGHT][MAP_WIDTH])
{
	//Allocating the memory
	m_map = new int* [MAP_HEIGHT]; //Doubt
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		m_map[i] = new int[MAP_WIDTH];
	}

	//Populating the memory
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			m_map[i][j] = map[i][j];
		}
	}
}
LevelMaps::~LevelMaps()
{
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		delete[] m_map[i];
	}
	delete[] m_map;
}
int LevelMaps::GetTileAt(unsigned int h, unsigned int w)
{
	if (h < MAP_HEIGHT && w < MAP_WIDTH)
	{
		return m_map[h][w];
	}
	return 0;
}
void LevelMaps::ChangeTileAt(unsigned int row, unsigned int column, unsigned int new_value)
{
	if (row < MAP_HEIGHT && column < MAP_WIDTH)
	{
		m_map[row][column]= new_value;
	}
}