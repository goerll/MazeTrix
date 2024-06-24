#include "../include/maze.h"
#include "../include/random.h"
#include "../include/pathfinder.h"
#include <raylib.h>
#include <stack>

Maze::Maze() : Maze(Vector2i{0, 0}) {}

Maze::Maze(Vector2i pos) : position(pos),
                           matrix(COL_NUM, std::vector<Cell>(LINE_NUM)),
                           pathfinder(new Pathfinder(this)) {

    // Initialize the matrix's cells
    for (size_t x = 0; x < matrix.size(); x++)
        for (size_t y = 0; y < matrix.at(x).size(); y++)
            matrix.at(x).at(y) = Cell({static_cast<int>(x), static_cast<int>(y)});
}

void Maze::draw(){
    // Draw a box around where the maze is
    // Draw upper bound
    DrawRectangle(position.x, position.y, COL_NUM*CELL_SIZE, WALL_SIZE, WALL_COLOR);
    // Draw lower bound
    DrawRectangle(position.x, position.y-WALL_SIZE+LINE_NUM*CELL_SIZE, COL_NUM*CELL_SIZE, WALL_SIZE, WALL_COLOR);
    // Draw left bound
    DrawRectangle(position.x, position.y, WALL_SIZE, COL_NUM*CELL_SIZE, WALL_COLOR);
    // Draw right bound
    DrawRectangle(position.x-WALL_SIZE+LINE_NUM*CELL_SIZE, position.y, WALL_SIZE, COL_NUM*CELL_SIZE, WALL_COLOR);

    // Draw all cell squares
    for (int x = 0; x < COL_NUM; x++)
        for (int y = 0; y < LINE_NUM; y++)
            if (matrix[x][y].getActive())
                matrix[x][y].drawSquare(position);

    // Draw pathfinder and it's path
    pathfinder->draw();

    // Draw all cell walls
    for (int x = 0; x < COL_NUM; x++)
        for (int y = 0; y < LINE_NUM; y++)
            if (matrix[x][y].getActive())
                matrix[x][y].drawWalls(position);
}

void Maze::reset() {
    // Reinitialize all cells
    for (size_t x = 0; x < matrix.size(); x++)
        for (size_t y = 0; y < matrix.at(x).size(); y++)
            matrix[x][y] = Cell({static_cast<int>(x), static_cast<int>(y)});

    // Update pathfinder
    pathfinder->update();
}

void Maze::copyMatrix(const Maze &maze) {
    // Copy matrix from another maze
    this->matrix = maze.matrix;
}

std::vector<std::vector<std::vector<Vector2i>>> Maze::toGraph() {
    using std::vector;

    // Adjacency list (represents maze as a graph)
    vector<vector<vector<Vector2i>>> graph(COL_NUM, vector<vector<Vector2i>>(LINE_NUM, vector<Vector2i>()));

    for (int y = 0; y < LINE_NUM; y++)
        for (int x = 0; x < COL_NUM; x++){
            // graph[x][y] stores a vector that contains all acessible neighbors of cell [x][y] from the maze
            graph[x][y] = getAccessibleNeighbors({x, y});

            // Print out the adjacency list generated (debugging)
            /*std::cout << "Cell[" << x << "][" << y << "]: ";*/
            /*for (Vector2i cell : graph[x][y])*/
            /*    std::cout << "(" << cell.x << "," << cell.y << ")";*/
            /*std::cout << std::endl;*/
        }

    return graph;
}

Cell& Maze::getCell(Vector2i cell) {
    return matrix.at(cell.x).at(cell.y);
}

Vector2i Maze::getMouseCell() {
    // Get mouse position
    Vector2 mouse_pos = GetMousePosition();

    // Cell indexes corresponding to mouse position
    int x = (mouse_pos.x - position.x) / CELL_SIZE;
    int y = (mouse_pos.y - position.y) / CELL_SIZE;

    // Verify if cell indexes are in bounds and return the cell
    if (x >= 0 && x < COL_NUM && y >= 0 && y < LINE_NUM)
        return Vector2i{x, y};

    // Else return -1,-1
    return {-1, -1};
}

