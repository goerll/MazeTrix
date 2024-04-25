#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "cell.h"
#include "maze.h"
#include "global.h"

class Pathfinder{
public:
  std::vector<Cell*> path;
  Maze* maze;
  int x;
  int y;
  Direction direction { up };
 
  Pathfinder(Maze* maze, int x, int y);
  bool is_path(Direction side);
  bool move_absolute(Direction direction);
  bool move_relative(Direction direction);
  void draw(sf::RenderWindow* window);
  void draw_path(sf::RenderWindow* window);
  Direction get_absolute_dir(enum Direction direction);
  void find_right_hand(Maze* maze, Cell* start, Cell* finish);
  bool find_recursive(Maze* maze, Cell* start);
};
