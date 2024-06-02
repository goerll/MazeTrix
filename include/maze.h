#pragma once
#include "cell.h"
#include "global.h"
#include <SFML/Graphics.hpp>
#include <array>
#include <list>
class Maze {
public:
    std::array<std::array<Cell, LINE_NUM>, COL_NUM> matrix;

    int x;
    int y;

    // Constructor
    Maze(int x = 0, int y = 0);

    // Draw the maze on the screen
    void draw(sf::RenderWindow* window);
    // Reset the matrix's cells to their default state
    void reset();
    // Generate graph representation
    std::array<std::array<std::vector<Cell*>, LINE_NUM>, COL_NUM> toGraph();

    void resetVisited();
    // Get the cell that is at a specific screen coordinate
    Cell* get_cell(float x, float y);
    Cell* getFinish();
    // Turn the matrix into a maze using the binary tree algorithm
    void mazefy_binary_tree(sf::RenderWindow* window);
    // Turn the matrix into a maze using the depth first serach algorithm
    void mazefy_depth_first_search(sf::RenderWindow* window, Cell* cell);

};
