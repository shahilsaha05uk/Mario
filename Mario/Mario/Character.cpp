#include "Character.h"
#include "Texture2D.h"
#include "CharacterKoopa.h"
using namespace std;

Character::Character(SDL_Renderer* renderer, string imagepath, Vector2D start_position, LevelMaps* maps)
{

	m_renderer = renderer;
	m_texture = new Texture2D(renderer);
	m_texture->LoadFromFile(imagepath);
	m_current_level_map = maps;
	m_position = start_position;
	m_alive = true;
	m_collision_radius = 15.0f;

}

Character::~Character()
{
	m_renderer = nullptr;
}
void Character::Render()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}
void Character::Update(float deltaTime, SDL_Event e)
{
	int foot_position;
	int centralX_position;

	if (m_jumping)
	{
		//adjust position
		m_position.y -= m_jump_force * deltaTime;
		//reduce jump position
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;
		//if jump force is 0
		if (m_jump_force <= 0.0f)
		{
			m_jumping = false;
		}
	}

	//deal with moving left
	if (m_moving_left)
	{
		MoveLeft(deltaTime);

	}
	//deal with moving right
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}
	centralX_position = (int)(m_position.x + (m_texture->GetWidth()/ m_single_sprite_w)*0.5) / TILE_WIDTH;
	foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;

	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		m_can_jump=true;
	}
}

float Character::GetCollisionRadius()
{
	return m_collision_radius;
}
Rect2D Character::GetCollisionBox()
{
	return Rect2D(m_position.x, m_position.y, m_single_sprite_w, m_single_sprite_h);
}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}
Vector2D Character::GetPosition()
{
	return m_position;
}


void Character::MoveLeft(float deltaTime)
{
	m_facing_direction = FACING_LEFT;
	m_position.x -= deltaTime * MOVEMENT_SPEED;
}
void Character::MoveRight(float deltaTime)
{
	m_facing_direction = FACING_RIGHT;
	m_position.x += deltaTime * MOVEMENT_SPEED;
}
void Character::AddGravity(float deltaTime) //to prevent it from drowning
{
	if (m_position.y + 64 <= SCREEN_HEIGHT)
	{
		m_position.y += GRAVITY * deltaTime;
	}
	else
	{
		m_can_jump = true;
	}
}
void Character::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}
