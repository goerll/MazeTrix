#pragma once

#include "global.h"

class Maze;

class Cell {
public:
    // Pointer to the maze the cell is in
    Maze* maze;

    // Position in the maze
    int x;
    int y;

    // Constructor
    Cell(Maze* maze = nullptr, int x = 0, int y = 0);

    // State
    bool active;
    bool highlighted;

    // Walls
    bool wall_up;
    bool wall_down;
    bool wall_left;
    bool wall_right;

    // Number of times the cell has been visited
    int times_visited { 0 };

    // Draw cell respecting state variables
    void draw();
    // Draw cell walls
    void drawWalls();
    // Draw cell square
    void drawSquare();

    // Verify if a cell is acessible from current cell
    bool isAcessible(Cell* cell);
    // Verify if a cell is a dead end (has no unvisited neighbours)
    bool isDeadEnd();

    // Neighbor acess methods
    // Get a neighbor from a specific direction
    Cell* getNeighbor(Direction direction);
    // Get all neighbors
    std::vector<Cell*> getNeighbors();
    // Get all neighbors acessible (with no walls in between)
    std::vector<Cell*> getAcessibleNeighbors();
    // Get all unvisited neighbors
    std::vector<Cell*> getUnvisitedNeighbors();
    // Get all acessible unvisited neighbors
    std::vector<Cell*> getAcessibleUnvisitedNeighbors();
    // Get a random neighbor from a list of neighbors
    Cell* getRandomNeighbor(std::vector<Cell*> potential_neighbors);
};
