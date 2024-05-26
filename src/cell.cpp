#include "../include/cell.h"
#include "../include/global.h"
#include "../include/maze.h"
#include "../include/random.h"
#include <SFML/Graphics/RectangleShape.hpp>

sf::RectangleShape CELL_SQUARE( { CELL_SIZE - (WALL_SIZE*2), CELL_SIZE - (WALL_SIZE*2) } );
sf::RectangleShape BORDER_VERTICAL( { WALL_SIZE*2, CELL_SIZE + (WALL_SIZE*2) } );
sf::RectangleShape BORDER_HORIZONTAL( { CELL_SIZE + (WALL_SIZE*2), WALL_SIZE*2 } );

Cell::Cell() : maze(nullptr), x(0), y(0), active(false), highlighted(false),
    wall_up(true), wall_down(true), wall_left(true), wall_right(true),
    times_visited(0) {}

Cell::Cell(Maze* maze, int x, int y) : maze(maze), x(x), y(y), active(false),
    highlighted(false), wall_up(true), wall_down(true), wall_left(true),
    wall_right(true), times_visited(0) {}

void Cell::draw(sf::RenderWindow* window){
    int x = (this->x * CELL_SIZE) + this->maze->x;
    int y = (this->y * CELL_SIZE) + this->maze->y;

    if (!this->highlighted) {
        CELL_SQUARE.setFillColor(CELL_COLOR);
        BORDER_VERTICAL.setFillColor(BORDER_COLOR);
        BORDER_HORIZONTAL.setFillColor(BORDER_COLOR);
    }
    else {
        CELL_SQUARE.setFillColor(HIGHLIGHT_COLOR);
        BORDER_VERTICAL.setFillColor(BORDER_HIGHLIGHT_COLOR);
        BORDER_HORIZONTAL.setFillColor(BORDER_HIGHLIGHT_COLOR);
    }

    CELL_SQUARE.setPosition(x + WALL_SIZE, y+WALL_SIZE);
    window->draw(CELL_SQUARE);

    if (this->wall_up) {
        BORDER_HORIZONTAL.setPosition(x - WALL_SIZE, y - WALL_SIZE);
        window->draw(BORDER_HORIZONTAL);
    }
    if (this->wall_right) {
        BORDER_VERTICAL.setPosition(x + CELL_SIZE - WALL_SIZE, y - WALL_SIZE);
        window->draw(BORDER_VERTICAL);
    }
    if (this->wall_down) {
        BORDER_HORIZONTAL.setPosition(x - WALL_SIZE, y + CELL_SIZE - WALL_SIZE );
        window->draw(BORDER_HORIZONTAL);
    }
    if (this->wall_left) {
        BORDER_VERTICAL.setPosition(x - WALL_SIZE, y - WALL_SIZE);
        window->draw(BORDER_VERTICAL);
    }
}

Cell* Cell::get_neighbor(Direction direction) {
    switch (direction) {
    case up:
        if (this->y == 0) {
            return nullptr;
        }
        else {
            return &(this->maze->matrix[this->x][this->y - 1]);
        }
    case right:
        if (this->x == COL_NUM - 1) {
            return nullptr;
        }
        else {
            return &(this->maze->matrix[this->x + 1][this->y]);
        }
    case down:
        if (this->y == LINE_NUM - 1) {
            return nullptr;
        }
        else {
            return &(this->maze->matrix[this->x][this->y + 1]);
        }
    case left:
        if (this->x == 0) {
            return nullptr;
        }
        else {
            return &(this->maze->matrix[this->x - 1][this->y]);
        }
    default:
        return this;
    }
}

Cell* Cell::random_unvisited_neighbor() {
    // Array to store neighbors
    std::vector<Cell*> neighbors;

    // Left neighbore 
    if (this->x > 0) {
        if (this->maze->matrix[this->x - 1][this->y].times_visited == false)
            neighbors.push_back(&(this->maze->matrix[this->x - 1][this->y]));
    }
    // Right neighbor
    if (this->x < LINE_NUM - 1) {
        if (this->maze->matrix[this->x + 1][this->y].times_visited == false)
            neighbors.push_back(&(this->maze->matrix[this->x + 1][this->y]));
    }
    // Up neighbor
    if (this->y > 0) {
        if (this->maze->matrix[this->x][this->y - 1].times_visited == false)
            neighbors.push_back(&(this->maze->matrix[this->x][this->y - 1]));
    }
    // Down neighbor
    if (this->y < LINE_NUM - 1) {
        if (this->maze->matrix[this->x][this->y + 1].times_visited == false)
            neighbors.push_back(&(this->maze->matrix[this->x][this->y + 1]));
    }

    if (neighbors.empty()) {
        return nullptr;
    }

    int random_index = rand_num(0, neighbors.size() - 1);
    return neighbors[random_index];
}

bool Cell::is_dead_end() {
    // Left neighbor
    if (this->x > 0) {
        if (this->maze->matrix[this->x - 1][this->y].times_visited == false)
            return false;
    }
    // Right neighbor
    if (this->x < LINE_NUM - 1) {
        if (this->maze->matrix[this->x + 1][this->y].times_visited == false)
            return false;
    }
    // Up neighbor
    if (this->y > 0) {
        if (this->maze->matrix[this->x][this->y - 1].times_visited == false)
            return false;
    }
    // Down neighbor
    if (this->y < LINE_NUM - 1) {
        if (this->maze->matrix[this->x][this->y + 1].times_visited == false)
            return false;
    }

    return true;
}
