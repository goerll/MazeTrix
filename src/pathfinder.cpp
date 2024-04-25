#include "../include/pathfinder.h"
#include <SFML/Graphics/RenderWindow.hpp>

Pathfinder::Pathfinder(Maze* maze, int x, int y){
  this->maze = maze;
  this->x = x;
  this->y = y;
}

bool Pathfinder::is_path(Direction side){
  side = get_absolute_dir(side);

  switch (side) {
    case up:
      if (this->y == 0 || this->maze->matrix[this->y-1][this->x].wall_down)
        return false;
      else
        return true;

    case down:
      if (this->y == NUM_OF_LINES-1 || this->maze->matrix[this->y+1][this->x].wall_up)
        return false;
      else
        return true;

    case left:
      if (this->x == 0 || this->maze->matrix[this->y][this->x-1].wall_right)
        return false;
      else
        return true;

    case right:
      if (this->x == NUM_OF_LINES-1 || this->maze->matrix[this->y][this->x+1].wall_left)
        return false;
      else
        return true;

    default:
      return false;
  }
}

bool Pathfinder::move_absolute(Direction direction){
  if (this->is_path(direction)){
    switch (direction) {
      case up:
        this->y--;
        break;

      case down:
        this->y++;
        break;

      case left:
        this->x--;
        break;

      case right:
        this->x++;
        break;

    }

    return true;
  }

  return false;
}

bool Pathfinder::move_relative(enum Direction direction){
  if(this->move_absolute(get_absolute_dir(direction)))
      return true;
  else
    return false;
}

void Pathfinder::draw(sf::RenderWindow* window){
  this->maze->matrix[this->y][this->x].draw_highlighted(window);
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
}

