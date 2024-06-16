#pragma once

#include "cell.h"
#include "global.h"
#include <array>
#include <list>

class Pathfinder;

class Maze {
public:
    std::array<std::array<Cell, LINE_NUM>, COL_NUM> matrix;
    Pathfinder* pathfinder;

    int x;
    int y;

    // Constructor
    Maze(int x = 0, int y = 0);

    // Generate graph representation
    std::array<std::array<std::vector<Cell*>, LINE_NUM>, COL_NUM> toGraph();
    // Draw the maze on the screen
    void draw();
    // Reset the matrix's cells to their default state
    void reset();
    // Reset the number of times each cell has been visited
    void resetVisited();
    // Get the cell that is at a specific screen coordinate
    Cell* getCell(Vector2 coord);

    // Maze Generation
    // Turn the matrix into a maze using the binary tree algorithm
    void mazefyBinaryTree();
    // Turn the matrix into a maze using the depth first search algorithm
    void mazefyDepthFirstSearch(Cell* cell);
};
