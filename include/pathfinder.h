#pragma once
#include "structs.h"
#include <vector>
#include <algorithm>

class Maze;
class Pathfinder{
public:
    std::vector<Vector2i> path;
    std::vector<std::vector<std::vector<Vector2i>>> map;

    Maze* maze;
    Vector2i position;

    // Constructor
    Pathfinder(Maze* maze);
    ~Pathfinder() = default;

    // Draw the pathfinder (path included)
    void draw();

    // Verifies if pathfinder is in dead end
    bool isDeadEnd();
    // Random viable way
    Vector2i getWay();
    // Change pathfinder position
    void setPosition(Vector2i cell);
    // Update pathfinder's graph map and clear current path
    void update();

    // Depth first search
    void depthFirstSearch(Vector2i end);
    // Breath first search
    void breadthFirstSearch(Vector2i end);
};
