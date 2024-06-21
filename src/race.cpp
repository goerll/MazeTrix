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


// Set pathfinder position to cell at mouse 
void Race::setPathfinderPosition(){
    /*Vector2 coord = GetMousePosition();*/
    Maze* chosenMaze = getMaze();

    if (chosenMaze == nullptr)
        return;

    chosenMaze->getPathfinder()->setPosition(chosenMaze->getMouseCell());

    for (auto &maze : mazeGrid) {
        if (maze.get() != chosenMaze) {
            maze->getPathfinder()->setPosition(chosenMaze->getPathfinder()->getPosition());
        }
    }
}

// Make pathfinder find it's way to cell at mouse (depth first for left maze, binary tree for right maze)
void Race::findWay() {
    Maze* chosenMaze = getMaze();
    if (chosenMaze == nullptr)
        return;

    for (auto& maze : mazeGrid){
        maze->resetVisited();
        maze->getPathfinder()->clearPath();
    }

    Vector2i end = chosenMaze->getMouseCell();

    std::unique_ptr<Pathfinder>& depthPathfinder = mazeGrid[0]->getPathfinder();
    depthPathfinder->pathPush(depthPathfinder->getPosition());

    std::unique_ptr<Pathfinder>& breadthPathfinder = mazeGrid[1]->getPathfinder();
    breadthPathfinder->pathPush(breadthPathfinder->getPosition());
    using std::vector;
    vector<vector<Vector2i>> previous(COL_NUM, vector<Vector2i>(LINE_NUM, {-1, -1}));

    while (depthPathfinder->getPosition() != end || breadthPathfinder->getPosition() != end) {

        if (depthPathfinder->getPosition() != end) {
            Vector2i nextCell = depthPathfinder->getWay();
            if (nextCell != Vector2i{-1, -1}) {
                depthPathfinder->setPosition(nextCell);
                mazeGrid[0]->getCell(nextCell).increaseTimesVisited();
                depthPathfinder->pathPush(nextCell);
            }
            else {
                depthPathfinder->pathPop();
                if (depthPathfinder->isPathEmpty()) {
                    depthPathfinder->setPosition(depthPathfinder->getPathTop());
                }
            }

        }

        if (breadthPathfinder->getPosition() != end) {
            breadthPathfinder->setPosition(end);
        }

        BeginDrawing();
            ClearBackground(BG_COLOR);
            draw();
        EndDrawing();
    }
}

