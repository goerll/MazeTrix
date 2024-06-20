#include "../include/maze.h"
#include "../include/random.h"
#include "../include/pathfinder.h"
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <raylib.h>
#include <stack>
#include <cassert>

Maze::Maze() : Maze(Vector2i{0, 0}) {}

Maze::Maze(Vector2i pos) : position(pos),
                           matrix(COL_NUM, std::vector<Cell>(LINE_NUM)),
                           pathfinder(std::make_unique<Pathfinder>(this)) {
    for (size_t x = 0; x < matrix.size(); x++)
    for (size_t y = 0; y < matrix.at(x).size(); y++)
            matrix.at(x).at(y).position = {static_cast<int>(x), static_cast<int>(y)};
}

void Maze::draw(){
    for (int x = 0; x < COL_NUM; x++)
        for (int y = 0; y < LINE_NUM; y++)
            if (matrix[x][y].active)
                matrix[x][y].drawSquare(position);

    pathfinder->draw();

    for (int x = 0; x < COL_NUM; x++)
        for (int y = 0; y < LINE_NUM; y++)
            if (matrix[x][y].active)
                matrix[x][y].drawWalls(position);
}

void Maze::reset() {
  for (size_t x = 0; x < matrix.size(); x++)
  for (size_t y = 0; y < matrix.at(x).size(); y++)
            matrix[x][y] = Cell({static_cast<int>(x), static_cast<int>(y)});

    pathfinder->path.clear();
}

void Maze::copyMatrix(const Maze &maze) {
    // std::memcpy(&this->matrix, &maze.matrix, sizeof(matrix));
    this->matrix = maze.matrix;
}

std::vector<std::vector<std::vector<Vector2i>>> Maze::toGraph() {
    using std::vector;

    vector<vector<vector<Vector2i>>> graph(COL_NUM, vector<vector<Vector2i>>(LINE_NUM, vector<Vector2i>()));

    for (int y = 0; y < LINE_NUM; y++)
        for (int x = 0; x < COL_NUM; x++){
            graph[x][y] = getAccessibleNeighbors({x, y});

            // Print out the adjacency list generated
            std::cout << "Cell[" << x << "][" << y << "]: ";
            for (Vector2i cell : graph[x][y])
                std::cout << "(" << cell.x << "," << cell.y << ")";

            std::cout << std::endl;
        }

    return graph;
}

Cell& Maze::getCell(Vector2i cell) {
    return matrix.at(cell.x).at(cell.y);
}

Vector2i Maze::getMouseCell() {
    Vector2 mouse_pos = GetMousePosition();
    int x = (mouse_pos.x - position.x) / CELL_SIZE;
    int y = (mouse_pos.y - position.y) / CELL_SIZE;

    if (x >= 0 && x < COL_NUM && y >= 0 && y < LINE_NUM)
        return Vector2i{x, y};

    return {-1, -1};
}

bool Maze::isAccessible(Vector2i cell, Vector2i neighbor) {
    Vector2i notgood = {-1, -1};
    assert(cell != neighbor);
    assert(cell != notgood);
    assert(neighbor != notgood);
    assert(!(abs(neighbor.x - cell.x) > 1 || abs(neighbor.x - cell.x) > 1));
    assert(!(neighbor.x < 0 || neighbor.x > COL_NUM-1));
    assert(!(neighbor.y < 0 || neighbor.x > LINE_NUM-1));

    Cell& c = getCell(cell);
    bool w_l = c.wall_left;
    bool w_r = c.wall_right;
    bool w_u = c.wall_up;
    bool w_d = c.wall_down;

    if (neighbor.x == cell.x) {
        if (neighbor.y < cell.y && !w_u)
            return true;
        if (neighbor.y > cell.y && !w_d)
            return true;
    }

    if (neighbor.y == cell.y) {
        if (neighbor.x < cell.x && !w_l)
            return true;
        if (neighbor.x > cell.x && !w_r)
            return true;
    }

    return false;
}

