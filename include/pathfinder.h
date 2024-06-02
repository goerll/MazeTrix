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
    std::array<std::array<std::vector<Cell*>, LINE_NUM>, COL_NUM> map;

    Maze* maze;

    int x;
    int y;


    Direction direction { down };

    // Constructor
    Pathfinder(Maze* maze, int x, int y);

    // Verifies if the pathfinder can walk forward
    bool is_free();
    // Walks the pathfinder forward and returns if it could do so
    bool walk();
    // Goes back to previous cell position
    void step_back();
    // Depth first search
    void depth_search(int x = COL_NUM-1, int y = LINE_NUM-1);
    // Verifies if pathfinder is in dead end
    bool dead_end();
    // Random viable way
    Cell* random_way();


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
