#include "CharacterKoopa.h"


CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMaps* maps, FACING start_facing, float movement_speed): Character(renderer,imagePath, start_position, maps)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_injured = false;

	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();
}
CharacterKoopa::~CharacterKoopa()
{
	
}
void CharacterKoopa::Render()
{
	int left = 0.0f;
	if (m_injured)
	{
		left = m_single_sprite_w;
	}
	SDL_Rect first_frame = { left,0,m_single_sprite_w,m_single_sprite_h };
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
void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);
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
}

void CharacterKoopa::TakeDamage()
{
	m_injured = true;
	m_injured_time = INJURED_TIME;
	Jump();
}
void CharacterKoopa::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE_SMALL;
		m_jumping = true;
		m_can_jump = false;
	}
}
void CharacterKoopa::FlipRightWayUp()
{
	m_facing_direction = FACING_LEFT;
	m_injured = false;
	Jump();
}
void CharacterKoopa::KoopaMovements(float deltaTime)
{
	if (m_position.x > SCREEN_WIDTH)
	{
		m_position.x -= 0.5f * deltaTime;
	}
}