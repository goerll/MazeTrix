#pragma once
#include <SFML/Graphics.hpp>

class Cell {
public:
    int x;
    int y;

    bool active{ false };
    bool highlighted{ false };
    bool wall_up{ true };
    bool wall_down{ true };
    bool wall_left{ true };
    bool wall_right{ true };

    void draw_cell(sf::RenderWindow* window);
};
