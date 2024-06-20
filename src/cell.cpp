#include "../include/cell.h"
#include "../include/global.h"
#include <raylib.h>

const int SQUARE_SIZE = CELL_SIZE - (WALL_SIZE*2);
const int WALL_THICKNESS = WALL_SIZE*2;
const int WALL_LEN = CELL_SIZE + (WALL_SIZE*2);

Cell::Cell(int x, int y) :
    x(x), y(y),
    active(false),
    wall_up(true), wall_down(true), wall_left(true), wall_right(true),
    times_visited(0) {}

void Cell::draw(int offsetX, int offsetY){
    drawSquare(offsetX, offsetY);
    drawWalls(offsetX, offsetY);
}

void Cell::drawWalls(int offsetX, int offsetY) {
    int x = (this->x * CELL_SIZE) + offsetX;
    int y = (this->y * CELL_SIZE) + offsetY;

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

void Cell::drawSquare(int offsetX, int offsetY) {
    DrawRectangle((x * CELL_SIZE) + offsetX + WALL_SIZE, (y * CELL_SIZE) + offsetY + WALL_SIZE, SQUARE_SIZE, SQUARE_SIZE, CELL_COLOR);
}

