#pragma once

#include "maze.h"
#include <array>

class Race {

    public:
        std::array<Maze, 2> mazeGrid;

        Race();

        void draw();
        void reset();
        Cell* getCell(Vector2 coord);
        Maze* getMaze(Vector2 coord);
        void mazefyDepthFirst(Vector2 coord);
        void mazefyBinaryTree(Vector2 coord);
};
