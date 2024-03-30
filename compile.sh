g++ -c main.cpp src/*.cpp -I "./SFML-2.6.1/include"
g++ *.o -o sfml-app -L "./SFML-2.6.1/lib" -lsfml-graphics -lsfml-window -lsfml-system

