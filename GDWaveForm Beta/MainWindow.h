#pragma once
#include "WindowBase.h"
#include "Drawable.h"

constexpr short CURSORLINE_WIDTH = 3;
     
class MainWindow : public WindowBase {
private:
	SDL_Texture* _texture = nullptr;
	void eventHandler(SDL_Event& Event) override;
	uint16_t grid_x = 0;
	bool enableCursorUpdate = false;
	SDL_Rect cursorHighlight{ 0,0,CURSORLINE_WIDTH,255 };

public:
	MainWindow(const std::string& title, int width, int height);
	~MainWindow();
	void load_image(const std::string& filename);
	void draw() override;
	int get_x() const;
};