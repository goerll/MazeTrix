#include "../include/pathfinder.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "../include/global.h"

sf::RectangleShape CELL_SQUARE({ CELL_SIZE-WALL_SIZE, CELL_SIZE-WALL_SIZE});


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
  switch (direction) {
    case up:

    case down:

    case left:

    case right:

  }
}

void Pathfinder::draw_pathfinder(sf::RenderWindow* window){
  this->position->draw_highlighted(window);
}

void Pathfinder::draw_path(sf::RenderWindow* window){
  for (int i = 0; i < this->path.size(); i++){
    this->path[i]->draw_cell(window);
  }
}

char Pathfinder::get_relative_dir(enum Direction direction){
  switch (direction) {
    case up:
      switch (this->direction){
        case up:

        case down:

        case left:

        case right:

      }
 
    case down:
      switch (this->direction){
        case up:

        case down:

        case left:

        case right:

        default:
          return this->direction;
      }

    case left:
      switch (this->direction){
        case up:

        case down:

        case left:

        case right:

        default:
          return this->direction;
      }

    case right:
      switch (this->direction){
        case up:

        case down:

        case left:

        case right:

        default:
          return this->direction;
      }

  }
}

void Pathfinder::find_right_hand(Maze* maze, Cell* start, Cell* finish){
  this->path.push_back(start);
  this->direction = 'r';
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
