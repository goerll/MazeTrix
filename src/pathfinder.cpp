#include <queue>
#include "../include/pathfinder.h"
#include "../include/maze.h"
#include "../include/global.h"

Pathfinder::Pathfinder(Maze* maze) : position({0,0}), maze(maze), map(maze->toGraph()) {};

Color interpolateColor(Color a, Color b, float t) {
    return {
        (unsigned char)(a.r + (b.r - a.r) * t),
        (unsigned char)(a.g + (b.g - a.g) * t),
        (unsigned char)(a.b + (b.b - a.b) * t),
        (unsigned char)(a.a + (b.a - a.a) * t)
    };
}

void Pathfinder::draw () {
    // Draw path
    Color color;
    Color start = MAGENTA;

    int i = 0;

    for (Vector2i cell : path) {
        i++;
        int x = (cell.x * CELL_SIZE) + this->maze->position.x;
        int y = (cell.y * CELL_SIZE) + this->maze->position.y;

        color = interpolateColor(start, PATHFINDER_COLOR, i/(float)path.size());

        DrawRectangle(x + WALL_SIZE, y + WALL_SIZE, CELL_SIZE, CELL_SIZE, color);
    }

    // Draw pathfinder
    int x = (this->position.x * CELL_SIZE) + this->maze->position.x;
    int y = (this->position.y * CELL_SIZE) + this->maze->position.y;

    DrawRectangle(x + WALL_SIZE, y + WALL_SIZE, CELL_SIZE - (WALL_SIZE*2), CELL_SIZE - (WALL_SIZE*2), PATHFINDER_COLOR);
}

void Pathfinder::setPosition(Vector2i cell) {
    position = cell;
    path.clear();
}

bool Pathfinder::isDeadEnd(){
    return maze->isDeadEnd(position);
}

Vector2i Pathfinder::getWay() {
    if (isDeadEnd()) {
        return {-1, -1};
    }

    for (int i = 0; i < map[position.x][position.y].size(); i++) {
        if (maze->getCell(map[position.x][position.y][i]).times_visited == 0) {
            return map[position.x][position.y][i];
        }
    }
    return {-1, -1};
}

void Pathfinder::depthFirstSearch(Vector2i end) {
    if (end == Vector2i{-1, -1})
        return;
    path.clear();
    maze->resetVisited();
    path.push_back(position);

    while (!path.empty()) {
        if (position == end)
            break;

        Vector2i nextCell = getWay();

        if (nextCell != Vector2i{-1, -1}) {
            position = nextCell;
            maze->getCell(position).times_visited++;
            // position->times_visited++;
            path.push_back(position);
        }
        else {
            path.pop_back();
            if (!path.empty())
                position = path.back();
        }

        BeginDrawing();
            ClearBackground(BG_COLOR);
            maze->draw();
        EndDrawing();
    }
}

void Pathfinder::breadthFirstSearch(Vector2i end) {
    if (end == Vector2i{-1, -1})
        return;

    using std::vector;

    path.clear();
    maze->resetVisited();
    bool found = false;
    std::queue<Vector2i> queue;

    queue.push(position);
    path.push_back(position);
    maze->getCell(position).times_visited++;

    vector<vector<Vector2i>> previous(COL_NUM, vector<Vector2i>(LINE_NUM, {-1, -1}));

    while (!queue.empty()) {
        Vector2i node = queue.front();
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

        vector<Vector2i> neighbors = maze->getAcessibleUnvisitedNeighbors(node);
        for (Vector2i next : neighbors) {
            queue.push(next);
            path.push_back(next);
            maze->getCell(next).times_visited++;
            previous[next.x][next.y] = node;
        }
    }

    if (found) {
        path.clear();
        for (Vector2i at = end; at != Vector2i{-1, -1}; at = previous[at.x][at.y]) {
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
