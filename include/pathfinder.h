#pragma once

#include "maze.h"
#include <vector>
#include <algorithm>

class Pathfinder{
public:
    std::vector<Cell*> path;
    std::array<std::array<std::vector<Cell*>, LINE_NUM>, COL_NUM> map;

    Maze* maze;
    Cell* position;

    // Constructor
    Pathfinder(Maze* maze);

    // Draw the pathfinder (path included)
    void draw();

    // Verifies if pathfinder is in dead end
    bool isDeadEnd();
    // Random viable way
    Cell* getWay();
    // Change pathfinder position
    void setPosition(Cell* cell);
    // Update pathfinder's graph map and clear current path
    void update();

    // Depth first search
    void depthFirstSearch(Cell* end);

    // Breath first search
    void breadthFirstSearch(Cell* end);
};
