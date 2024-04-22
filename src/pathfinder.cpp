#include "../include/pathfinder.h"
#include <SFML/Graphics/RenderWindow.hpp>

Pathfinder::Pathfinder(Maze* maze){
  this->position = &(maze->matrix[0][0]);
}

void Pathfinder::move_absolute(enum Direction direction){
  switch (direction) {
    case up:
      this->position = &(this->maze->matrix[this->position->y-1][this->position->x]);

    case down:
      this->position = &(this->maze->matrix[this->position->y+1][this->position->x]);

    case left:
      this->position = &(this->maze->matrix[this->position->y][this->position->x-1]);

    case right:
      this->position = &(this->maze->matrix[this->position->y][this->position->x+1]);

  }
}

void Pathfinder::move_relative(enum Direction direction){
  this->move_absolute(get_absolute_dir(direction));
}

void Pathfinder::draw(sf::RenderWindow* window){
  this->position->draw_highlighted(window);
}

void Pathfinder::draw_path(sf::RenderWindow* window){
  for (int i = 0; i < this->path.size(); i++){
    this->path[i]->draw_cell(window);
  }
}

/* The relative directions up and down mean frontwards and backwards */
Direction Pathfinder::get_absolute_dir(enum Direction relative_dir){
  switch (relative_dir) {

    case up:
      return this->direction;

    case down:
      switch (this->direction){
        case up:
          return down;
        case down:
          return up;
        case left:
          return right;
        case right:
          return left;
      }

    case left:
      switch (this->direction){
        case up:
          return left;
        case down:
          return right;
        case left:
          return down;
        case right:
          return up;
      }

    case right:
      switch (this->direction){
        case up:
          return right;
        case down:
          return left;
        case left:
          return up;
        case right:
          return down;
      }

    default:
      return this->direction;

  }
}

void Pathfinder::find_right_hand(Maze* maze, Cell* start, Cell* finish){
  this->path.push_back(start);
  this->direction = right;
  Cell* current_cell = start;

  while (current_cell != finish) {
    if(current_cell->wall_right){
      current_cell = maze->get_neighbor(current_cell, 'l');
    }
    else if (!current_cell->wall_down) {
      current_cell = maze->get_neighbor(current_cell, 'd');
    }
    else if (!current_cell->wall_right){
      current_cell = maze->get_neighbor(current_cell, 'r');
    }
    else if (!current_cell->wall_up){
      current_cell = maze->get_neighbor(current_cell, 'd');
    }

    current_cell->highlighted = true;
    this->path.push_back(current_cell);
  }
}

bool Pathfinder::find_recursive(Maze* maze, Cell* start){
}
