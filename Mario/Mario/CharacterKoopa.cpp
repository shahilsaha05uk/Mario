#include "CharacterKoopa.h"


CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMaps* maps, FACING start_facing, float movement_speed): Character(renderer,imagePath, start_position, maps)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_injured = false;

	m_single_sprite_h = m_texture->GetHeight();
	m_single_sprite_w = m_texture->GetWidth() / 11;
	TotalframesCount = 11;
}
CharacterKoopa::~CharacterKoopa()
{
	
}
void CharacterKoopa::Render()
{

	int firstSprite = currentFrameCount * m_single_sprite_w;

	SDL_Rect firstFrame = { firstSprite,0, m_single_sprite_w, m_single_sprite_h };
	SDL_Rect worldDrawPosition = { (int)m_position.x , (int)m_position.y , m_single_sprite_w, m_single_sprite_h };

	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(firstFrame, worldDrawPosition, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(firstFrame, worldDrawPosition, SDL_FLIP_HORIZONTAL);
	}
}
void CharacterKoopa::Update(float deltaTime, SDL_Event e)
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
	KoopaAnimation(deltaTime, e);
}

void CharacterKoopa::TakeDamage()
{
	m_injured = true;
	m_injured_time = INJURED_TIME;

		Jump();
}
void CharacterKoopa::KoopaAnimation(float deltaTime, SDL_Event e)
{
	mtimer += deltaTime;
	if (m_moving_right || m_moving_left)
	{
		if (mtimer > ANIMATIONDELAY)
		{

			currentFrameCount++;
			mtimer = 0;

			if (currentFrameCount >= 5)
			{
				currentFrameCount = 0;
			}
		}
	}
	else if (m_injured == true)
	{
		setframe = 6;

		if (mtimer > ANIMATIONDELAY)
		{

			currentFrameCount++;
			mtimer = 0;

			if (currentFrameCount >= 11)
			{
				currentFrameCount = setframe;
			}
		}
	}
}
void CharacterKoopa::FlipRightWayUp()
{
	m_facing_direction = FACING_LEFT;
	m_injured = false;

	Jump();
}