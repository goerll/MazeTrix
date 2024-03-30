#include "../include/cell.h"
#include "../include/global.h"

sf::RectangleShape CELL_SQUARE({ CELL_SIZE - (2 * WALL_SIZE), CELL_SIZE - (2 * WALL_SIZE) });
sf::RectangleShape BORDER_VERTICAL({ WALL_SIZE, CELL_SIZE });
sf::RectangleShape BORDER_HORIZONTAL({ CELL_SIZE + (2 * WALL_SIZE), WALL_SIZE });

void Cell::draw_cell(sf::RenderWindow* window, int x, int y) {
    CELL_SQUARE.setPosition(x + WALL_SIZE, y + WALL_SIZE);
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

    window->draw(CELL_SQUARE);

    if (wall_up) {
        BORDER_HORIZONTAL.setPosition(x - WALL_SIZE, y);
        window->draw(BORDER_HORIZONTAL);
    }
    if (wall_down) {
        BORDER_HORIZONTAL.setPosition(x - WALL_SIZE, y + (CELL_SIZE - WALL_SIZE));
        window->draw(BORDER_HORIZONTAL);
    }
    if (wall_left) {
        BORDER_VERTICAL.setPosition(x, y);
        window->draw(BORDER_VERTICAL);
    }
    if (wall_right) {
        BORDER_VERTICAL.setPosition(x + (CELL_SIZE - WALL_SIZE), y);
        window->draw(BORDER_VERTICAL);
    }
}
