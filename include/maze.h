#pragma once

#include "cell.h"
#include <array>
#include <list>
#include <memory>

class Pathfinder;

class Maze {
public:
    std::array<std::array<Cell, LINE_NUM>, COL_NUM> matrix;
    Pathfinder* pathfinder;

    int x, y;

    // Constructor
    Maze();
    Maze(int x, int y);
    Maze(Maze &maze);

    // Generate graph representation
    std::array<std::array<std::vector<Cell*>, LINE_NUM>, COL_NUM> toGraph();
    // Draw the maze on the screen
    void draw();
    // Reset the matrix's cells to their default state
    void reset();
    // Reset the number of times each cell has been visited
    void resetVisited();
    // Get the cell that is at a specific screen coordinate
    Cell* getCell(Vector2 coord);

    // Cell neighbor functions
    // Verify if a cell is acessible from current cell
    bool isAcessible(Cell* cell, Cell* neighbor);
    // Verify if a cell is a dead end (has no unvisited neighbours)
    bool isDeadEnd(Cell* cell);
    // Get a neighbor from a specific direction
    Cell* getNeighbor(Cell* cell, Direction direction);
    // Get all neighbors
    std::vector<Cell*> getNeighbors(Cell* cell);
    // Get all neighbors acessible (with no walls in between)
    std::vector<Cell*> getAcessibleNeighbors(Cell* cell);
    // Get all unvisited neighbors
    std::vector<Cell*> getUnvisitedNeighbors(Cell* cell);
    // Get all acessible unvisited neighbors
    std::vector<Cell*> getAcessibleUnvisitedNeighbors(Cell* cell);
    // Get a random neighbor from a list of neighbors
    Cell* getRandomNeighbor(std::vector<Cell*> potentialNeighbors);

    // Maze Generation
    // Turn the matrix into a maze using the binary tree algorithm
    void mazefyBinaryTree();
    // Turn the matrix into a maze using the depth first search algorithm
    void mazefyDepthFirstSearch(Cell* cell);
};
