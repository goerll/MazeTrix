#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "cell.h"
#include "maze.h"

enum Direction {up, down, left, right};

class Pathfinder{
public:
  std::vector<Cell*> path;
  Maze* maze;
  Cell* position;
  char direction;
 
  void move_absolute(enum Direction direction);
  void move_relative(enum Direction direction);
  void draw_pathfinder(sf::RenderWindow* window);
  void draw_path(sf::RenderWindow* window);
  char get_relative_dir(enum Direction direction);
  void find_right_hand(Maze* maze, Cell* start, Cell* finish);
  bool find_recursive(Maze* maze, Cell* start);
};
