#include "../include/cell.h"
#include "../include/global.h"
#include <raylib.h>

const int SQUARE_SIZE = CELL_SIZE - (WALL_SIZE*2);
const int WALL_THICKNESS = WALL_SIZE*2;
const int WALL_LEN = CELL_SIZE + (WALL_SIZE*2);

Cell::Cell() : Cell({0,0}) {}

Cell::Cell(Vector2i pos) :
    position(pos),
    active(false),
    wall_up(true), wall_down(true), wall_left(true), wall_right(true),
    times_visited(0) {}

void Cell::draw(Vector2i offset){
    drawSquare(offset);
    drawWalls(offset);
}

void Cell::drawWalls(Vector2i offset) {
    // x and y coordinates for the cell
    int x = (position.x * CELL_SIZE) + offset.x;
    int y = (position.y * CELL_SIZE) + offset.y;

    // Draw each wall if variable is set to true
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

void Cell::drawSquare(Vector2i offset) {
    DrawRectangle((position.x * CELL_SIZE) + offset.x + WALL_SIZE, (position.y * CELL_SIZE) + offset.y + WALL_SIZE, SQUARE_SIZE, SQUARE_SIZE, CELL_COLOR);
}

// Getters
Vector2i Cell::getPosition() {
    return position;
}

bool Cell::getWall(Direction direction) {
    switch (direction) {
        case up:
            return wall_up;
        case right:
            return wall_right;
        case down:
            return wall_down;
        case left:
            return wall_left;
        default:
            return true;
    }
}

bool Cell::getActive() {
    return active;
}

int Cell::getTimesVisited() {
    return times_visited;
}

// Setters
void Cell::setActive(bool state) {
    active = state;
}

void Cell::setWall(Direction direction, bool state) {
    switch (direction) {
        case up:
            wall_up = state;
            break;
        case right:
            wall_right = state;
            break;
        case down:
            wall_down = state;
            break;
        case left:
            wall_left = state;
            break;
    }
}

void Cell::increaseTimesVisited() {
    times_visited++;
}

void Cell::resetTimesVisited() {
    times_visited = 0;
}
