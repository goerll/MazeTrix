#include "../include/maze.h"
#include "../include/random.h"
#include "../include/pathfinder.h"
#include <array>
#include <cmath>
#include <iostream>
#include <stack>


Maze::Maze() : x(0), y(0) {
  for (int x = 0; x < COL_NUM; x++)
        for (int y = 0; y < LINE_NUM; y++)
            matrix[x][y] = Cell(x, y);
}

Maze::Maze(int x, int y) : x(x), y(y) {
    for (int x = 0; x < COL_NUM; x++)
      for (int y = 0; y < LINE_NUM; y++)
          matrix[x][y] = Cell(x, y);

    pathfinder = new Pathfinder(this);
}

Maze::Maze(Maze &maze) {
    for (int x = 0; x < COL_NUM; x++)
        for (int y = 0; y < LINE_NUM; y++)
            matrix[x][y] = maze.matrix[x][y];
}

void Maze::draw(){
    for (int x = 0; x < COL_NUM; x++)
        for (int y = 0; y < LINE_NUM; y++)
            if (matrix[x][y].active)
                matrix[x][y].drawSquare(this->x, this->y);

    pathfinder->draw();

    for (int x = 0; x < COL_NUM; x++)
        for (int y = 0; y < LINE_NUM; y++)
            if (matrix[x][y].active)
                matrix[x][y].drawWalls(this->x, this->y);


}

void Maze::reset() {
    for (int x = 0; x < LINE_NUM; ++x)
        for (int y = 0; y < COL_NUM; ++y)
            matrix[x][y] = Cell(x, y);

    pathfinder->path.clear();
}

std::array<std::array<std::vector<Cell*>, LINE_NUM>, COL_NUM> Maze::toGraph() {
    std::array<std::array<std::vector<Cell*>, LINE_NUM>, COL_NUM> graph;
    for (int y = 0; y < LINE_NUM; y++)
        for (int x = 0; x < COL_NUM; x++){
            graph[x][y] = getAcessibleNeighbors(&matrix[x][y]);

            // Print out the adjacency list generated
            std::cout << "Cell[" << x << "][" << y << "]: ";
            for (Cell* cell : graph[x][y]) {
                std::cout << "(" << cell->x << "," << cell->y << ")";
            }
            std::cout << std::endl;
        }


    return graph;
}

Cell* Maze::getCell(Vector2 coord) {
    int x = (coord.x - this->x) / CELL_SIZE;
    int y = (coord.y - this->y) / CELL_SIZE;

    if (x >= 0 && x < COL_NUM && y >= 0 && y < LINE_NUM)
        return &this->matrix[x][y];


    return nullptr;
}

bool Maze::isAcessible(Cell* cell, Cell* neighbor) {
    if (neighbor->x == cell->x) {
        if (neighbor->y == cell->y - 1) {
            return !(cell->wall_up);
        }
        else if (neighbor->y == cell->y + 1) {
            return !(cell->wall_down);
        }
    }
    else if (neighbor->y == cell->y) {
        if (neighbor->x == cell->x - 1) {
            return !(cell->wall_left);
        }
        else if (neighbor->x == cell->x + 1) {
            return !(cell->wall_right);
        }
    }
    return false;
}


bool Maze::isDeadEnd(Cell* cell) {
    return getUnvisitedNeighbors(cell).empty();
}

Cell* Maze::getNeighbor(Cell* cell, Direction direction) {
    switch (direction) {
        case up:
            if (cell->y > 0)
                return &(matrix[cell->x][cell->y-1]);
            break;
        case right:
            if (cell->x < COL_NUM-1)
                return &(matrix[cell->x+1][cell->y]);
            break;
        case down:
            if (cell->y < LINE_NUM-1)
                return &(matrix[cell->x][cell->y+1]);
            break;
        case left:
            if (cell->x > 0)
                return &(matrix[cell->x-1][cell->y]);
            break;
    }
    return nullptr;
}


std::vector<Cell*> Maze::getNeighbors(Cell* cell){
    std::vector<Cell*> neighbors;

    for (Direction dir : {up, right, down, left}) {
        Cell* neighbor = getNeighbor(cell, dir);
        if (neighbor)
            neighbors.push_back(neighbor);
    }

    return neighbors;
}

std::vector<Cell*> Maze::getAcessibleNeighbors(Cell* cell){
    std::vector<Cell*> neighbors;

    for (Cell* neighbor : getNeighbors(cell)) {
        if (isAcessible(cell, neighbor))
            neighbors.push_back(neighbor);
    }

    return neighbors;
};

std::vector<Cell*> Maze::getUnvisitedNeighbors(Cell* cell){
    std::vector<Cell*> neighbors;

    for (Cell* neighbor : getNeighbors(cell)) {
        if (neighbor->times_visited == 0)
            neighbors.push_back(neighbor);
    }

    return neighbors;
}

std::vector<Cell*> Maze::getAcessibleUnvisitedNeighbors(Cell* cell){
    std::vector<Cell*> neighbors;

    for (Cell* neighbor : getNeighbors(cell)) {
        if (neighbor->times_visited == 0 && isAcessible(cell, neighbor))
            neighbors.push_back(neighbor);
    }

    return neighbors;
}

Cell* Maze::getRandomNeighbor(std::vector<Cell*> potentialNeighbors){
    if (potentialNeighbors.empty())
        return nullptr;
    return potentialNeighbors[rand_num(0, potentialNeighbors.size()-1)];
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
        Cell* nextCell = getRandomNeighbor(getUnvisitedNeighbors(cell));

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
            draw();
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