bool Maze::isAccessible(Vector2i cell, Vector2i neighbor) {
    // If the neighbor is valid, either x or y will be equal to the cell's

    // If x is the same
    if (neighbor.x == cell.x) {
        // If y is less than the cell's, then the neighbor is up
        if (neighbor.y == cell.y - 1) {
            return !(getCell(cell).getWall(up));
        }
        // If y is greater than the cell's, then the neighbor is down
        else if (neighbor.y == cell.y + 1) {
            return !(getCell(cell).getWall(down));
        }
    }
    // If y is the same
    else if (neighbor.y == cell.y) {
        // If x is less than the cell's, then the neighbor is left
        if (neighbor.x == cell.x - 1) {
            return !(getCell(cell).getWall(left));
        }
        // If x is greater than the cell's, then the neighbor is right
        else if (neighbor.x == cell.x + 1) {
            return !(getCell(cell).getWall(right));
        }
    }
    // If neither the x or y are the same, then the neighbor is invalid
    return false;
}

bool Maze::isDeadEnd(Vector2i cell) {
    // If there are no unvisited neighbors, the cell is a dead end
    return getUnvisitedNeighbors(cell).empty();
}

Vector2i Maze::getNeighbor(Vector2i cell, Direction direction) {
    // If the neighbor is valid, return the neighbor
    switch (direction) {
        case up:
            // If the cell is not on the top row
            if (cell.y > 0)
                // Return the cell above
                return {cell.x, cell.y-1};
            break;
        case right:
            // If the cell is not on the rightmost column
            if (cell.x < COL_NUM-1)
                // Return the cell to the right
                return {cell.x+1, cell.y};
            break;
        case down:
            // If the cell is not on the bottom row
            if (cell.y < LINE_NUM-1)
                // Return the cell below
                return {cell.x, cell.y+1};
            break;
        case left:
            // If the cell is not on the leftmost column
            if (cell.x > 0)
                // Return the cell to the left
                return {cell.x-1, cell.y};
            break;
    }
    // Else, return -1,-1
    return {-1, -1};
}

std::vector<Vector2i> Maze::getNeighbors(Vector2i cell){
    // Neighbors vector to return
    std::vector<Vector2i> neighbors;

    // For each direction
    for (Direction dir : {up, right, down, left}) {
        // Get the neighbor in that direction
        Vector2i neighbor = getNeighbor(cell, dir);
        // If the neighbor is valid, add it to the vector
        if (neighbor != Vector2i{-1, -1})
            neighbors.push_back(neighbor);
    }
    return neighbors;
}

std::vector<Vector2i> Maze::getAccessibleNeighbors(Vector2i cell){
    // Neighbors vector to return
    std::vector<Vector2i> neighbors;

    // For each neighbor
    for (Vector2i neighbor : getNeighbors(cell)) {
        // If the neighbor is accessible, add it to the vector
        if (isAccessible(cell, neighbor))
            neighbors.push_back(neighbor);
    }

    return neighbors;
}

std::vector<Vector2i> Maze::getUnvisitedNeighbors(Vector2i cell){
    // Neighbors vector to return
    std::vector<Vector2i> neighbors;

    // For each neighbor
    for (Vector2i neighbor : getNeighbors(cell)) {
        // If the neighbor is unvisited, add it to the vector
        if (getCell(neighbor).getTimesVisited() == 0)
            neighbors.push_back(neighbor);
    }

    return neighbors;
}

std::vector<Vector2i> Maze::getAccessibleUnvisitedNeighbors(Vector2i cell){
    // Neighbors vector to return
    std::vector<Vector2i> neighbors;

    // For each neighbor
    for (Vector2i& neighbor : getNeighbors(cell))
        // If the neighbor is accessible and unvisited, add it to the vector
        if (getCell(neighbor).getTimesVisited() == 0 && isAccessible(cell, neighbor))
            neighbors.push_back(neighbor);

    return neighbors;
}

