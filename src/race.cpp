#include "../include/race.h"
#include <raylib.h>

Race::Race() {
    mazeGrid.push_back(Maze({0, 0}));
    mazeGrid.push_back(Maze({CELL_SIZE * LINE_NUM, 0}));
}

void Race::draw(){
    for (Maze& maze : mazeGrid)
        maze.draw();
}

void Race::reset(){
    for (Maze& maze : mazeGrid)
        maze.reset();
}

Maze* Race::getMaze() {
    Vector2 coord = GetMousePosition();
    if (coord.x > WIN_SIZE_X || coord.y > WIN_SIZE_Y || coord.x < 0 || coord.y < 0)
        return nullptr;

    if (coord.x < CELL_SIZE * COL_NUM && coord.y < CELL_SIZE * LINE_NUM)
        return &mazeGrid[0];

    return &mazeGrid[1];
}

void Race::mazefyDepthFirst(){
    Maze* chosenMaze = getMaze();

    if (chosenMaze == nullptr)
        return;

    chosenMaze->mazefyDepthFirstSearch(chosenMaze->getMouseCell());

    for (Maze& maze : mazeGrid) {
        if (&maze != chosenMaze) {
            maze.copyMatrix(*chosenMaze);
        }
    }
}

void Race::mazefyBinaryTree(){
    Maze* chosenMaze = getMaze();

    if (chosenMaze == nullptr)
        return;

    chosenMaze->mazefyBinaryTree();

    for (Maze& maze : mazeGrid) {
        if (&maze != chosenMaze) {
            maze.copyMatrix(*chosenMaze);
        }
    }
}
