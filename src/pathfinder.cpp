#include "../include/pathfinder.h"
/*#include <iostream>*/
#include <stack>
#include <queue>

/*sf::RectangleShape PATHFINDER_SQUARE( { CELL_SIZE - (WALL_SIZE*2), CELL_SIZE - (WALL_SIZE*2) } );*/
/*const int shrink = 10;*/
/*sf::RectangleShape PATH_SQUARE( { CELL_SIZE - (WALL_SIZE*2) - shrink*2, CELL_SIZE - (WALL_SIZE*2) - shrink*2 } );*/
/*sf::RectangleShape PATH_SQUARE( { CELL_SIZE, CELL_SIZE } );*/

Pathfinder::Pathfinder(Maze* maze, int x = 0, int y = 0) : maze(maze), map(maze->toGraph()) {
    position = &maze->matrix[x][y];
    maze->pathfinder = this;
}

void Pathfinder::draw () {
    drawPath();

    int x = (this->position->x * CELL_SIZE) + this->maze->x;
    int y = (this->position->y * CELL_SIZE) + this->maze->y;

    DrawRectangle(x + WALL_SIZE, y + WALL_SIZE, CELL_SIZE - (WALL_SIZE*2), CELL_SIZE - (WALL_SIZE*2), PATHFINDER_COLOR);
}

Color interpolateColor(Color a, Color b, float t) {
    Color color;
    color.r = (a.r + (b.r - a.r) * t);
    color.g = (a.g + (b.g - a.g) * t);
    color.b = (a.b + (b.b - a.b) * t);
    return color;
};

void Pathfinder::drawPath() {
    Color color;
    Color start = MAGENTA;

    int i = 0;

    for (Cell* cell : path) {
        i++;
        int x = (cell->x * CELL_SIZE) + this->maze->x;
        int y = (cell->y * CELL_SIZE) + this->maze->y;

        color = interpolateColor(start, PATHFINDER_COLOR, (float)i/(float)path.size());

        DrawRectangle(x + WALL_SIZE, y + WALL_SIZE, CELL_SIZE, CELL_SIZE, color);
    }
}

void Pathfinder::setPosition(Cell* cell) {
    position = cell;
    path.clear();
}

bool Pathfinder::isDeadEnd(){
    return position->isDeadEnd();
}

Cell* Pathfinder::getWay() {
    for (int i = 0; i < map[position->x][position->y].size(); i++) {
        if (map[position->x][position->y][i]->times_visited == 0) {
            return map[position->x][position->y][i];
        }
    }
    return nullptr;
}

bool Pathfinder::depthFirstSearch(Cell* end) {
    path.clear();
    maze->resetVisited();
    std::stack<Cell*> stack;
    stack.push(position);
    path.push_back(position);

    while (!stack.empty()) {
        if (position == end)
            break;

        Cell* nextCell = getWay();

        if (nextCell != nullptr) {
            position = nextCell;
            position->times_visited++;
            stack.push(position);
            path.push_back(position);
        }
        else {
            stack.pop();
            path.pop_back();
            if (!stack.empty())
                position = stack.top();
        }

        BeginDrawing();
            ClearBackground(BG_COLOR);
            maze->draw();
        EndDrawing();
    }

    if (position == end) {
        /*while (!stack.empty()) {*/
        /*    path.push_back(stack.top());*/
        /*    stack.pop();*/
        /*}*/
        /*std::reverse(path.begin(), path.end());*/
        return true;
    }
    return false;
}

void Pathfinder::breadthFirstSearch(Cell* end) {
    path.clear();
    maze->resetVisited();
    bool found = false;
    std::queue<Cell*> queue;
    queue.push(position);
    path.push_back(position);
    position->times_visited++;

    std::array<std::array<Cell*, LINE_NUM>, COL_NUM> previous;
    for (int i = 0; i < LINE_NUM; ++i) {
        for (int j = 0; j < COL_NUM; ++j) {
            previous[i][j] = nullptr;
        }
    }

    while (!queue.empty()) {
        Cell* node = queue.front();
        queue.pop();

        position = node;
        BeginDrawing();
            ClearBackground(BG_COLOR);
            maze->draw();
        EndDrawing();

        if (node == end) {
            found = true;
            break;
        }

        std::vector<Cell*> neighbors = node->getAcessibleUnvisitedNeighbors();
        for (Cell* next : neighbors) {
            queue.push(next);
            path.push_back(next);
            next->times_visited++;
            previous[next->x][next->y] = node;
        }
    }

    if (found) {
        path.clear();
        for (Cell* at = end; at != nullptr; at = previous[at->x][at->y]) {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());
        position = end;
    }
}

void Pathfinder::update() {
    path.clear();
    map = maze->toGraph();
}
