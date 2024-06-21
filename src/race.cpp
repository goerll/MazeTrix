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

// Make pathfinder find it's way to cell at mouse (depth first for left maze, breadth first for right maze)
void Race::findWay() {
    // Get maze at mouse position
    Maze* chosenMaze = getMaze();

    // If no maze at mouse position, return
    if (chosenMaze == nullptr)
        return;

    // Reset all mazes
    for (auto& maze : mazeGrid){
        maze->resetVisited();
        maze->getPathfinder()->clearPath();
    }

    // Store end position as the cell that's at mouse
    Vector2i end = chosenMaze->getMouseCell();

    // Get pathfinders
    std::unique_ptr<Pathfinder>& depthPathfinder = mazeGrid[0]->getPathfinder();
    std::unique_ptr<Pathfinder>& breadthPathfinder = mazeGrid[1]->getPathfinder();

    // Add their current position to their path
    depthPathfinder->pathPush(depthPathfinder->getPosition());
    breadthPathfinder->pathPush(breadthPathfinder->getPosition());

    // Initialize previous list, previous[x][y] contains the cell that was accessed before cell [x][y]
    using std::vector;
    vector<vector<Vector2i>> previous(COL_NUM, vector<Vector2i>(LINE_NUM, {-1, -1}));

    // While pathfinders aren't both at the end
    while (depthPathfinder->getPosition() != end || breadthPathfinder->getPosition() != end) {

        // If depth pathfinder isn't at the end, take one step
        if (depthPathfinder->getPosition() != end) {
            // Get pathfinder's next step
            Vector2i nextCell = depthPathfinder->getWay();
            // If there's a next step
            if (nextCell != Vector2i{-1, -1}) {
                // Pathfinder takes the next step
                depthPathfinder->setPosition(nextCell);
                // Increment the cell's times visited
                mazeGrid[0]->getCell(nextCell).increaseTimesVisited();
                // Add the step to the path
                depthPathfinder->pathPush(nextCell);
            }
            else {
                // If there's no next step, remove the last step from the path
                depthPathfinder->pathPop();
                // If the path isn't empty
                if (!depthPathfinder->isPathEmpty()) {
                    depthPathfinder->setPosition(depthPathfinder->getPathTop());
                }
            }
        }

        // If breadth pathfinder isn't at the end, take one step
        if (breadthPathfinder->getPosition() != end) {
            breadthPathfinder->setPosition(end);
        }

        BeginDrawing();
            ClearBackground(BG_COLOR);
            draw();
        EndDrawing();
    }
}

