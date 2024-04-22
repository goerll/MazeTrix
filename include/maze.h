#pragma once
#include "cell.h"
#include "global.h"
#include <SFML/Graphics.hpp>
#include <array>

class Maze {
public:
    std::array<std::array<Cell, NUM_OF_LINES>, NUM_OF_LINES> matrix;

    Maze();
    void draw(sf::RenderWindow* window);
    void clear();
    Cell* get_neighbor(Cell*, char direction);
    Cell* random_unvisited_neighbor(Cell* cell);
    bool is_dead_end(Cell* cell);
    Cell* get_cell(float x, float y);
    void mazefy_binary_tree(sf::RenderWindow* window);
    void mazefy_depth_first_search(sf::RenderWindow* window, Cell* cell);
};
