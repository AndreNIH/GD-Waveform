#pragma once
#include <SDL.h>

class Drawable {
protected:
	int _x;
	int _y;
public:
	virtual void draw_node(SDL_Renderer* sharedRender) = 0;
	virtual Drawable* send_copy() = 0;
	void setX(int x);
	void setY(int y);
	void setPos(int x, int y);
	virtual ~Drawable();
};