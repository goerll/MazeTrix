#pragma once

#include <random>
#include <array>
#include <raylib.h>

// COLOR VARIABLES
const Color NORD_DARK = CLITERAL(Color){36, 36, 36, 255};
const Color NORD_WHITE = CLITERAL(Color){236, 239, 244, 255};
const Color NORD_BLUE = CLITERAL(Color){136, 192, 208, 255};

// SIZE OF STUFF
// Number of lines and collumns
const int LINE_NUM = 20;
const int COL_NUM = 20;
// Cell and wall size
const int WALL_SIZE = 1;
const int CELL_SIZE = 20;
// Window size
const int WIN_SIZE_X = (CELL_SIZE * COL_NUM) * 2;
const int WIN_SIZE_Y = (CELL_SIZE * LINE_NUM);

// COLOR OF STUFF
// Background
const Color BG_COLOR = NORD_DARK;
// Cell in normal state
const Color CELL_COLOR = NORD_DARK;
const Color WALL_COLOR = NORD_WHITE;
// Cell in highlighted state
const Color HIGHLIGHT_COLOR = NORD_BLUE;
const Color BORDER_HIGHLIGHT_COLOR = NORD_DARK;
// Pathfinder color
const Color PATHFINDER_COLOR = NORD_BLUE;

// ENUM
enum Direction {up, right, down, left};

// Random ENUM
Direction random_dir();
