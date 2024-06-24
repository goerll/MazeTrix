#include "../include/race.h"
#include <raylib.h>
#include <queue>
#include <array>

Race::Race() : mazeGrid(2) {
    mazeGrid[0] = new Maze(Vector2i{0, 0});
    mazeGrid[1] = new Maze(Vector2i{CELL_SIZE * LINE_NUM, 0});
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
    // Get mouse position
    Vector2 coord = GetMousePosition();
    // Check if mouse is inside the window, if not, return nullptr
    if (coord.x > WIN_SIZE_X || coord.y > WIN_SIZE_Y || coord.x < 0 || coord.y < 0)
        return nullptr;

    // If mouse is before the middle of the screen, return left maze
    if (coord.x < CELL_SIZE * COL_NUM && coord.y < CELL_SIZE * LINE_NUM)
        return mazeGrid[0];

    // Else, return right maze
    return mazeGrid[1];
}

void Race::mazefyDepthFirst(){
    // Reset all mazes
    reset();
    // Get maze at mouse position
    Maze* chosenMaze = getMaze();

    // If there is no maze at the mouse position, return
    if (chosenMaze == nullptr)
        return;

    // Generate maze with depth first search at mouse
    chosenMaze->mazefyDepthFirstSearch(chosenMaze->getMouseCell());

    // Update all mazes to the new maze generated
    for (auto& maze : mazeGrid) {
        if (maze != chosenMaze) {
            maze->copyMatrix(*chosenMaze);
        }
        // Update pathfinder
        maze->getPathfinder()->update();
    }
}

void Race::mazefyBinaryTree(){
    // Reset all mazes
    reset();
    // Get maze at mouse position
    Maze* chosenMaze = getMaze();

    // If there is no maze at the mouse position, return
    if (chosenMaze == nullptr)
        return;

    // Generate maze with binary tree search at mouse
    chosenMaze->mazefyBinaryTree();

    // Update all mazes to the new maze generated
    for (auto& maze : mazeGrid) {
        if (maze != chosenMaze) {
            maze->copyMatrix(*chosenMaze);
        }
        // Update pathfinder
        maze->getPathfinder()->update();
    }
}


// Set pathfinder position to cell at mouse
void Race::setPathfinderPosition(){
    // Get maze at mouse position
    Maze* chosenMaze = getMaze();

    // If no maze at mouse position, return
    if (chosenMaze == nullptr)
        return;

    // Set pathfinder position
    chosenMaze->getPathfinder()->setPosition(chosenMaze->getMouseCell());

    // Copy the pathfinder position to all other pathfinders and clear their path
    for (auto &maze : mazeGrid) {
        maze->getPathfinder()->setPosition(chosenMaze->getPathfinder()->getPosition());
        maze->getPathfinder()->clearPath();
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
    // Mark their current position as visited
    mazeGrid[0]->getCell(depthPathfinder->getPosition()).increaseTimesVisited();
    mazeGrid[1]->getCell(depthPathfinder->getPosition()).increaseTimesVisited();

    // Initialize queue
    std::queue<Vector2i> queue;
    // Add the start position to the queue
    queue.push(breadthPathfinder->getPosition());

    // Store the start position
    Vector2i start = breadthPathfinder->getPosition();

    // Initialize previous list, previous[x][y] contains the cell that was accessed before cell [x][y]
    std::array<std::array<Vector2i, LINE_NUM>, COL_NUM> previous;
    for (int i = 0; i < LINE_NUM; i++) {
        for (int j = 0; j < COL_NUM; j++) {
            previous[i][j] = Vector2i{-1,-1};
        }
    }

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
                    // Return the pathfinder to the last step
                    depthPathfinder->setPosition(depthPathfinder->getPathTop());
                }
            }
        }

        // If breadth pathfinder isn't at the end, take one step
        if (breadthPathfinder->getPosition() != end) {
            // Get pathfinder's next step
            Vector2i nextCell = queue.front();
            // Remove last step from the queue
            queue.pop();

            // Update pathfinder position
            breadthPathfinder->setPosition(nextCell);

            // Get all accessible unvisited neighbors
            std::vector<Vector2i> neighbors = mazeGrid[1]->getAccessibleUnvisitedNeighbors(nextCell);
            // For each accessible unvisited neighbor
            for (Vector2i next : neighbors) {
                // Add the neighbor to the queue
                queue.push(next);
                // Add the neighbor to the path
                breadthPathfinder->pathPush(next);
                // Increment the neighbor's times visited
                mazeGrid[1]->getCell(next).increaseTimesVisited();
                // Update the previous list
                previous[next.x][next.y] = nextCell;
            }

            // If the pathfinder reached the end with this step
            if (breadthPathfinder->getPosition() == end) {
                // Clear the pathfinder's path
                breadthPathfinder->clearPath();
                // Starting at the final cell, go to the previous cell from it until at is equal to the starting cell
                // then we will have reconstructed the path from the end to the starting cell
                for (Vector2i at = end; at != start; at = previous[at.x][at.y]) {
                    breadthPathfinder->pathPush(at);
                }
                // Push the start to the path
                breadthPathfinder->pathPush(start);
                // Reverse the path
                breadthPathfinder->reversePath();
                // Set the pathfinder's position to the end
                breadthPathfinder->setPosition(end);
            }
        }

        // Draw the maze
        BeginDrawing();
            ClearBackground(BG_COLOR);
            draw();
        EndDrawing();
    }

}


