#pragma once
#include "structs.h"
#include <vector>

class Maze;
class Pathfinder{
    private:
        // Pointer to the maze the pathfinder's in
        Maze* maze;
        // Position in the maze
        Vector2i position;

        // Pathfinder position history
        std::vector<Vector2i> path;
        // Graph map
        std::vector<std::vector<std::vector<Vector2i>>> map;

    public:
        // Constructor
        Pathfinder(Maze* maze);

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
        // Clear path
        void clearPath();
        // Push to path
        void pathPush(Vector2i cell);
        // Pop from path
        void pathPop();

        // Use depth first search to find path to end
        void depthFirstSearch(Vector2i end);
        // Use breath first search to find path to end
        void breadthFirstSearch(Vector2i end);

        // Getters
        Vector2i getPosition();
        Vector2i getPathTop();
        bool isPathEmpty();
};
