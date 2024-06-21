#pragma once

#include "global.h"
#include "structs.h"

class Cell {
    private:
        // Position in the maze
        Vector2i position;

        // State
        bool active;

        // Walls
        bool wall_up;
        bool wall_down;
        bool wall_left;
        bool wall_right;

        // Number of times the cell has been visited
        int times_visited;

    public:
        // Constructor
        Cell();
        Cell(Vector2i position);

        // Draw cell respecting state variables
        void draw(Vector2i offset);
        // Draw cell walls
        void drawWalls(Vector2i offset);
        // Draw cell square
        void drawSquare(Vector2i offset);

        // Getters
        Vector2i getPosition();
        bool getWall(Direction direction);
        bool getActive();
        int getTimesVisited();

        // Setters
        void setActive(bool state);
        void setWall(Direction direction, bool state);
        void increaseTimesVisited();
        void resetTimesVisited();
};
