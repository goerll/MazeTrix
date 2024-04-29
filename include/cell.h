#pragma once

#include <SFML/Graphics.hpp>
#include "global.h"

class Maze;

class Cell {
public:
    // Pointer to the maze the cell is in
    Maze* maze;

    // Position in the maze
    int x;
    int y;

    // State
    bool active{ true };
    bool highlighted{ false };

    bool wall_up{ true };
    bool wall_down{ true };
    bool wall_left{ true };
    bool wall_right{ true };

    int times_visited { 0 };

    // Draw cell respecting state variables
    void draw(sf::RenderWindow* window);
    // Draw cell but with offset
    void draw(sf::RenderWindow* window, int offset_x, int offset_y);
    // Draw cell as if it was highlighted
    void draw_highlighted(sf::RenderWindow* window);
    // Get a neighbor from a cell
    Cell* get_neighbor(Direction direction);
    // Get a random unvisited neighbor from a cell
    Cell* random_unvisited_neighbor();
    // Verify if a cell is a dead end (has no unvisited neighbours)
    bool is_dead_end();
};
