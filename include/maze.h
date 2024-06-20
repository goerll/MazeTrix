#pragma once

#include "pathfinder.h"
#include "cell.h"
#include <array>
#include <list>
#include <memory>

class Maze {
public:
    Vector2i position;
    std::vector<std::vector<Cell>> matrix;
    std::unique_ptr<Pathfinder> pathfinder;

    // Constructor
    Maze();
    Maze(Vector2i pos);

    // Generate graph representation
    std::vector<std::vector<std::vector<Vector2i>>> toGraph();
    // Draw the maze on the screen
    void draw();
    // Copy the cell states of another maze
    void copyMatrix(const Maze& maze);
    // Reset the matrix's cells to their default state
    void reset();
    // Reset the number of times each cell has been visited
    void resetVisited();
    // Get cell coordinates at mouse position, if applicable
    Vector2i getMouseCell();
    // Get the cell that is at a specific screen coordinate
    Cell& getCell(Vector2i cell);

    // Cell neighbor functions
    // Verify if a cell is acessible from current cell
    bool isAccessible(Vector2i cell, Vector2i neighbor);
    // Verify if a cell is a dead end (has no unvisited neighbours)
    bool isDeadEnd(Vector2i cell);
    // Get a neighbor from a specific direction
    Vector2i getNeighbor(Vector2i cell, Direction direction);
    // Get all neighbors
    std::vector<Vector2i> getNeighbors(Vector2i cell);
    // Get all neighbors acessible (with no walls in between)
    std::vector<Vector2i> getAccessibleNeighbors(Vector2i cell);
    // Get all unvisited neighbors
    std::vector<Vector2i> getUnvisitedNeighbors(Vector2i cell);
    // Get all acessible unvisited neighbors
    std::vector<Vector2i> getAccessibleUnvisitedNeighbors(Vector2i cell);
    // Get a random neighbor from a list of neighbors
    Vector2i getRandomNeighbor(std::vector<Vector2i> potentialNeighbors);

    // Maze Generation
    // Turn the matrix into a maze using the binary tree algorithm
    void mazefyBinaryTree();
    // Turn the matrix into a maze using the depth first search algorithm
    void mazefyDepthFirstSearch(Vector2i startCell);
};
