#pragma once

#include <raylib.h>

// COLOR VARIABLES
constexpr Color NORD_DARK = CLITERAL(Color){36, 36, 36, 255};
constexpr Color NORD_WHITE = CLITERAL(Color){236, 239, 244, 255};
constexpr Color NORD_BLUE = CLITERAL(Color){136, 192, 208, 255};

// SIZE OF STUFF
// Number of lines and collumns
constexpr int LINE_NUM = 20;
constexpr int COL_NUM = 20;
// Cell and wall size
constexpr int WALL_SIZE = 1;
constexpr int CELL_SIZE = 20;
// Window size
constexpr int WIN_SIZE_X = (CELL_SIZE * COL_NUM) * 2;
constexpr int WIN_SIZE_Y = (CELL_SIZE * LINE_NUM);

// COLOR OF STUFF
// Background
constexpr Color BG_COLOR = NORD_DARK;
// Cell in normal state
constexpr Color CELL_COLOR = NORD_DARK;
constexpr Color WALL_COLOR = NORD_WHITE;
// Cell in highlighted state
constexpr Color HIGHLIGHT_COLOR = NORD_BLUE;
constexpr Color BORDER_HIGHLIGHT_COLOR = NORD_DARK;
// Pathfinder color
constexpr Color PATHFINDER_COLOR = NORD_BLUE;

// ENUM
enum Direction {up, right, down, left};

// Random ENUM
Direction random_dir();
