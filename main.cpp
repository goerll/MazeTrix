#include <SFML/Graphics.hpp>
#include "include/maze.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "MazeTrix");
    window.setFramerateLimit(120);
    window.clear(NORD_DARK);

    Maze maze;
    maze.mazefy_depth_first_search(&window, &(maze.matrix[10][10]));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(NORD_DARK);

        maze.draw(&window);

        window.display();
    }

    return 0;
}
