#pragma once

#include "structs.h"

class Cell {
public:
    // Position in the maze
    Vector2i position;

    // Constructor
    Cell();
    Cell(Vector2i position);

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
    void draw(Vector2i offset);
    // Draw cell walls
    void drawWalls(Vector2i offset);
    // Draw cell square
    void drawSquare(Vector2i offset);
};
