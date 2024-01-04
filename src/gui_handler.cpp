#include "../include/gui_handler.h"

GUI_Handler::GUI_Handler() : reporter(nullptr), space(nullptr), window(), border(), view() { }
void GUI_Handler::initialize() {
    window.create(sf::VideoMode(1000, 1000), "n-body_simulation");
    window.setFramerateLimit(60);
    
    border.setScale(sf::Vector2f(10000, 10000));
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(sf::Color::Red);
    border.setOutlineThickness(1);
    border.setOrigin(border.getSize() / 2.f);   //? border.setOrigin(window.getSize() / 2.f);
    border.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
    
    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
}


void GUI_Handler::show() {

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { window.close(); }
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) { view.zoom(0.9f); }
                else if (event.mouseWheelScroll.delta < 0) { view.zoom(1.1f); }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { view.move(0, -10); }     
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { view.move(0, 10); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { view.move(-10, 0); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { view.move(10, 0); }
            
        if (reporter->is_running) {
            if (!space->simulation_step()) { return; }
            if (reporter->is_file_writing) {
                //hmmm
            }
        }

        for (auto& body : space->bodies) {
            body.move();
        }

        window.clear(sf::Color::Black);
        window.setView(view);
        window.draw(border);


        for (auto& body : space->bodies) {
            window.draw(body);
        }

        window.display();
    }

}

void GUI_Handler::pause() { }
void GUI_Handler::resume() {}
void GUI_Handler::speed_up() {}
void GUI_Handler::slow_down() {}
void GUI_Handler::draw_octree() {}