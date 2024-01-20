#include "../include/gui_handler.h"

GUI_Handler::GUI_Handler() : reporter(nullptr), space(nullptr), window(), border(), view(), text(), font(), is_text_visible(true), is_octree_visible(false), is_orbits_visible(false) { }
void GUI_Handler::initialize() {
    window.create(sf::VideoMode(1000, 1000), "n-body_simulation");
    window.setFramerateLimit(60);
    
    border.setSize({ 10000.f, 10000.f });
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(sf::Color::Red);
    border.setOutlineThickness(3);
    border.setOrigin(border.getSize() / 2.f);   
    border.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
    
    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);

    if (!font.loadFromFile("resources/arial.ttf")) {
        std::cerr << "Invalid font file path.\n";
        return;
    }
    text.setFont(font);
    text.setCharacterSize(100);
    float initialScale = 0.1f;
    text.setScale(initialScale, initialScale);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    text.setString(std::string{ });
}


void GUI_Handler::run() {

    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        window.setView(view);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { window.close(); }
            else if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) { view.zoom(0.9f); }
                else if (event.mouseWheelScroll.delta < 0) { view.zoom(1.1f); }
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) { pause(); }
                else if (event.key.code == sf::Keyboard::O) { is_octree_visible = !is_octree_visible; pause(); }
                else if (event.key.code == sf::Keyboard::T) { is_text_visible = !is_text_visible; }
                else if (event.key.code == sf::Keyboard::C) { is_orbits_visible = !is_orbits_visible; }
            }
        }
        
        sf::Vector2f move_offset(0.f, 0.f);
        float speed_factor = view.getSize().x / window.getSize().x;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { move_offset.y = -25 * speed_factor; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { move_offset.y = 25 * speed_factor; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { move_offset.x = -25 * speed_factor; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { move_offset.x = 25 * speed_factor; }
        sf::FloatRect borderBounds = border.getGlobalBounds();
        sf::Vector2f new_position = view.getCenter() + move_offset;
        if (new_position.x - view.getSize().x / 2.f >= borderBounds.left - 25 &&
            new_position.x + view.getSize().x / 2.f <= borderBounds.left + borderBounds.width + 25 &&
            new_position.y - view.getSize().y / 2.f >= borderBounds.top - 25 &&
            new_position.y + view.getSize().y / 2.f <= borderBounds.top + borderBounds.height + 25) {
            view.move(move_offset);
        }
        
        if (is_octree_visible) {
            reporter->is_running = false;
            draw_octree();
        }

        if (reporter->is_running) {
            if (!space->simulation_step()) { return; }
            if (reporter->is_file_writing) {
                if (space->current_time % reporter->writer->print_time_interval < space->dt) {
                    reporter->writer->write_space();
                }
            }
        }

        if (reporter->is_running) {
            for (auto& body : space->bodies) {
                body.move();
            }
        }
        window.draw(border);

        for (auto& body : space->bodies) {
            window.draw(body);
        }

        if (!is_orbits_visible) {
            space->save_positions = false;
            space->body_positions.clear();
        }
        if (is_orbits_visible) {
            space->save_positions = true;
            draw_orbits();
        }

        if (is_text_visible) {
            update_text();
            window.draw(text);
        }

        window.display();
    }

}

void GUI_Handler::pause() { reporter->is_running = !reporter->is_running; }
void GUI_Handler::draw_octree() {
    auto it = space->octree.create_iterator();
    Node* node;
    while (!it->is_end()) {
        node = it->current();
        if (node != nullptr) {
            double length = node->octant.length;
            Vector v1 = node->octant.anchor;
            Vector v2 = v1 + Vector{ length, 0, 0 };
            Vector v3 = v1 + Vector{ length, length, 0 };
            Vector v4 = v1 + Vector{ 0, length, 0 };

            sf::Vector2f w1 = to_graphic_coords(v1);
            sf::Vector2f w2 = to_graphic_coords(v2);
            sf::Vector2f w3 = to_graphic_coords(v3);
            sf::Vector2f w4 = to_graphic_coords(v4);

            sf::ConvexShape square;
            square.setPointCount(4);
            square.setPoint(0, w1);
            square.setPoint(1, w2);
            square.setPoint(2, w3);
            square.setPoint(3, w4);

            square.setOutlineColor(sf::Color::Green);
            square.setFillColor(sf::Color::Transparent);
            square.setOutlineThickness(1); 
            window.draw(square); 
        }
        node = it->next();
    }

}
void GUI_Handler::update_text() {
    text.setString(std::string{ });
    std::string tmp_text;
    tmp_text += std::string("Amount of bodies: ") + std::to_string(space->body_count) + std::string("\n");
    tmp_text += std::string("Current time: ") + std::to_string(space->current_time) + std::string("\n");
    tmp_text += std::string("Biggest radius: ") + std::to_string(space->bodies[space->largest_body_index()].radius) + std::string("\n");
    text.setString(tmp_text);
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();
    float padding = 10.0f; 
    text.setPosition(viewCenter.x + viewSize.x / 2.f - text.getGlobalBounds().width - padding, viewCenter.y + viewSize.y / 2.f - text.getGlobalBounds().height - padding);
}

void GUI_Handler::draw_orbits() {
    sf::VertexArray orbits(sf::Points);
    for (auto& body_position : space->body_positions) {
        for (auto& position : body_position) {
            sf::Vector2f graphic_position = to_graphic_coords(position);
            orbits.append(sf::Vertex(graphic_position, sf::Color::Blue));
        }
    }
    window.draw(orbits);
}