Vector2i Maze::getRandomNeighbor(std::vector<Vector2i> potentialNeighbors){
    // If there are no potential neighbors, return -1,-1
    if (potentialNeighbors.empty())
        return {-1, -1};
    // Else, return a random neighbor
    return potentialNeighbors.at(rand_num(0, potentialNeighbors.size()-1));
}

void Maze::mazefyBinaryTree(){
    // For each line
    for (int y = 0; y < COL_NUM; y++){
        // For each column
        for (int x = 0; x < LINE_NUM; x++){
            // Set the cell as active
            matrix[x][y].setActive(true);

            // Get a random number
            int random = rand_num(0, 1);

            // If the number is 1, remove the up wall
            if (random == 1 || x == 0 || y == 0) {
                matrix[x][y].setWall(up, false);
                // Also remove the down wall fom the cell above
                if (y > 0)
                    matrix[x][y-1].setWall(down, false);
            }

            // If the number is 0, remove the left wall
            if (random == 0 || x == 0 || y == 0) {
                matrix[x][y].setWall(left, false);
                // Also remove the right wall from the cell to the left
                if (x > 0)
                    matrix[x-1][y].setWall(right, false);
            }

            // Draw maze on screen
            BeginDrawing();
                ClearBackground(BG_COLOR);
                this->draw();
            EndDrawing();
        }
    }
}

void Maze::mazefyDepthFirstSearch(Vector2i cell) {
    // If the cell is not valid, return
    if (cell == Vector2i{-1, -1})
        return;

    // Reset the maze (this is to prevent mazing on top of what's already a maze)
    reset();

    // Create a stack to store cells visited
    std::stack<Vector2i> stack;

    // Set the starting cell as active and visited
    getCell(cell).setActive(true);
    getCell(cell).increaseTimesVisited();

    // Add it to the stack
    stack.push(cell);

    while (!stack.empty()) {
        // Get the next cell
        Vector2i nextCell = getRandomNeighbor(getUnvisitedNeighbors(cell));

        // If the next cell is valid
        if (nextCell != Vector2i{-1, -1}) {
            // Find out on which side the next cell is and
            // remove the wall between it and the previous cell
            if (cell.x > nextCell.x) {
                getCell(cell).setWall(left, false);
                getCell(nextCell).setWall(right, false);
            }
            else if (cell.x < nextCell.x) {
                getCell(cell).setWall(right, false);
                getCell(nextCell).setWall(left, false);
            }
            else if (cell.y > nextCell.y) {
                getCell(cell).setWall(up, false);
                getCell(nextCell).setWall(down, false);
            }
            else if (cell.y < nextCell.y) {
                getCell(cell).setWall(down, false);
                getCell(nextCell).setWall(up, false);
            }

            // Update the cell to the next cell
            cell = nextCell;
            // Mark it as viisted and active
            getCell(cell).increaseTimesVisited();
            getCell(cell).setActive(true);
            // Add it to the stack
            stack.push(cell);
        }

        // If the next cell is not valid, that means we are at a dead end
        else {
            // Pop the stack and go back to the last position
            stack.pop();
            if (!stack.empty())
                cell = stack.top();
        }

        // Draw the maze
        BeginDrawing();
            ClearBackground(BG_COLOR);
            draw();
        EndDrawing();

    }
}

void Maze::resetVisited(){
    for (auto& y : matrix)
        for (auto& x : y)
            x.resetTimesVisited();
}

// Getters
Vector2i Maze::getPosition() {
    return position;
}

std::vector<std::vector<Cell>>& Maze::getMatrix() {
    return matrix;
}

std::unique_ptr<Pathfinder>& Maze::getPathfinder() {
    return pathfinder;
}
