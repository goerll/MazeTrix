#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "include/global.h"
#include "include/maze.h"
#include "include/pathfinder.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(WIN_SIZE_X, WIN_SIZE_Y), "MazeTrix");
    window.setFramerateLimit(10);
    window.clear(BG_COLOR);

    Maze maze(0,0);
    maze.mazefy_depth_first_search(&window, &maze.matrix[0][0]);
    Pathfinder joe(&maze, 0, 0);
    joe.depthFirstSearch();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        /* RESET MAZE */
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
          maze.reset();
        }

        /* BINARY TREE */
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
          window.setFramerateLimit(120);
          maze.mazefy_binary_tree(&window);
          window.setFramerateLimit(10);
        }

        /* DEPTH FIRST SEARCH */
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
          window.setFramerateLimit(120);
          Cell* cell_at_mouse = maze.get_cell(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
          maze.mazefy_depth_first_search(&window, cell_at_mouse);
          window.setFramerateLimit(10);
        }

        /* DEACTIVATE CELL AT MOUSE */
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
          Cell* cell_at_mouse = maze.get_cell(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
          cell_at_mouse->active = false;
        }

        /* ACTIVATE CELL AT MOUSE */
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
          Cell* cell_at_mouse = maze.get_cell(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
          cell_at_mouse->active = true;
        }

        /* HIGLIGHT CELL AT MOUSE */
        /* if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)){ */
        /*   Cell* cell_at_mouse = maze.get_cell(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y); */
        /*   cell_at_mouse->highlighted = !cell_at_mouse->highlighted; */
        /* } */
        /**/
        /* PATHFINDER MOVEMENTS */
        /* if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)){ */
        /*   if (pathfinder.move_absolute(up)) */
        /*   std::cout << pathfinder.x << " " << pathfinder.y << std::endl; */
        /* } */
        /* if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)){ */
        /*   if (pathfinder.move_absolute(down)) */
        /*   std::cout << pathfinder.x << " " << pathfinder.y << std::endl; */
        /* } */
        /* if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)){ */
        /*   if (pathfinder.move_absolute(left)) */
        /*   std::cout << pathfinder.x << " " << pathfinder.y << std::endl; */
        /* } */
        /* if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)){ */
        /*   if (pathfinder.move_absolute(right)) */
        /*   std::cout << pathfinder.x << " " << pathfinder.y << std::endl; */
        /* } */

        /* WINDOW REFRESH */
        window.clear(BG_COLOR);

        maze.draw(&window);
        joe.draw(&window);

        window.display();
    }

    return 0;
}
