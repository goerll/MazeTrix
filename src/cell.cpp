#include "../include/cell.h"
#include "../include/global.h"

sf::RectangleShape CELL_SQUARE({ CELL_SIZE, CELL_SIZE });
sf::RectangleShape BORDER_VERTICAL({ WALL_SIZE, CELL_SIZE });
sf::RectangleShape BORDER_HORIZONTAL({ CELL_SIZE + static_cast<int>(WALL_SIZE/2)*2, WALL_SIZE });


int half_wall = (static_cast<int>(WALL_SIZE/2));

void Cell::draw_cell(sf::RenderWindow* window) {
    int x = this->x * CELL_SIZE;
    int y = this->y * CELL_SIZE;

    CELL_SQUARE.setPosition(x, y);

    if (this->highlighted) {
        CELL_SQUARE.setFillColor(HIGHLIGHT_COLOR);
        BORDER_HORIZONTAL.setFillColor(BORDER_HIGHLIGHT_COLOR);
        BORDER_VERTICAL.setFillColor(BORDER_HIGHLIGHT_COLOR);
    }
    else {
        CELL_SQUARE.setFillColor(CELL_COLOR);
        BORDER_HORIZONTAL.setFillColor(BORDER_COLOR);
        BORDER_VERTICAL.setFillColor(BORDER_COLOR);
    }

    //window->draw(CELL_SQUARE);

    if (wall_up) {
        BORDER_HORIZONTAL.setPosition(x - half_wall, y - half_wall);
        window->draw(BORDER_HORIZONTAL);
    }
    if (wall_down) {
        BORDER_HORIZONTAL.setPosition(x - half_wall, y + (CELL_SIZE - half_wall));
        window->draw(BORDER_HORIZONTAL);
    }
    if (wall_left) {
        BORDER_VERTICAL.setPosition(x - half_wall, y);
        window->draw(BORDER_VERTICAL);
    }
    if (wall_right) {
        BORDER_VERTICAL.setPosition(x + (CELL_SIZE - WALL_SIZE) + half_wall, y);
        window->draw(BORDER_VERTICAL);
    }
}
