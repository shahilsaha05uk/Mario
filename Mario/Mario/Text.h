#ifdef _TEXT_H_
#define _TEXT_H_
#endif // _TEXT_H_
#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include "Commons.h"
#include <fstream>
using namespace std;
class Text
{
private:
	SDL_Texture* text_texture;
	SDL_Rect text_rect;

	SDL_Renderer* _renderer;
	string _path;
	int _fontsize;
	SDL_Color _color;
	TTF_Font* _fonts;

public:
	SDL_Color default_color = { 255,255,255,255 };

	Text(SDL_Renderer* renderer, TTF_Font* font, string text, SDL_Color color = { 255,255,255,255 });

	~Text();

	SDL_Texture* Load(SDL_Renderer* renderer, TTF_Font* font, string text, SDL_Color color);

	void Render(SDL_Rect rect, SDL_Renderer* renderer);

	void Update(string updated_text);
	void Update(string updated_text, SDL_Color updated_color);

	void Draw();
};

