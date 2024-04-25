#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "include/global.h"
#include "include/maze.h"
#include "include/pathfinder.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "MazeTrix");
    window.setFramerateLimit(10);
    window.clear(BG_COLOR);

    Maze maze;
    Pathfinder pathfinder(&maze, 3, 0);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
          maze.reset();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
          window.setFramerateLimit(120);
          maze.mazefy_binary_tree(&window);
          window.setFramerateLimit(10);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
          window.setFramerateLimit(120);
          Cell* cell_at_mouse = maze.get_cell(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
          maze.mazefy_depth_first_search(&window, cell_at_mouse);
          window.setFramerateLimit(10);
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
          if (pathfinder.move_absolute(up))
          std::cout << pathfinder.x << " " << pathfinder.y << std::endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
          if (pathfinder.move_absolute(down))
          std::cout << pathfinder.x << " " << pathfinder.y << std::endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
          if (pathfinder.move_absolute(left))
          std::cout << pathfinder.x << " " << pathfinder.y << std::endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
          if (pathfinder.move_absolute(right))
          std::cout << pathfinder.x << " " << pathfinder.y << std::endl;
        }


        window.clear(BG_COLOR);
        maze.draw(&window);

        pathfinder.draw(&window);


        window.display();
    }

    return 0;
}
