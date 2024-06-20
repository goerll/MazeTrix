#pragma once

#include "global.h"

class Cell {
public:
    // Position in the maze
    int x;
    int y;

    // Constructor
    Cell(int x = 0, int y = 0);

    // State
    bool active;

    // Walls
    bool wall_up;
    bool wall_down;
    bool wall_left;
    bool wall_right;

    // Number of times the cell has been visited
    int times_visited;

    // Draw cell respecting state variables
    void draw(int offsetX, int offsetY);;
    // Draw cell walls
    void drawWalls(int offsetX, int offsetY);
    // Draw cell square
    void drawSquare(int offsetX, int offsetY);
};
