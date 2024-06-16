#include "../include/race.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>

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

Cell* Race::getCell(Vector2 coord){
    if (coord.x < (CELL_SIZE * LINE_NUM)) {
        return mazeGrid[0].getCell(coord);
    }
    else {
        return mazeGrid[1].getCell(coord);
    }
}

Maze* Race::getMaze(Vector2 coord) {
    Maze* maze;
    if (coord.x < (CELL_SIZE * LINE_NUM)) {
        return &mazeGrid[0];
    }
    else {
        return &mazeGrid[1];
    }
}

void Race::mazefyDepthFirst(Vector2 coord){
    Maze* chosenMaze = getMaze(coord);
    chosenMaze->mazefyDepthFirstSearch(chosenMaze->getCell(coord));
    for (Maze maze : mazeGrid) {
        maze.matrix = chosenMaze->matrix;
    }
}

void Race::mazefyBinaryTree(Vector2 mouse_pos){
    Cell* cell_at_mouse = getCell(mouse_pos);
    cell_at_mouse->maze->mazefyBinaryTree();

    /*for (Maze maze : mazeGrid) {*/
    /*    maze.matrix = cell_at_mouse->maze->matrix;*/
    /*}*/
}
