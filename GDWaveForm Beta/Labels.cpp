#include "Labels.h"
#include <iostream>
SDL_Texture* LabelTTF::get_label_texture(SDL_Renderer* renderer)
{
	SDL_Surface* surface = TTF_RenderText_Solid(_font, _label.c_str(), _labelColor);
	if (surface == nullptr) return nullptr;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

Drawable* LabelTTF::send_copy()
{
	// create new object of the same class based on this one
	LabelTTF* temp = new LabelTTF(_label, _fontName, _fontSize);
	
	// deep copy every aspect of this object to the new one
	temp->_x = _x;
	temp->_y = _y;
	temp->_renderer = _renderer; // copied labels may have the same renderer. Please advise.
	temp->_font = TTF_OpenFont(_fontName.c_str(), _fontSize);

	
	// return the new object as a pointer to the Drawable ABC object.
	return temp;
}

LabelTTF::LabelTTF(const std::string& text, const std::string& fontname, int fontSize)
{
	_fontName = fontname;
	_fontSize = fontSize;
	TTF_Font* font = TTF_OpenFont(fontname.c_str(), fontSize);
	std::cout << SDL_GetError() << "\n";
	if (!font) throw std::runtime_error{ "TTF_Font Error" };
	_font = font;
	set_label(text);
}

LabelTTF::~LabelTTF()
{

}

void LabelTTF::set_label(const std::string& text)
{
	_label = text;	
}

void LabelTTF::set_position(int x, int y) {
	_labelRect.x = x;
	_labelRect.y = y;
}

LabelTTF LabelTTF::create_string(const std::string& text, const std::string& fontname, int fontSize) {return LabelTTF(text, fontname,fontSize);}
LabelTTF LabelTTF::create_string(const std::string& fontName, int fontSize) { return LabelTTF("", fontName, fontSize);  }

void LabelTTF::draw_node(SDL_Renderer* sharedRender)
{
	_renderer = sharedRender;
	SDL_Texture* text_texture = get_label_texture(sharedRender);
	if(!text_texture) std::runtime_error{ "SDL Label Texture Error" };
	SDL_QueryTexture(text_texture, nullptr, nullptr, &_labelRect.w, &_labelRect.h);
	SDL_RenderCopy(sharedRender, text_texture, nullptr, &_labelRect);
	SDL_DestroyTexture(text_texture);
}
