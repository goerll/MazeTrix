#pragma once

#include <SFML/Graphics.hpp>
#include <random>

// Color variables
const sf::Color NORD_DARK(36, 36, 36, 255);
const sf::Color NORD_WHITE(236, 239, 244, 255);
const sf::Color NORD_BLUE(136, 192, 208, 255);

// Size of stuff
const int WINDOW_SIZE = 800;
const int NUM_OF_LINES = 20;
const int WALL_SIZE = 2;
const int CELL_SIZE = WINDOW_SIZE / NUM_OF_LINES;
const int DELAY = 0;

// Color of stuff
const sf::Color BG_COLOR = NORD_DARK;
const sf::Color CELL_COLOR = NORD_DARK;
const sf::Color BORDER_COLOR = NORD_WHITE;
const sf::Color HIGHLIGHT_COLOR = NORD_BLUE;
const sf::Color BORDER_HIGHLIGHT_COLOR = CELL_COLOR;
