#pragma once

#include "maze.h"
#include <raylib.h>

class Race {
    std::vector<Maze> mazeGrid;

public:
    Race();

    // Draw all mazes
    void draw();
    // Reset all mazes
    void reset();
    // Get maze at mouse position
    Maze *getMaze();
    // Generate maze with depth first search at mouse
    void mazefyDepthFirst();
    // Generate maze with binary tree search at mouse
    void mazefyBinaryTree();
};
