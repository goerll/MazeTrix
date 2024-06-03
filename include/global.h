#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <array>

// COLOR VARIABLES
const sf::Color NORD_DARK(36, 36, 36, 255);
const sf::Color NORD_WHITE(236, 239, 244, 255);
const sf::Color NORD_BLUE(136, 192, 208, 255);

// SIZE OF STUFF
// Number of lines and collumns
const int LINE_NUM = 20;
const int COL_NUM = 20;
// Cell and wall size
const int WALL_SIZE = 2;
const int CELL_SIZE = 40;
// Window size
const int WIN_SIZE_X = CELL_SIZE * COL_NUM;
const int WIN_SIZE_Y = CELL_SIZE * LINE_NUM;

// COLOR OF STUFF
// Background
const sf::Color BG_COLOR = NORD_DARK;
// Cell in normal state
const sf::Color CELL_COLOR = NORD_DARK;
const sf::Color BORDER_COLOR = NORD_WHITE;
// Cell in highlighted state
const sf::Color HIGHLIGHT_COLOR = NORD_BLUE;
const sf::Color BORDER_HIGHLIGHT_COLOR = NORD_DARK;
// Pathfinder color
const sf::Color PATHFINDER_COLOR = sf::Color::Cyan;

// ENUM
enum Direction {up, right, down, left};

// Random ENUM
Direction random_dir();
