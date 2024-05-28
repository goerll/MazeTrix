#include "../include/pathfinder.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

sf::RectangleShape SQUARE( { CELL_SIZE - (WALL_SIZE*2), CELL_SIZE - (WALL_SIZE*2) } );

Pathfinder::Pathfinder(Maze* maze, int x = 0, int y = 0) : maze(maze), x(x), y(y) {
    map();
}

void Pathfinder::draw (sf::RenderWindow* window) {
    int x = (this->x * CELL_SIZE) + this->maze->x;
    int y = (this->y * CELL_SIZE) + this->maze->y;

    SQUARE.setFillColor(PATHFINDER_COLOR);
    SQUARE.setPosition(x + WALL_SIZE, y+WALL_SIZE);
    window->draw(SQUARE);

    draw_path(window);
}

void Pathfinder::draw_path(sf::RenderWindow* window) {
    for (Cell* cell : path) {
        cell->highlighted = true;
    }
}

void Pathfinder::map(){
    for (int y = 0; y < LINE_NUM; y++){
        for (int x = 0; x < COL_NUM; x++){
            for (int dir = up; dir <= left; ++dir){
                Cell* neighbor = this->maze->matrix[x][y].get_neighbor((Direction)dir);
                if (neighbor && is_path((Direction)dir)){
                    adjacency[x][y].push_back(neighbor);
                }
            }
            std::cout << "Cell[" << x << "][" << y << "]: ";
            for (Cell* cell : adjacency[x][y]) {
                std::cout << "(" << cell->x << "," << cell->y << ")";
            }
            std::cout << std::endl;
        }
    }
}


bool Pathfinder::dead_end(){
    if (maze->matrix[this->x][this->y].is_dead_end())
        return true;
    return false;
}

Cell* Pathfinder::random_way() {
    return maze->matrix[this->x][this->y].random_unvisited_neighbor();
}

bool Pathfinder::is_path(Direction side){
    if (!this->maze->matrix[x][y].get_neighbor(side))
        return false;
    else {
        /*switch (side) {*/
        /*    case up:*/
        /*        if (maze->matrix[x][y].wall_up){*/
        /*            return false;*/
        /*            break;*/
        /*        }*/
        /**/
        /*    case down:*/
        /*        if (maze->matrix[x][y].wall_down){*/
        /*            return false;*/
        /*            break;*/
        /*        }*/
        /**/
        /*    case left:*/
        /*        if (maze->matrix[x][y].wall_left){*/
        /*            return false;*/
        /*            break;*/
        /*        }*/
        /**/
        /*    case right:*/
        /*        if (maze->matrix[x][y].wall_right){*/
        /*            return false;*/
        /*            break;*/
        /*        }*/
        /**/
        /*    default:*/
        /*        return false;*/
        /*        break;*/
        /*}*/
        return true;
    }
}

void Pathfinder::depth_search(int x, int y) {
    bool found = false;
    while (!dead_end()) {

        Cell* way = random_way();

        path.push_back(way);
        way->times_visited++;

        if (way == &maze->matrix[x][y]){
            found = true;
            break;
        }
    }
    if (!found)
        path.pop_back();
}
