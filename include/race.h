#pragma once

#include "maze.h"
#include <array>

class Race {
    std::array<Maze, 2> mazeGrid;

    public:

        Race();

        // Draw all mazes
        void draw();
        // Reset all mazes
        void reset();
        // Get maze at mouse position
        Maze* getMaze(Vector2 coord);
        // Generate maze with depth first search at mouse
        void mazefyDepthFirst(Vector2 coord);
        // Generate maze with binary tree search at mouse
        void mazefyBinaryTree(Vector2 coord);
};
