#pragma once
#include "WindowBase.h"
#include "Drawable.h"

class MainWindow : public WindowBase {
private:
	constexpr static short CURSORLINE_WIDTH = 3;
	SDL_Texture* _texture = nullptr;
	void eventHandler(SDL_Event& Event) override;
	uint16_t grid_x = 0;
	bool enableCursorUpdate = false;
	SDL_Rect cursorHighlight{ 0,0,CURSORLINE_WIDTH,255 };
	void copy(const MainWindow& rhs);
	void dealloc();
public:
	MainWindow(const std::string& title, int width, int height);
	MainWindow(const MainWindow& rhs);
	MainWindow& operator=(const MainWindow& rhs);
	~MainWindow();
	void load_image(const std::string& filename);
	void draw() override;
	int get_x() const;
};