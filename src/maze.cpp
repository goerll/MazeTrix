#include "../include/maze.h"
#include "../include/random.h"

// Constructor
Maze::Maze() {
    for (int y = 0; y < NUM_OF_LINES; y++) {
        for (int x = 0; x < NUM_OF_LINES; x++) {
            matrix[y][x].x = x;
            matrix[y][x].y = y;
        }
    }
}

// Draw
void Maze::draw(sf::RenderWindow* window) {
    for (int y = 0; y < NUM_OF_LINES; y++) {
        for (int x = 0; x < NUM_OF_LINES; x++) {
            if (this->matrix[y][x].active) {
                this->matrix[y][x].draw_cell(window, x * CELL_SIZE, y * CELL_SIZE);
            }
        }
    }
}

// Get a cell's random unvisited neighbor
Cell* Maze::random_unvisited_neighbor(Cell* cell) {
    // Array to store neighbors
    std::vector<Cell*> neighbors;

    // Left neighbor
    if (cell->x > 0) {
        if (this->matrix[cell->y][cell->x - 1].active == false)
            neighbors.push_back(&(this->matrix[cell->y][cell->x - 1]));
    }
    // Right neighbor
    if (cell->x < NUM_OF_LINES - 1) {
        if (this->matrix[cell->y][cell->x + 1].active == false)
            neighbors.push_back(&(this->matrix[cell->y][cell->x + 1]));
    }
    // Up neighbor
    if (cell->y > 0) {
        if (this->matrix[cell->y - 1][cell->x].active == false)
            neighbors.push_back(&(this->matrix[cell->y - 1][cell->x]));
    }
    // Down neighbor
    if (cell->y < NUM_OF_LINES - 1) {
        if (this->matrix[cell->y + 1][cell->x].active == false)
            neighbors.push_back(&(this->matrix[cell->y + 1][cell->x]));
    }

    if (neighbors.empty()) {
        return nullptr;
    }

    int random_index = rand_num(0, neighbors.size() - 1);
    return neighbors[random_index];
}

// Verifies if a given cell is a dead end (has no unvisited neighbors)
bool Maze::is_dead_end(Cell* cell) {
    // Left neighbor
    if (cell->x > 0) {
        if (this->matrix[cell->y][cell->x - 1].active == false)
            return false;
    }
    // Right neighbor
    if (cell->x < NUM_OF_LINES - 1) {
        if (this->matrix[cell->y][cell->x + 1].active == false)
            return false;
    }
    // Up neighbor
    if (cell->y > 0) {
        if (this->matrix[cell->y - 1][cell->x].active == false)
            return false;
    }
    // Down neighbor
    if (cell->y < NUM_OF_LINES - 1) {
        if (this->matrix[cell->y + 1][cell->x].active == false)
            return false;
    }

    return true;
}

// Transform the matrix into a maze using the binary tree algorithm
// (also draws the matrix in the process for a cool visualization)
void Maze::mazefy_binary_tree(sf::RenderWindow* window) {
    for (int y = 0; y < NUM_OF_LINES; y++) {
        for (int x = 0; x < NUM_OF_LINES; x++) {
            this->matrix[y][x].active = true;

            int random = rand_num(0, 1);

            if (random == 1 || x == 0 || y == 0) {
                this->matrix[y][x].wall_up = false;
                if (y > 0) {
                    this->matrix[y - 1][x].wall_down = false;
                    this->matrix[y - 1][x].draw_cell(window, x * CELL_SIZE, (y - 1) * CELL_SIZE);
                }
            }

            if (random == 0 || x == 0 || y == 0) {
                this->matrix[y][x].wall_left = false;
                if (x > 0) {
                    this->matrix[y][x - 1].wall_right = false;
                    this->matrix[y][x - 1].draw_cell(window, (x - 1) * CELL_SIZE, y * CELL_SIZE);
                }
            }

            this->matrix[y][x].draw_cell(window, x * CELL_SIZE, y * CELL_SIZE);

            window->display();

            sf::sleep(sf::milliseconds(DELAY));
        }
    }
}

// Transform the matrix into a maze using the binary tree algorithm
// (also draws the matrix in the process for a cool visualization)
void Maze::mazefy_depth_first_search(sf::RenderWindow* window, Cell* cell) {
    cell->active = true;
    while (is_dead_end(cell) == false) {
        Cell* neighbor = this->random_unvisited_neighbor(cell);

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

        cell->draw_cell(window, cell->x * CELL_SIZE, cell->y * CELL_SIZE);
        neighbor->draw_cell(window, neighbor->x * CELL_SIZE, neighbor->y * CELL_SIZE);
        window->display();

        mazefy_depth_first_search(window, neighbor);
    }
}
