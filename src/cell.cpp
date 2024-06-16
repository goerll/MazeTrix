#include "../include/cell.h"
#include "../include/global.h"
#include "../include/maze.h"
/*#include <SFML/Graphics/RectangleShape.hpp>*/
#include <raylib.h>

/*sf::RectangleShape CELL_SQUARE( { CELL_SIZE - (WALL_SIZE*2), CELL_SIZE - (WALL_SIZE*2) } );*/
/*sf::RectangleShape BORDER_VERTICAL( { WALL_SIZE*2, CELL_SIZE + (WALL_SIZE*2) } );*/
/*sf::RectangleShape BORDER_HORIZONTAL( { CELL_SIZE + (WALL_SIZE*2), WALL_SIZE*2 } );*/

const int SQUARE_SIZE = CELL_SIZE - (WALL_SIZE*2);
const int WALL_THICKNESS = WALL_SIZE*2;
const int WALL_LEN = CELL_SIZE + (WALL_SIZE*2);

Cell::Cell(Maze* maze, int x, int y) : maze(maze),
    x(x), y(y),
    active(false), highlighted(false),
    wall_up(true), wall_down(true), wall_left(true), wall_right(true),
    times_visited(0) {}

void Cell::draw(){
    drawSquare();
    drawWalls();
}

void Cell::drawWalls() {
    int x = (this->x * CELL_SIZE) + maze->x;
    int y = (this->y * CELL_SIZE) + maze->y;

    if (this->wall_up) {
        DrawRectangle(x - WALL_SIZE, y - WALL_SIZE, WALL_LEN, WALL_THICKNESS, WALL_COLOR);
    }
    if (this->wall_right) {
        DrawRectangle(x + CELL_SIZE - WALL_SIZE, y - WALL_SIZE, WALL_THICKNESS, WALL_LEN, WALL_COLOR);
    }
    if (this->wall_down) {
        DrawRectangle(x - WALL_SIZE, y + CELL_SIZE - WALL_SIZE, WALL_LEN, WALL_THICKNESS, WALL_COLOR);
    }
    if (this->wall_left) {
        DrawRectangle(x - WALL_SIZE, y - WALL_SIZE, WALL_THICKNESS, WALL_LEN, WALL_COLOR);
    }
}

void Cell::drawSquare() {
    int x = (this->x * CELL_SIZE) + maze->x;
    int y = (this->y * CELL_SIZE) + maze->y;
    DrawRectangle(x + WALL_SIZE, y + WALL_SIZE, SQUARE_SIZE, SQUARE_SIZE, CELL_COLOR);
}

bool Cell::isAcessible(Cell* neighbor) {
    if (neighbor->x == this->x) {
        if (neighbor->y == this->y - 1) {
            return !(this->wall_up);
        }
        else if (neighbor->y == this->y + 1) {
            return !(this->wall_down);
        }
    }
    else if (neighbor->y == this->y) {
        if (neighbor->x == this->x - 1) {
            return !(this->wall_left);
        }
        else if (neighbor->x == this->x + 1) {
            return !(this->wall_right);
        }
    }
    return false;
}

bool Cell::isDeadEnd() {
    return this->getUnvisitedNeighbors().empty();
}

Cell* Cell::getNeighbor(Direction direction) {
    switch (direction) {
    case up:
        if (y == 0) {
            return nullptr;
        }
        else {
            return &(maze->matrix[x][y - 1]);
        }
    case right:
        if (x == COL_NUM - 1) {
            return nullptr;
        }
        else {
            return &(maze->matrix[x + 1][y]);
        }
    case down:
        if (y == LINE_NUM - 1) {
            return nullptr;
        }
        else {
            return &(maze->matrix[x][y + 1]);
        }
    case left:
        if (x <= 0) {
            return nullptr;
        }
        else {
            return &(maze->matrix[x - 1][y]);
        }
    default:
        return nullptr;
    }
}

std::vector<Cell*> Cell::getNeighbors(){
    std::vector<Cell*> neighbors;

    for (Direction dir : {up, right, down, left}) {
        Cell* neighbor = this->getNeighbor(dir);
        if (neighbor)
            neighbors.push_back(neighbor);
    }

    return neighbors;
}

std::vector<Cell*> Cell::getAcessibleNeighbors(){
    std::vector<Cell*> neighbors;

    for (Cell* neighbor : this->getNeighbors()) {
        if (this->isAcessible(neighbor))
            neighbors.push_back(neighbor);
    }

    return neighbors;
}

std::vector<Cell*> Cell::getUnvisitedNeighbors(){
    std::vector<Cell*> neighbors;

    for (Cell* neighbor : this->getNeighbors()) {
        if (neighbor->times_visited == 0)
            neighbors.push_back(neighbor);
    }

    return neighbors;
}

std::vector<Cell*> Cell::getAcessibleUnvisitedNeighbors(){
    std::vector<Cell*> neighbors;

    for (Cell* neighbor : this->getNeighbors()) {
        if (neighbor->times_visited == 0 && this->isAcessible(neighbor))
            neighbors.push_back(neighbor);
    }

    return neighbors;
}

Cell* Cell::getRandomNeighbor(std::vector<Cell*> potentialNeighbors){
    if (potentialNeighbors.empty())
        return nullptr;
    int index = rand() % potentialNeighbors.size();
    return (potentialNeighbors[index]);
}
