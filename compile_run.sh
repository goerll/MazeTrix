g++ -c main.cpp -I "/home/$USER/MazeTrix/SFML-2.6.1/include"
g++ main.o -o sfml-app -L "/home/$USER/MazeTrix/SFML-2.6.1/lib" -lsfml-graphics -lsfml-window -lsfml-system
LD_LIBRARY_PATH=/home/$USER/MazeTrix/SFML-2.6.1/lib ./sfml-app
