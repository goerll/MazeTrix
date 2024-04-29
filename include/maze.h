#pragma once
#include "cell.h"
#include "global.h"
#include <SFML/Graphics.hpp>
#include <array>

class Maze {
public:
    std::array<std::array<Cell, LINE_NUM>, COL_NUM> matrix;

    int x { 0 };
    int y { 0 };

    // Constructor
    Maze();
    // Constructor
    Maze(int x, int y);
    // Draw the maze on the screen
    void draw(sf::RenderWindow* window);
    // Reset the matrix's cells to their default state
    void reset();
    // Get the cell that is at a specific screen coordinate
    Cell* get_cell(float x, float y);
    // Turn the matrix into a maze using the binary tree algorithm
    void mazefy_binary_tree(sf::RenderWindow* window);
    // Turn the matrix into a maze using the depth first serach algorithm
    void mazefy_depth_first_search(sf::RenderWindow* window, Cell* cell);

};
