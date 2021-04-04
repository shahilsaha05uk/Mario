#include "PowBlock.h"
using namespace std;

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMaps* maps)
{
	string imagePath = "Images/PowBlock.png";
	m_texture = new Texture2D(renderer);

	if (!m_texture->LoadFromFile(imagePath.c_str()))
	{
		cout << "Failed to load texture" << endl;
		return;
	}
	m_level_map = maps;
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
	m_num_hits_left = 3;
	m_position = Vector2D((SCREEN_WIDTH * 0.5f) - m_single_sprite_w * 0.5f, 260);
}
PowBlock::~PowBlock()
{
	m_renderer = nullptr;
	delete m_texture;
	m_level_map = nullptr;
}
void PowBlock::Render()
{
	if (m_num_hits_left > 0)
	{
		int frame_hits = m_single_sprite_w*(m_num_hits_left-1);
		SDL_Rect first_frame = { frame_hits,0,m_single_sprite_w, m_single_sprite_h };
		SDL_Rect spritePosition = {(int)(m_position.x),(int)(m_position.y),m_single_sprite_w, m_single_sprite_h};
		m_texture->Render(first_frame, spritePosition, SDL_FLIP_NONE);
		m_num_hits_left-1;
	}
}
void PowBlock::TakeHit()
{
	m_num_hits_left--;
	if (m_num_hits_left <= 0)
	{
		m_num_hits_left = 0;
		m_level_map->ChangeTileAt(8, 7, 0);
		m_level_map->ChangeTileAt(8, 8, 0);
	}
}