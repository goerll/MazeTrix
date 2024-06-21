#pragma once

#include "pathfinder.h"
#include "cell.h"
#include "global.h"
#include <memory>

class Maze {
    private:
        // Maze position on screen
        Vector2i position;
        // Matrix of cells
        std::vector<std::vector<Cell>> matrix;
        // Pathfinder
        std::unique_ptr<Pathfinder> pathfinder;

    public:

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

        // Getters
        Vector2i getPosition();
        std::vector<std::vector<Cell>>& getMatrix();
        std::unique_ptr<Pathfinder>& getPathfinder();
};
