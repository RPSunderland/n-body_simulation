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
	void run();
	void pause();
	void draw_octree();
	void update_text();
	void draw_orbits();

public:
	Reporter* reporter;
	std::shared_ptr<Space> space;
	sf::RenderWindow window;
	sf::RectangleShape border;
	sf::View view;
	sf::Text text;
	sf::Font font;
	bool is_text_visible;
	bool is_octree_visible;
	bool is_orbits_visible;
};

