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
    int x = (position.x * CELL_SIZE) + offset.x;
    int y = (position.y * CELL_SIZE) + offset.y;

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
