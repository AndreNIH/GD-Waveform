#include <iostream>
#include "MainWindow.h"
#include "Labels.h"
//TODO:aadd super-init function for C libraries
template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	if (size <= 0) { throw std::runtime_error("Error during formatting."); }
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

const int pixel_to_second(int pixel){
	constexpr int total_pixels = 1280;
	constexpr int total_seconds= 92;
	int seconds = (pixel * 92) / total_pixels;
	return seconds;
}

bool library_superinit() {
	if (SDL_Init(SDL_INIT_EVERYTHING)) return false;
	if (TTF_Init()) return false;
	if ((IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG) != IMG_INIT_PNG) return false; //major piece of shit
}
int main(int argc, char** argv) {
	
	if (library_superinit()) {
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) std::cerr << "Error";
		TTF_Init();
		MainWindow mainWindow("GDWaveform Beta 1.0.0", 1280, 250);
		LabelTTF time_label = time_label.create_string("arial.ttf", 24);
		time_label.setPos(0, 0);

		mainWindow.load_image("toe2waveformrenderfull.png");
		mainWindow.append(&time_label);


		while (!mainWindow.is_closed()) {
			const int seconds = pixel_to_second(mainWindow.get_x());
			mainWindow.poll_event();
			time_label.set_label(string_format("%02d:%02d", seconds / 60, seconds % 60));
			mainWindow.draw();
		}
	}
	
	
	if(SDL_WasInit(SDL_INIT_EVERYTHING) ) SDL_Quit();
	if(TTF_WasInit()) TTF_Quit();
	IMG_Quit(); //wishful thinking writes good code :D
	return 0;
}