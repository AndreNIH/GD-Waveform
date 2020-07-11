#pragma once
#include <SDL_ttf.h>
#include "Drawable.h"
#include <string>
#include <stdexcept>
class LabelTTF : public Drawable{
private:
	SDL_Texture* _texture = nullptr;
	TTF_Font* _font = nullptr;
	SDL_Rect _labelRect;
	std::string _label;
	SDL_Color _labelColor = {0,0,255,0};
	SDL_Texture* get_label_texture(SDL_Renderer* renderer);
public:
	LabelTTF(const std::string& text, const std::string& fontname, int fontSize);
	~LabelTTF();
	void set_position(int x, int y);
	void set_label(const std::string& text);
	static LabelTTF create_string(const std::string& text, const std::string& fontname, int fontSize);
	static LabelTTF create_string(const std::string& fontname, int fontSize);
	void draw_node(SDL_Renderer* sharedRender) override;

};