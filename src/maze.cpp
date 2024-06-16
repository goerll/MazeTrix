#include "../include/maze.h"
#include "../include/random.h"
#include "../include/pathfinder.h"
#include <array>
#include <cmath>
#include <iostream>
#include <stack>

Maze::Maze(int x, int y) : x(x), y(y) {
    for (int cell_x = 0; cell_x < COL_NUM; cell_x++){
        for (int cell_y = 0; cell_y < LINE_NUM; cell_y++){
            matrix[cell_x][cell_y] = Cell(this, cell_x, cell_y);
        }
    }
    pathfinder = new Pathfinder(this, 0, 0);
}

void Maze::draw(){
    for (int x = 0; x < COL_NUM; x++){
        for (int y = 0; y < LINE_NUM; y++){
            if (this->matrix[x][y].active)
                this->matrix[x][y].drawSquare();
        }
    }

    pathfinder->draw();

    for (int x = 0; x < COL_NUM; x++){
        for (int y = 0; y < LINE_NUM; y++){
            if (this->matrix[x][y].active)
                this->matrix[x][y].drawWalls();
        }
    }
}

void Maze::reset() {
    for (int x = 0; x < LINE_NUM; ++x) {
        for (int y = 0; y < COL_NUM; ++y) {
            matrix[x][y] = Cell(this, x, y);
        }
    }

    pathfinder->path.clear();
}

std::array<std::array<std::vector<Cell*>, LINE_NUM>, COL_NUM> Maze::toGraph() {
    std::array<std::array<std::vector<Cell*>, LINE_NUM>, COL_NUM> graph;

    for (int y = 0; y < LINE_NUM; y++){
        for (int x = 0; x < COL_NUM; x++){
            graph[x][y] = this->matrix[x][y].getAcessibleNeighbors();

            // Print out the adjacency list generated
            std::cout << "Cell[" << x << "][" << y << "]: ";
            for (Cell* cell : graph[x][y]) {
                std::cout << "(" << cell->x << "," << cell->y << ")";
            }
            std::cout << std::endl;
        }
    }

    return graph;
}

Cell* Maze::getCell(Vector2 coord) {
    int index_x = (coord.x - this->x)/CELL_SIZE;
    int index_y = (coord.y - this->y)/CELL_SIZE;

    std::cout << index_x << ", " << index_y << std::endl;
    return &(this->matrix[index_x][index_y]);
}

void Maze::mazefyBinaryTree(){
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

            BeginDrawing();
                ClearBackground(BG_COLOR);
                this->draw();
            EndDrawing();
        }
    }
    pathfinder->update();
}

void Maze::mazefyDepthFirstSearch(Cell* cell) {
    this->reset();
    std::stack<Cell*> stack;
    cell->active = true;
    cell->times_visited++;
    stack.push(cell);

    while (!stack.empty()) {
        Cell* nextCell = cell->getRandomNeighbor(cell->getUnvisitedNeighbors());

        if (nextCell) {

            if (cell->x > nextCell->x) {
                cell->wall_left = false;
                nextCell->wall_right = false;
            }
            else if (cell->x < nextCell->x) {
                cell->wall_right = false;
                nextCell->wall_left = false;
            }
            else if (cell->y > nextCell->y) {
                cell->wall_up = false;
                nextCell->wall_down = false;
            }
            else if (cell->y < nextCell->y) {
                cell->wall_down = false;
                nextCell->wall_up = false;
            }

            cell = nextCell;
            cell->times_visited++;
            cell->active = true;
            stack.push(cell);
        }

        else {
            stack.pop();
            if (!stack.empty())
                cell = stack.top();
        }

        BeginDrawing();
            ClearBackground(BG_COLOR);
            this->draw();
        EndDrawing();

    }

    pathfinder->update();
}

void Maze::resetVisited(){
    for (int x = 0; x < COL_NUM; x++){
        for (int y = 0; y < LINE_NUM; y++){
            this->matrix[x][y].times_visited = 0;
        }
    }
}

