#include "../include/pathfinder.h"
#include <queue>

Pathfinder::Pathfinder(Maze* maze) : maze(maze), map(maze->toGraph()) {
    position = &maze->matrix[0][0];
}

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

    for (Cell* cell : path) {
        i++;
        int x = (cell->x * CELL_SIZE) + this->maze->x;
        int y = (cell->y * CELL_SIZE) + this->maze->y;

        color = interpolateColor(start, PATHFINDER_COLOR, i/(float)path.size());

        DrawRectangle(x + WALL_SIZE, y + WALL_SIZE, CELL_SIZE, CELL_SIZE, color);
    }

    // Draw pathfinder
    int x = (this->position->x * CELL_SIZE) + this->maze->x;
    int y = (this->position->y * CELL_SIZE) + this->maze->y;

    DrawRectangle(x + WALL_SIZE, y + WALL_SIZE, CELL_SIZE - (WALL_SIZE*2), CELL_SIZE - (WALL_SIZE*2), PATHFINDER_COLOR);
}

void Pathfinder::setPosition(Cell* cell) {
    position = cell;
    path.clear();
}

bool Pathfinder::isDeadEnd(){
    return maze->isDeadEnd(position);
}

Cell* Pathfinder::getWay() {
    for (int i = 0; i < map[position->x][position->y].size(); i++) {
        if (map[position->x][position->y][i]->times_visited == 0) {
            return map[position->x][position->y][i];
        }
    }
    return nullptr;
}

void Pathfinder::depthFirstSearch(Cell* end) {
    path.clear();
    maze->resetVisited();
    path.push_back(position);

    while (!path.empty()) {
        if (position == end)
            break;

        Cell* nextCell = getWay();

        if (nextCell != nullptr) {
            position = nextCell;
            position->times_visited++;
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

        std::vector<Cell*> neighbors = maze->getAcessibleUnvisitedNeighbors(node);
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
