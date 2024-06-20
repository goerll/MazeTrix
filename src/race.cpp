#include "../include/race.h"
#include <raylib.h>

Race::Race() : mazeGrid(2) {
    mazeGrid[0] = std::make_unique<Maze>(Vector2i{0, 0});
    mazeGrid[1] = std::make_unique<Maze>(Vector2i{CELL_SIZE * LINE_NUM, 0});
}

void Race::draw(){
    for (auto& maze : mazeGrid)
        maze->draw();
}

void Race::reset(){
    for (auto& maze : mazeGrid)
        maze->reset();
}

Maze* Race::getMaze() {
    Vector2 coord = GetMousePosition();
    if (coord.x > WIN_SIZE_X || coord.y > WIN_SIZE_Y || coord.x < 0 || coord.y < 0)
        return nullptr;

    if (coord.x < CELL_SIZE * COL_NUM && coord.y < CELL_SIZE * LINE_NUM)
        return mazeGrid[0].get();

    return mazeGrid[1].get();
}

void Race::mazefyDepthFirst(){
    Maze* chosenMaze = getMaze();

    if (chosenMaze == nullptr)
        return;

    chosenMaze->mazefyDepthFirstSearch(chosenMaze->getMouseCell());

    for (auto& maze : mazeGrid) {
        if (maze.get() != chosenMaze) {
            maze->copyMatrix(*chosenMaze);
        }
    }
}

void Race::mazefyBinaryTree(){
    Maze* chosenMaze = getMaze();

    if (chosenMaze == nullptr)
        return;

    chosenMaze->mazefyBinaryTree();

    for (auto& maze : mazeGrid) {
        if (maze.get() != chosenMaze) {
            maze->copyMatrix(*chosenMaze);
        }
    }
}
