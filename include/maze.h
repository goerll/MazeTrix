#pragma once
#include "cell.h"
#include "global.h"
#include <SFML/Graphics.hpp>
#include <array>

class Maze {
public:
    std::array<std::array<Cell, NUM_OF_LINES>, NUM_OF_LINES> matrix;

    Maze();

    // Draw the maze on the screen
    void draw(sf::RenderWindow* window);
    // Reset the matrix's cells to their default state
    void reset();
    // Get a neighbour from a cell
    Cell* get_neighbor(Cell*, Direction direction);
    // Get a random unvisited neighbour from a cell
    Cell* random_unvisited_neighbor(Cell* cell);
    // Verify if a cell is a dead end (has no unvisited neighbours)
    bool is_dead_end(Cell* cell);
    // Get the cell that is at a specific screen coordinate
    Cell* get_cell(float x, float y);
    // Turn the matrix into a maze using the binary tree algorithm
    void mazefy_binary_tree(sf::RenderWindow* window);
    // Turn the matrix into a maze using the depth first serach algorithm
    void mazefy_depth_first_search(sf::RenderWindow* window, Cell* cell);

};
