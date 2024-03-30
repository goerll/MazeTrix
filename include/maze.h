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
    Cell* random_unvisited_neighbor(Cell* cell);
    bool is_dead_end(Cell* cell);
    void mazefy_binary_tree(sf::RenderWindow* window);
    void mazefy_depth_first_search(sf::RenderWindow* window, Cell* cell);
};
