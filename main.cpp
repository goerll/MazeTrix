#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "include/maze.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "MazeTrix");
    window.setFramerateLimit(120);
    window.clear(NORD_DARK);

    Maze maze;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
          maze.clear();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
          maze.mazefy_binary_tree(&window);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
          Cell* cell_at_mouse = maze.get_cell(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
          maze.mazefy_depth_first_search(&window, cell_at_mouse);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
          Cell* cell_at_mouse = maze.get_cell(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
          cell_at_mouse->active = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
          Cell* cell_at_mouse = maze.get_cell(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
          cell_at_mouse->active = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)){
          Cell* cell_at_mouse = maze.get_cell(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
          cell_at_mouse->highlighted = !cell_at_mouse->highlighted;
        }

        window.clear(NORD_DARK);

        maze.draw(&window);

        window.display();
    }

    return 0;
}
