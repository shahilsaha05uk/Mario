#include "CharacterGoomba.h"
CharacterGoomba::CharacterGoomba(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMaps* maps, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, maps)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_injured = false;

	m_single_sprite_w = m_texture->GetWidth()/2;
	m_single_sprite_h = m_texture->GetHeight();
}
CharacterGoomba::~CharacterGoomba()
{

}
void CharacterGoomba::Render()
{
	int firstframe = currentFrameCount* m_single_sprite_w;
	SDL_Rect first_frame = { firstframe,0,m_single_sprite_w,m_single_sprite_h };
	SDL_Rect draw_pos = { (int)(m_position.x),(int)(m_position.y),m_single_sprite_w, m_single_sprite_h };

	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(first_frame, draw_pos, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(first_frame, draw_pos, SDL_FLIP_HORIZONTAL);
	}
}
void CharacterGoomba::Update(float deltaTime, SDL_Event e)
{
	if (!m_injured)
	{
		if (m_facing_direction == FACING_LEFT)
		{
			m_moving_left = true;
			m_moving_right = false;
		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			m_moving_left = false;
			m_moving_right = true;
		}
	}
	else
	{
		m_moving_left = false;
		m_moving_right = false;

		m_injured_time -= deltaTime;

		if (m_injured_time <= 0)
		{
			FlipRightWayUp();
		}
	}
	Character::Update(deltaTime, e);

	GoombaAnimation(deltaTime, e);

}

void CharacterGoomba::TakeDamage()
{
	m_injured = true;
	m_injured_time = INJURED_TIME;

	Jump();
}
void CharacterGoomba::FlipRightWayUp()
{
	m_facing_direction = FACING_LEFT;
	m_injured = false;

	Jump();
}

void CharacterGoomba::GoombaAnimation(float deltaTime, SDL_Event e)
{
	mtimer += deltaTime;
	if (mtimer > GOOMBA_ANIMATION_DELAY)
	{

		currentFrameCount++;
		mtimer = 0;

		cout << currentFrameCount << endl;

		if (currentFrameCount > 1)
		{
			currentFrameCount = 0;
		}
	}
}
