#include "Labels.h"
#include <iostream>
LabelTTF::LabelTTF(const std::string& text, const std::string& fontname, int fontSize)
{
	TTF_Font* font = TTF_OpenFont(fontname.c_str(), fontSize);
	std::cout << SDL_GetError() << "\n";
	if (!font) throw std::runtime_error{ "TTF_Font Error" };
	_font = font;
	set_label(text);
}

LabelTTF::~LabelTTF()
{
	if (_surface) SDL_FreeSurface(_surface);
}

void LabelTTF::set_label(const std::string& text)
{
	if (_surface != nullptr) {
		SDL_FreeSurface(_surface);
		_surface = nullptr;
	}
	_surface = TTF_RenderText_Solid(_font, text.c_str(), { 0,0,255,0 });
	if (!_surface) std::runtime_error{ "TTF_RenderTextSolid Error" };
}

void LabelTTF::set_position(int x, int y) {
	_labelRect.x = x;
	_labelRect.y = y;
}

LabelTTF LabelTTF::create_string(const std::string& text, const std::string& fontname, int fontSize) {return LabelTTF(text, fontname,fontSize);}
LabelTTF LabelTTF::create_string(const std::string& fontName, int fontSize) { return LabelTTF("", fontName, fontSize);  }

void LabelTTF::draw_node(SDL_Renderer* sharedRender)
{
	auto text_texture = SDL_CreateTextureFromSurface(sharedRender, _surface);
	if(!text_texture) std::runtime_error{ "SDL_CreateTextureFromSurface Error" };
	SDL_QueryTexture(text_texture, nullptr, nullptr, &_labelRect.w, &_labelRect.h);
	SDL_RenderCopy(sharedRender, text_texture, nullptr, &_labelRect);
	SDL_DestroyTexture(text_texture);
}
