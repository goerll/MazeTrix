//#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <random>
#include <array>

// Color variables
const sf::Color NORD_DARK(59,66,82,255);
const sf::Color NORD_WHITE(236, 239, 244, 255);
const sf::Color NORD_BLUE(136, 192, 208, 255);

// Size of stuff
const int WINDOW_SIZE = 800;
const int NUM_OF_LINES = 20;
const int CELL_SIZE = WINDOW_SIZE/NUM_OF_LINES;
const int WALL_SIZE = 2;
const int DELAY = 0;

// Stuff
sf::RectangleShape CELL_SQUARE({CELL_SIZE, CELL_SIZE});
sf::RectangleShape BORDER_VERTICAL({WALL_SIZE, CELL_SIZE});
sf::RectangleShape BORDER_HORIZONTAL({CELL_SIZE, WALL_SIZE});

// Color of stuff
const sf::Color BG_COLOR = NORD_DARK;
const sf::Color CELL_COLOR = NORD_DARK;
const sf::Color BORDER_COLOR = NORD_BLUE;
const sf::Color HIGHLIGHT_COLOR = NORD_BLUE;

// Random number generation
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis;

int rand_num(int start, int end) {
    // Update the distribution range
    dis.param(std::uniform_int_distribution<>::param_type(start, end));
    return dis(gen);
}

class cell{
  public:
    bool active{false};
    bool highlighted{false};
    bool wall_up{true};
    bool wall_down{true};
    bool wall_left{true};
    bool wall_right{true};

    void draw_cell(sf::RenderWindow* window, int x, int y){
      CELL_SQUARE.setPosition(x, y);
      if(this->highlighted){
        CELL_SQUARE.setFillColor(HIGHLIGHT_COLOR);
      }
      else{
        CELL_SQUARE.setFillColor(CELL_COLOR);
      }

      window->draw(CELL_SQUARE);

      if(wall_up){
        BORDER_HORIZONTAL.setPosition(x, y);
        window->draw(BORDER_HORIZONTAL);
      }
      if(wall_down){
        BORDER_HORIZONTAL.setPosition(x, y+(CELL_SIZE-WALL_SIZE));
        window->draw(BORDER_HORIZONTAL);
      }
      if(wall_left){
        BORDER_VERTICAL.setPosition(x, y);
        window->draw(BORDER_VERTICAL);
      }
      if(wall_right){
        BORDER_VERTICAL.setPosition(x+(CELL_SIZE-WALL_SIZE), y);
        window->draw(BORDER_VERTICAL);
      }

    }
};

class Maze{
  public:
    std::array<std::array<cell, NUM_OF_LINES>, NUM_OF_LINES> matrix;

    void draw(sf::RenderWindow* window){
      for(int y = 0; y < NUM_OF_LINES; y++){
        for(int x = 0; x < NUM_OF_LINES; x++){
          if(this->matrix[y][x].active){
            this->matrix[y][x].draw_cell(window, x*CELL_SIZE, y*CELL_SIZE);
          }
        }
      }
    }

    void mazefy_binary_tree(sf::RenderWindow* window){
      for(int y = 0; y < NUM_OF_LINES; y++){
        for(int x = 0; x < NUM_OF_LINES; x++){
          this->matrix[y][x].active = true;

          int random = rand_num(0, 1);

          if(random == 1 or x == 0 or y == 0){
            this->matrix[y][x].wall_up = false;
            if(y > 0){
              this->matrix[y-1][x].wall_down = false;
              this->matrix[y-1][x].draw_cell(window, x*CELL_SIZE, (y-1)*CELL_SIZE);
            }
          }

          if(random == 0 or x == 0 or y == 0){
            this->matrix[y][x].wall_left = false;
            if(x > 0){
              this->matrix[y][x-1].wall_right = false;
              this->matrix[y][x-1].draw_cell(window, (x-1)*CELL_SIZE, y*CELL_SIZE);
            }
          }

          this->matrix[y][x].draw_cell(window, x*CELL_SIZE, y*CELL_SIZE);
          window->display();
          sf::sleep(sf::milliseconds(DELAY));
        }
      }
    }

};

int main(){
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "MazeTrix");

    BORDER_VERTICAL.setFillColor(BORDER_COLOR);
    BORDER_HORIZONTAL.setFillColor(BORDER_COLOR);

    Maze maze;
    maze.mazefy_binary_tree(&window);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(NORD_DARK);

        maze.draw(&window);

        window.display();
    }

    return 0;
}
