#include "../include/pathfinder.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <stack>

/*sf::RectangleShape SQUARE( { CELL_SIZE - (WALL_SIZE*2), CELL_SIZE - (WALL_SIZE*2) } );*/
sf::RectangleShape SQUARE( { CELL_SIZE - (WALL_SIZE*2), CELL_SIZE - (WALL_SIZE*2) } );

Pathfinder::Pathfinder(Maze* maze, int x = 0, int y = 0) : maze(maze), map(maze->toGraph()) {
    position = &maze->matrix[x][y];
    maze->pathfinders.push_back(this);
}

void Pathfinder::draw (sf::RenderWindow* window) {
    drawPath(window);

    int x = (this->position->x * CELL_SIZE) + this->maze->x;
    int y = (this->position->y * CELL_SIZE) + this->maze->y;

    SQUARE.setFillColor(PATHFINDER_COLOR);
    SQUARE.setPosition(x + WALL_SIZE, y+WALL_SIZE);
    window->draw(SQUARE);
}

void Pathfinder::drawPath(sf::RenderWindow* window) {
    for (Cell* cell : path) {
        int x = (cell->x * CELL_SIZE) + this->maze->x;
        int y = (cell->y * CELL_SIZE) + this->maze->y;

        SQUARE.setFillColor(sf::Color::Black);
        SQUARE.setPosition(x + WALL_SIZE, y+WALL_SIZE);
        window->draw(SQUARE);
    }
}

void Pathfinder::setPosition(Cell* cell) {
    position = cell;
    path.clear();
}

bool Pathfinder::isDeadEnd(){
    if (position->is_dead_end())
        return true;
    return false;
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

    std::cout << "Starting while" << std::endl;
    while (!stack.empty()) {
        if (position == end)
            break;

        Cell* nextCell = getWay();

        if (nextCell != nullptr) {
            position = nextCell;
            position->times_visited++;
            stack.push(position);
        }
        else {
            stack.pop();
            if (!stack.empty())
                position = stack.top();
        }
    }

    if (position == end) {
        while (!stack.empty()) {
            path.push_back(stack.top());
            std::cout << stack.top()->x << " " << stack.top()->y << std::endl;
            stack.pop();
        }
        std::reverse(path.begin(), path.end());
        return true;
    }
    return false;
}

void Pathfinder::update() {
    path.clear();
    map = maze->toGraph();
}


void Pathfinder::depthFirstSearch() {
    depthFirstSearch(maze->getFinish());
}
