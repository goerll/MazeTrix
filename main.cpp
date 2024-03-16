#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <array>

// Color variables
const sf::Color NORD_DARK(59,66,82,255);
const sf::Color NORD_WHITE(236, 239, 244, 255);
const sf::Color NORD_BLUE(136, 192, 208, 255);

// Size of stuff
const int WINDOW_SIZE = 500;
const int NUM_OF_LINES = 10;
const int CELL_SIZE = WINDOW_SIZE/NUM_OF_LINES;
const int WALL_SIZE = 2;

// Stuff
sf::RectangleShape CELL_SQUARE({CELL_SIZE, CELL_SIZE});
sf::RectangleShape BORDER_VERTICAL({WALL_SIZE, CELL_SIZE});
sf::RectangleShape BORDER_HORIZONTAL({CELL_SIZE, WALL_SIZE});

// Color of stuff
const sf::Color CELL_COLOR = NORD_DARK;
const sf::Color BORDER_COLOR = NORD_WHITE;
const sf::Color HIGHLIGHT_COLOR = NORD_BLUE;

class cell{
  public:
    bool exists;
    bool highlighted{false};
    bool wall_up{true};
    bool wall_down{true};
    bool wall_left{true};
    bool wall_right{true};

    void draw_cell(sf::RenderWindow* window, int x, int y){
      CELL_SQUARE.setPosition(x, y);
      CELL_SQUARE.setFillColor(CELL_COLOR);
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

int main(){
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "MazeTrix");
    std::array<std::array<cell, NUM_OF_LINES>, NUM_OF_LINES> matrix;
    BORDER_VERTICAL.setFillColor(BORDER_COLOR);
    BORDER_HORIZONTAL.setFillColor(BORDER_COLOR);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for(int y = 0; y < NUM_OF_LINES; y++){
          for(int x = 0; x < NUM_OF_LINES; x++){
            matrix[y][x].draw_cell(&window, x*CELL_SIZE, y*CELL_SIZE);
          }
        }

        window.display();
    }

    return 0;
}