// bool Maze::isAccessible(Vector2i cell, Vector2i neighbor) {
//     if (neighbor.x == cell.x) {
//         if (neighbor.y == cell.y - 1) {
//             return !(getCell(cell).wall_up);
//         }
//         else if (neighbor.y == cell.y + 1) {
//             return !(getCell(cell).wall_down);
//         }
//     }
//     else if (neighbor.y == cell.y) {
//         if (neighbor.x == cell.x - 1) {
//             return !(getCell(cell).wall_left);
//         }
//         else if (neighbor.x == cell.x + 1) {
//             return !(getCell(cell).wall_right);
//         }
//     }
//     return false;
// }

bool Maze::isDeadEnd(Vector2i cell) {
    return getUnvisitedNeighbors(cell).empty();
}

Vector2i Maze::getNeighbor(Vector2i cell, Direction direction) {
    switch (direction) {
        case up:
            if (cell.y > 0)
                return {cell.x, cell.y-1};
            break;
        case right:
            if (cell.x < COL_NUM-1)
                return {cell.x+1, cell.y};
            break;
        case down:
            if (cell.y < LINE_NUM-1)
                return {cell.x, cell.y+1};
            break;
        case left:
            if (cell.x > 0)
                return {cell.x-1, cell.y};
            break;
    }
    return {-1, -1};
}

std::vector<Vector2i> Maze::getNeighbors(Vector2i cell){
    std::vector<Vector2i> neighbors;

    for (Direction dir : {up, right, down, left}) {
        Vector2i neighbor = getNeighbor(cell, dir);
        if (neighbor != Vector2i{-1, -1})
            neighbors.push_back(neighbor);
    }
    return neighbors;
}

std::vector<Vector2i> Maze::getAccessibleNeighbors(Vector2i cell){
    std::vector<Vector2i> neighbors;

    for (Vector2i neighbor : getNeighbors(cell)) {
        if (isAccessible(cell, neighbor))
            neighbors.push_back(neighbor);
    }

    return neighbors;
}

std::vector<Vector2i> Maze::getUnvisitedNeighbors(Vector2i cell){
    std::vector<Vector2i> neighbors;

    for (Vector2i neighbor : getNeighbors(cell)) {
        if (getCell(neighbor).times_visited == 0)
            neighbors.push_back(neighbor);
    }

    return neighbors;
}

std::vector<Vector2i> Maze::getAccessibleUnvisitedNeighbors(Vector2i cell){
    std::vector<Vector2i> neighbors;

    for (Vector2i& neighbor : getNeighbors(cell))
        if (getCell(neighbor).times_visited == 0 && isAccessible(cell, neighbor))
            neighbors.push_back(neighbor);

    return neighbors;
}

Vector2i Maze::getRandomNeighbor(std::vector<Vector2i> potentialNeighbors){
    if (potentialNeighbors.empty())
        return {-1, -1};
    return potentialNeighbors.at(rand_num(0, potentialNeighbors.size()-1));
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



void Maze::mazefyDepthFirstSearch(Vector2i cell) {
    if (cell == Vector2i{-1, -1})
        return;

    reset();
    std::stack<Vector2i> stack;
    getCell(cell).active = true;
    getCell(cell).times_visited++;
    stack.push(cell);

    while (!stack.empty()) {
        Vector2i nextCell = getRandomNeighbor(getUnvisitedNeighbors(cell));

        if (nextCell != Vector2i{-1, -1}) {
            if (cell.x > nextCell.x) {
                getCell(cell).wall_left = false;
                getCell(nextCell).wall_right = false;
            }
            else if (cell.x < nextCell.x) {
                getCell(cell).wall_right = false;
                getCell(nextCell).wall_left = false;
            }
            else if (cell.y > nextCell.y) {
                getCell(cell).wall_up = false;
                getCell(nextCell).wall_down = false;
            }
            else if (cell.y < nextCell.y) {
                getCell(cell).wall_down = false;
                getCell(nextCell).wall_up = false;
            }

            cell = nextCell;
            getCell(cell).times_visited++;
            getCell(cell).active = true;
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
    for (auto& y : matrix)
        for (auto& x : y)
            x.times_visited = 0;
}
