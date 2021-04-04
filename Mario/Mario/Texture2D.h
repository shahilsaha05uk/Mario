#pragma once
#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H

//Headers
#include <SDL.h>
#include <string>
#include "Commons.h"

class Texture2D
{
private:

	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;

	int m_width;
	int m_height;

public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	bool LoadFromFile(std::string path);

	void Render(Vector2D new_position, SDL_RendererFlip flip, double angle=0.0f);

	void Render(SDL_Rect, SDL_RendererFlip flip, double angle = 0.0);
	void Render(SDL_Rect src_rect, SDL_Rect src_dest, SDL_RendererFlip flip, double angle = 0.0);


	void Free();


	int GetWidth();
	int GetHeight();

};

#endif // !_TEXTURE2D_H