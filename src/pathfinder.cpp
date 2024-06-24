#include <queue>
#include "../include/pathfinder.h"
#include "../include/maze.h"
#include "../include/global.h"
#include <algorithm>
#include <iostream>

Pathfinder::Pathfinder(Maze* maze) : maze(maze), position({0,0}), path(), map(maze->toGraph()) {};

Color interpolateColor(Color a, Color b, float t) {
    // t = 0 gives color a, t = 1 gives color b, in between gives linear interpolation
    return {
        (unsigned char)(a.r + (b.r - a.r) * t),
        (unsigned char)(a.g + (b.g - a.g) * t),
        (unsigned char)(a.b + (b.b - a.b) * t),
        (unsigned char)(a.a + (b.a - a.a) * t)
    };
}

void Pathfinder::draw () {
    // Draw path
    // Set start color (start of the path gradient)
    Color start({240, 4, 245, 255});
    // Counter variable to calculate color interpolation
    int i = 0;

    for (auto& cell : path) {
        // Increase i
        i++;

        // Cell coordinates
        int x = (cell.x * CELL_SIZE) + maze->getPosition().x;
        int y = (cell.y * CELL_SIZE) + maze->getPosition().y;

        // Color interpolation
        Color color = interpolateColor(start, PATHFINDER_COLOR, i/(float)path.size());

        // Draw the cell with the interpolated color
        DrawRectangle(x + WALL_SIZE, y + WALL_SIZE, CELL_SIZE, CELL_SIZE, color);
    }

    // Draw pathfinder
    // Pathfinder coordinates
    int x = (this->position.x * CELL_SIZE) + this->maze->getPosition().x;
    int y = (this->position.y * CELL_SIZE) + this->maze->getPosition().y;
    // Draw the pathfinder square
    DrawRectangle(x + WALL_SIZE, y + WALL_SIZE, CELL_SIZE - (WALL_SIZE*2), CELL_SIZE - (WALL_SIZE*2), PATHFINDER_COLOR);
}

void Pathfinder::setPosition(Vector2i cell) {
    position = cell;
}

bool Pathfinder::isDeadEnd(){
    return maze->isDeadEnd(position);
}

Vector2i Pathfinder::getWay() {
    // Run through the map and find the first cell that has not been visited
    for (size_t i = 0; i < map[position.x][position.y].size(); i++) {
        if (maze->getCell(map[position.x][position.y][i]).getTimesVisited() == 0) {
            return map[position.x][position.y][i];
        }
    }
    // If no cell has not been visited, return {-1, -1}
    return {-1, -1};
}

void Pathfinder::depthFirstSearch(Vector2i end) {
    // If end is not valid, return
    if (end == Vector2i{-1, -1})
        return;

    // Clear path and reset visited
    path.clear();
    maze->resetVisited();
    // Add the start position to the path
    path.push_back(position);

    while (!path.empty()) {
        // If we reached end, break while
        if (position == end)
            break;

        // Get next cell
        Vector2i nextCell = getWay();

        // If the next cell is valid
        if (nextCell != Vector2i{-1, -1}) {
            // Update position
            position = nextCell;
            // Increment the cell's times visited
            maze->getCell(position).increaseTimesVisited();
            // Add the cell to the path
            path.push_back(position);
        }
        // If next cell is not valid
        else {
            // Remove the last cell from the path
            path.pop_back();
            // If the path isn't empty
            if (!path.empty())
                // Go to previous position
                position = path.back();
        }

        // Draw the maze
        BeginDrawing();
            ClearBackground(BG_COLOR);
            maze->draw();
        EndDrawing();
    }
}

void Pathfinder::breadthFirstSearch(Vector2i end) {
    // If end is not valid, return
    if (end == Vector2i{-1, -1})
        return;

    using std::vector;

    // Clear path and reset visited
    path.clear();
    maze->resetVisited();

    bool found = false;
    std::queue<Vector2i> queue;

    queue.push(position);
    path.push_back(position);
    maze->getCell(position).increaseTimesVisited();

    vector<vector<Vector2i>> previous(COL_NUM, vector<Vector2i>(LINE_NUM, {-1, -1}));

    while (!path.empty()) {
        Vector2i node = queue.front();
        path.pop_back();

        position = node;

        // Draw the maze
        BeginDrawing();
            ClearBackground(BG_COLOR);
            maze->draw();
        EndDrawing();

        // If we reached the end, break the loop
        if (node == end) {
            found = true;
            break;
        }

        vector<Vector2i> neighbors = maze->getAccessibleUnvisitedNeighbors(node);
        // Add all acessible and unvisited neighbors to the queue and path
        for (Vector2i next : neighbors) {
            queue.push(next);
            path.push_back(next);
            maze->getCell(next).increaseTimesVisited();
            previous[next.x][next.y] = node;
        }
    }

    // If we found the end, reconstruct the path
    if (found) {
        // Clear the path
        path.clear();

        // Reconstruct the path using our previous map
        for (Vector2i at = end; at != Vector2i{-1, -1}; at = previous[at.x][at.y]) {
            path.push_back(at);
        }
        // Reverse the path
        std::reverse(path.begin(), path.end());
        // Update pathfinder to end
        position = end;
    }
}

void Pathfinder::update() {
    path.clear();
    map = maze->toGraph();
}

void Pathfinder::clearPath() {
    path.clear();
}

Vector2i Pathfinder::getPosition() {
    return position;
}

std::vector<Vector2i> Pathfinder::getPath() {
    return path;
}

Vector2i Pathfinder::getPathTop() {
    if (path.empty()) {
        std::cerr << "Error: Attempted to get top of empty path." << std::endl;
        return Vector2i{-1, -1};
    }
    return path.back();
}

void Pathfinder::pathPush(Vector2i cell) {
    path.push_back(cell);
}

void Pathfinder::pathPop() {
    if (!path.empty()) {
        path.pop_back();
    } else {
        std::cerr << "Warning: Attempted to pop from empty path." << std::endl;
    }
}

bool Pathfinder::isPathEmpty() {
    return path.empty();
}

void Pathfinder::reversePath() {
    std::reverse(path.begin(), path.end());
}
