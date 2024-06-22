# MazeTrix: a graph traversal algorithm visualizer (with mazes)


https://github.com/goerll/MazeTrix/assets/90577512/0c1f6a26-a45d-4d77-a9eb-2fb9dc103ff4



## Index
- [Introduction](#introduction)
- [Features](#features)
- [Usage](#description)
- [Project Structure](#project-structure)
- [Algorithms Used](#algorithms-used)
- [Acknowledgements](#acknowledgements)

## Introduction
The goal of this project is to provide a  **cool looking**, real-time visualization of maze generation algorithms and a visual comparison of graph traversal algorithms while allowing the user to control the whole thing.

## Features
### Maze Grid
The program displays a grid consisting of two mazes that mirror each other, if you mazefy one of them, the maze is copied to the other one too.

https://github.com/goerll/MazeTrix/assets/90577512/88f48e2e-71fa-4861-a546-4469ecf8cde7


### Pathfinders
Each maze has a pathfinder and they also mimick each other, but the pathfinder on the left maze will always find it's way to other positions through the depth first search algorithm, and the one on the right will always use breadth first search, see who get's there faster!

https://github.com/goerll/MazeTrix/assets/90577512/ce7bd07c-e39c-4909-af2e-2c771a18b29d

## Usage
### Compiling and Running
``` bash
# Compile
Cmake .
make
# Run
./bin/MazeTrix
```
### Keybinds
| Key | Alt | Function |
| - | - | - |
| <kbd>D</kbd> | - | Generates maze with depth first search starting on the cell at mouse |
| <kbd>B</kbd> | - | Generates maze using the binary tree algorithm on the maze at mouse |
| <kbd>P</kbd> | <kbd>🖱️ LMB</kbd> | Place pathfinders at cell at mouse |
| <kbd>O</kbd> | <kbd>🖱️ RMB</kbd> | Make pathfinders find their way to where the mouse is |

## Project Structure
```mermaid
%%{init: {'theme': 'dark' } }%%
classDiagram
    class Maze {
        Vector2i position
        std::vector<std::vector<Cell>> matrix
        std::unique_ptr<Pathfinder> pathfinder

        Maze()
        Maze(Vector2i pos)

        std::vector<std::vector<std::vector<Vector2i>>> toGraph()
        void draw()
        void copyMatrix(const Maze& maze)
        void reset()
        void resetVisited()
        Vector2i getMouseCell()
        Cell& getCell(Vector2i cell)
        bool isAccessible(Vector2i cell, Vector2i neighbor)
        bool isDeadEnd(Vector2i cell)
        Vector2i getNeighbor(Vector2i cell, Direction direction)
        std::vector<Vector2i> getNeighbors(Vector2i cell)
        std::vector<Vector2i> getAccessibleNeighbors(Vector2i cell)
        std::vector<Vector2i> getUnvisitedNeighbors(Vector2i cell)
        std::vector<Vector2i> getAccessibleUnvisitedNeighbors(Vector2i cell)
        Vector2i getRandomNeighbor(std::vector<Vector2i> potentialNeighbors)
        void mazefyBinaryTree()
        void mazefyDepthFirstSearch(Vector2i startCell)
        Vector2i getPosition()
        std::vector<std::vector<Cell>>& getMatrix()
        std::unique_ptr<Pathfinder>& getPathfinder()
    }

    class Cell {
        Vector2i position
        bool active
        bool wall_up
        bool wall_down
        bool wall_left
        bool wall_right
        int times_visited

        Cell()
        Cell(Vector2i position)

        void draw(Vector2i offset)
        void drawWalls(Vector2i offset)
        void drawSquare(Vector2i offset)
        Vector2i getPosition()
        bool getWall(Direction direction)
        bool getActive()
        int getTimesVisited()
        void setActive(bool state)
        void setWall(Direction direction, bool state)
        void increaseTimesVisited()
        void resetTimesVisited()
    }

    class Pathfinder {
        Maze* maze
        Vector2i position
        std::vector<Vector2i> path
        std::vector<std::vector<std::vector<Vector2i>>> map

        Pathfinder(Maze* maze)

        void draw()
        bool isDeadEnd()
        Vector2i getWay()
        void setPosition(Vector2i cell)
        void update()
        void clearPath()
        void pathPush(Vector2i cell)
        void pathPop()
        void reversePath()
        void depthFirstSearch(Vector2i end)
        void breadthFirstSearch(Vector2i end)
        Vector2i getPosition()
        Vector2i getPathTop()
        std::vector<Vector2i> getPath()
        bool isPathEmpty()
    }

    class Race {
        std::vector<Maze*> mazeGrid

        Race()

        void draw()
        void reset()
        Maze* getMaze()
        void mazefyDepthFirst()
        void mazefyBinaryTree()
        void setPathfinderPosition()
        void findWay()
    }
```

## Algorithms Used
### Generation
- Depth First Search
- Binary Tree
### Solving
These use an adjacency list that represents the maze in the form of a graph.
- Depth First Search
- Breadth First Search

## Acknowledgements
This project was created for my Object Oriented Programming II class on my third semester in college. Special thanks to [SamVeras](www.github.com/SamVeras) for suggesting raylib and helping me immensely with final stage debugging and to [JotaEspig](www.github.com/JotaEspig) for setting up the Cmake for the project.
