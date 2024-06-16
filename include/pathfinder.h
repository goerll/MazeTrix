#pragma once

#include <vector>
#include "cell.h"
#include "maze.h"
#include "global.h"
#include <algorithm>

class Pathfinder{
public:
    std::vector<Cell*> path;
    std::array<std::array<std::vector<Cell*>, LINE_NUM>, COL_NUM> map;

    Maze* maze;
    Cell* position;

    // Constructor
    Pathfinder(Maze* maze, int x, int y);


    // Draw the pathfinder (path included)
    void draw();
    // Draw pathfinder's path
    void drawPath();

    // Verifies if pathfinder is in dead end
    bool isDeadEnd();
    // Random viable way
    Cell* getWay();
    // Change pathfinder position
    void setPosition(Cell* cell);
    // Update pathfinder's graph map and clear current path
    void update();

    // Depth first search
    bool depthFirstSearch(Cell* start, Cell* end);
    bool depthFirstSearch(Cell* end);
    void depthFirstSearch();

    // Breath first search
    void breadthFirstSearch(Cell* end);
};
