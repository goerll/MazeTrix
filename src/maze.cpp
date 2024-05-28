#include "../include/maze.h"
#include "../include/random.h"
#include <cmath>

Maze::Maze(int x, int y) : x(x), y(y){
    for (int cell_x = 0; cell_x < COL_NUM; cell_x++){
        for (int cell_y = 0; cell_y < LINE_NUM; cell_y++){
            this->matrix[cell_x][cell_y].x = cell_x;
            this->matrix[cell_x][cell_y].y = cell_y;
            this->matrix[cell_x][cell_y].maze = this;
        }
    }
}

void Maze::draw(sf::RenderWindow* window){
    for (int x = 0; x < COL_NUM; x++){
        for (int y = 0; y < LINE_NUM; y++){
            if (this->matrix[x][y].active)
                this->matrix[x][y].draw(window);
        }
    }
}

void Maze::reset() {
    for (int x = 0; x < LINE_NUM; ++x) {
        for (int y = 0; y < COL_NUM; ++y) {
            matrix[x][y] = Cell(this, x, y);
        }
    }
}

Cell* Maze::get_cell(float x, float y){
    float index_x = floor(x/CELL_SIZE);
    float index_y = floor(y/CELL_SIZE);

    return &(this->matrix[index_x][index_y]);
}

void Maze::mazefy_binary_tree(sf::RenderWindow* window){
    window->setFramerateLimit(120);
    for (int x = 0; x < COL_NUM; x++){
        for (int y = 0; y < LINE_NUM; y++){
            this->matrix[x][y].active = true;

            int random = rand_num(0, 1);

            if (random == 1 || x == 0 || y == 0) {
                this->matrix[x][y].wall_up = false;
                if (y > 0) {
                    this->matrix[x][y - 1].wall_down = false;
                }
            }

            if (random == 0 || x == 0 || y == 0) {
                this->matrix[x][y].wall_left = false;
                if (x > 0) {
                    this->matrix[x - 1][y].wall_right = false;
                }
            }

            window->clear(BG_COLOR);
            this->draw(window);
            window->display();
        }
    }
    window->setFramerateLimit(10);
}

void Maze::mazefy_depth_first_search(sf::RenderWindow* window, Cell* cell){
    window->setFramerateLimit(120);
    cell->active = true;

    while (!cell->is_dead_end()) {
        Cell* neighbor = cell->random_unvisited_neighbor();
        neighbor->times_visited++;

        if (cell->x > neighbor->x) {
            cell->wall_left = false;
            neighbor->wall_right = false;
        }
        else if (cell->x < neighbor->x) {
            cell->wall_right = false;
            neighbor->wall_left = false;
        }
        else if (cell->y > neighbor->y) {
            cell->wall_up = false;
            neighbor->wall_down = false;
        }
        else if (cell->y < neighbor->y) {
            cell->wall_down = false;
            neighbor->wall_up = false;
        }

        window->clear(BG_COLOR);
        cell->draw(window);
        neighbor->draw(window);
        this->draw(window);
        window->display();

        mazefy_depth_first_search(window, neighbor);
    }
    window->setFramerateLimit(10);
}

