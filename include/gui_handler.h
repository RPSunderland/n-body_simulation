#pragma once
#include "reporter.h"

class Reporter;

class GUI_Handler {
public:
	GUI_Handler();
	GUI_Handler(const GUI_Handler& other) = delete;
	GUI_Handler(GUI_Handler&& other) noexcept = delete;
	GUI_Handler& operator=(const GUI_Handler& other) = delete;
	GUI_Handler& operator=(GUI_Handler&& other) noexcept = delete;
	~GUI_Handler() = default;
public:
	void initialize();
	void show();
	void pause();
	void resume();
	void speed_up();
	void slow_down();
	void draw_octree();

public:
	Reporter* reporter;
	std::shared_ptr<Space> space;
	sf::RenderWindow window;
	sf::RectangleShape border;
	sf::View view;
};

