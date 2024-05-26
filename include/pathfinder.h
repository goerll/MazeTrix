#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "cell.h"
#include "maze.h"
#include "global.h"

class Pathfinder{
public:
    std::vector<Cell*> path;
    Maze* maze;
    int x;
    int y;
    Direction direction { down };

    // Constructor
    Pathfinder(Maze* maze, int x, int y);
    // Verifies if the cell at a relative position can be accessed
    bool is_path(Direction side);
    // Moves the pathfinder to an absolute given direction
    bool move_absolute(Direction direction);
    // Moves the pathfinder to a relative given direction
    bool move_relative(Direction direction);
    // Draw the pathfinder
    void draw(sf::RenderWindow* window);
    // Draw pathfinder's path
    void draw_path(sf::RenderWindow* window);
    // Get the absolute direction given a direction based on the pathfinder's orientation
    Direction get_absolute_dir(enum Direction direction);
    // Turn pathfinder to relative direction
    void turn(Direction direction);
    void find_right_hand(Maze* maze, Cell* start, Cell* finish);
    bool find_recursive(Maze* maze, Cell* start);
};
