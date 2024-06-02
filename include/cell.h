#pragma once

#include <SFML/Graphics.hpp>
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
    bool active{ true };
    bool highlighted{ false };

    bool wall_up{ true };
    bool wall_down{ true };
    bool wall_left{ true };
    bool wall_right{ true };

    int times_visited { 0 };

    // Draw cell respecting state variables
    void draw(sf::RenderWindow* window);
    // Draw cell as if it was highlighted
    void draw_highlighted(sf::RenderWindow* window);
    // Get a neighbor from a specific direction
    Cell* getNeighbor(Direction direction);
    // Verify if a cell is acessible from current cell
    bool isAcessible(Cell* cell);
    // Get all neighbors
    std::vector<Cell*> getNeighbors();
    // Get all neighbors acessible (with no walls in between)
    std::vector<Cell*> getAcessibleNeighbors();
    std::vector<Cell*> getUnvisitedNeighbors();
    std::vector<Cell*> getAcessibleUnvisitedNeighbors();
    Cell* getRandomNeighbor(std::vector<Cell*> potential_neighbors);
    Cell* random_unvisited_neighbor();
    // Verify if a cell is a dead end (has no unvisited neighbours)
    bool is_dead_end();
};
