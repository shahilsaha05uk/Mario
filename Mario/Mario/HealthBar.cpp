#include "HealthBar.h"

HealthBar::HealthBar(SDL_Renderer* renderer, Vector2D start_position, LevelMaps* maps, string imagePath) : Character(renderer,imagePath, start_position, maps)
{
	if (!m_texture->LoadFromFile(imagePath.c_str()))
	{
		cout << "Failed to load texture" << endl;
		return;
	}

	m_position = start_position;
	frame_delay = COINS_ROTATE_SPEED;
	framescount = 3;
	m_single_sprite_w = m_texture->GetWidth() / 4;
	m_single_sprite_h = m_texture->GetHeight();
}

HealthBar::~HealthBar()
{

}

void HealthBar::Render()
{
	int left = currentFrame * m_single_sprite_w;
	SDL_Rect first_frame = { left,0,m_single_sprite_w,m_single_sprite_h };
	SDL_Rect draw_pos = { (int)(m_position.x),(int)(m_position.y),m_single_sprite_w, m_single_sprite_h };
	m_texture->Render(first_frame, draw_pos, SDL_FLIP_NONE);
}

int HealthBar::Update(float deltatime, Character* c1)
{
	frame_delay -= deltatime;
	if (frame_delay <= 0)
	{
		currentFrame++;

		frame_delay = COINS_ROTATE_SPEED;

		if (currentFrame == 0)
		{
			healthValue = 100;

		}
		else if (currentFrame == 1)
		{
			healthValue = 70;

		}
		else if (currentFrame == 2)
		{
			healthValue = 25;

		}
		else if(currentFrame == 3)
		{
			healthValue = 5;

		}
		else if (currentFrame > 3)
		{
			healthValue = 0;

			c1->SetAlive(false);
			cout << "Mario dead" << endl;
		}
	}
	return healthValue;
}


