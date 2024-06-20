#include "../include/race.h"
#include <SFML/System/Vector2.hpp>

Race::Race() {
    this->mazeGrid[0] = Maze(0, 0);
    this->mazeGrid[1] = Maze(CELL_SIZE * LINE_NUM, 0);
}

void Race::draw(){
    for (Maze maze : mazeGrid) {
        maze.draw();
    }
}

void Race::reset(){
    for (Maze maze : mazeGrid) {
        maze.reset();
    }
}

Maze* Race::getMaze(Vector2 coord) {
    if (coord.x < CELL_SIZE * COL_NUM) {
        return &mazeGrid[0];
    }
    return &mazeGrid[1];
}

void Race::mazefyDepthFirst(Vector2 coord){
    Maze* chosenMaze = getMaze(coord);
    chosenMaze->mazefyDepthFirstSearch(chosenMaze->getCell(coord));
    for (Maze maze : mazeGrid) {
        if (&maze != chosenMaze) {
            maze = Maze(*chosenMaze);
        }
    }
}

void Race::mazefyBinaryTree(Vector2 coord){
    getMaze(coord)->mazefyBinaryTree();

    /*for (Maze maze : mazeGrid) {*/
    /*    maze.matrix = cell_at_mouse->maze->matrix;*/
    /*}*/
}
