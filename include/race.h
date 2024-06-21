#pragma once

#include "maze.h"
#include <raylib.h>

class Race {
    private:
        std::vector<Maze*> mazeGrid;

    public:
        Race();

        // Draw all mazes
        void draw();
        // Reset all mazes
        void reset();
        // Get maze at mouse position
        Maze* getMaze();
        // Generate maze with depth first search at mouse
        void mazefyDepthFirst();
        // Generate maze with binary tree search at mouse
        void mazefyBinaryTree();
        // Set pathfinder position to cell at mouse 
        void setPathfinderPosition();
        // Make pathfinder find it's way to cell at mouse
        // (depth first for left maze, binary tree for right maze)
        void findWay();
};
