//#include "../include/octree.h" //x
//#include "../include/reporter.h"


#include <SFML/Graphics.hpp>
#include "../include/vector.h"






sf::Vector2f to_graphic_coords(Vector v) {
    double x = v.x + 500;
    double y = -v.y + 500;
    return sf::Vector2f(x, y);
}


class Bod : public sf::CircleShape {
public:
    Bod(double mass, double radius, Vector position, Vector velocity) : sf::CircleShape(radius), mass(mass), radius(radius), position(position), velocity(velocity), acceleration(0, 0, 0) { 
        sf::Vector2f graphic_position = to_graphic_coords(position);
        setPosition(graphic_position);
        setFillColor(sf::Color::White);
    }
    void move() {
        sf::Vector2f graphic_velocity = sf::Vector2f(velocity.x, -velocity.y);
        double dx = graphic_velocity.x * 1; //dt
        double dy = graphic_velocity.y * 1; 
        sf::CircleShape::move(dx, dy);
    }
public:
    double mass;
    double radius;
    Vector position;
    Vector velocity;
    Vector acceleration;
};


void hadle_escape(int i, std::vector<Bod>& bodies) {
    bodies.erase(bodies.begin() + i);
};

void hadle_collision(int i, int j, std::vector<Bod>& bodies) {
    bodies[i].velocity = (bodies[j].mass * bodies[j].velocity + bodies[i].mass * bodies[i].velocity) / (bodies[i].mass + bodies[j].mass);
    bodies[i].mass += bodies[j].mass;
    bodies[i].radius = std::pow(std::pow(bodies[i].radius, 3) + std::pow(bodies[j].radius, 3), 1.0 / 3);
    bodies[i].setRadius(bodies[i].radius);
    bodies.erase(bodies.begin() + j);
}






int main(int argc, char* argv[]) {
	//Reporter reporter; //create reporter (singleton?)
	//reporter.create_space(); //reporter create default empty space
	//reporter.read_file_data(argv[1]); //reporter will make reader to read data to space
	//reporter.run(); //reporter will start simulation and make writer to write data to file in specific time interval






    sf::RenderWindow window(sf::VideoMode(1000, 1000), "n-body_simulation");
    window.setFramerateLimit(60);

    sf::RectangleShape border(sf::Vector2f(10000, 10000));
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(sf::Color::Red);
    border.setOutlineThickness(1);
    border.setOrigin(border.getSize() / 2.f);   //? border.setOrigin(window.getSize() / 2.f);
    border.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

    sf::View view;
    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);


    
    std::vector<Bod> bodies;


    for (int i = 1; i <= 100; ++i) {
        Vector pos;
        Vector vel;
        double r = 5;
        pos.x = rand() % 2000 - 1000;
        pos.y = rand() % 2000 - 1000;
        //vel.x = ((rand() % 20) - 10) / 10.f;
        //vel.y = ((rand() % 20) - 10) / 10.f;
        vel.x = 0;
        vel.y = 0;

        bodies.push_back(Bod(10, r, pos, vel));
    }

    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { window.close(); }
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) { view.zoom(0.9f); }
                else if (event.mouseWheelScroll.delta < 0) { view.zoom(1.1f); }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            view.move(0, -10);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            view.move(0, 10);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            view.move(-10, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            view.move(10, 0);

       /* for (auto it = bodies.begin(); it != bodies.end(); ) {
            it->move();
            if (!border.getGlobalBounds().contains(it->getPosition())) {
                it = bodies.erase(it);
                std::cout << "elo";
            }
            else {
                ++it;
            }
        }*/


        double dt = 1;

        for (int i = 0; i < bodies.size(); ++i) {
            Vector acceleration;
            for (int j = 0; j < bodies.size(); ++j) {
                if (i == j) continue;
                Vector r = bodies[j].position - bodies[i].position;
                if (r.norm() < bodies[i].radius + bodies[j].radius) {
                    hadle_collision(i, j, bodies);
                    std::cout << "boom \n";
                    --j;
                    continue;
                }
                acceleration += (G * bodies[j].mass / r.sq_norm()) * (r / r.norm());
            }
            bodies[i].velocity += acceleration * static_cast<double>(dt);
        }

        for (int i = 0; i < bodies.size(); ++i) {
            bodies[i].position += bodies[i].velocity * static_cast<double>(dt);
            if (bodies[i].position.max_norm() > 5000) {
                if (!border.getGlobalBounds().contains(bodies[i].getPosition())) { std::cout << "wow"; }
                hadle_escape(i, bodies);
                std::cout << "elo \n";
                --i;
            }
        }

        for (auto it = bodies.begin(); it != bodies.end(); ++it) {
            it->move();
        }

      



        window.clear(sf::Color::Black);
        window.setView(view);
        window.draw(border);
        for (const auto& bod : bodies) {
            window.draw(bod);
        }

        window.display();
    }






	return 0;
}







//reporter.stop(); //reporter will stop simulation