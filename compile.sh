g++ -c main.cpp src/*.cpp -I "./SFML-2.6.1/include"
g++ *.o -o sfml-app -L "./SFML-2.6.1/lib" "./SFML-2.6.1/lib/libsfml-graphics.so.2.6" "./SFML-2.6.1/lib/libsfml-window.so.2.6" "./SFML-2.6.1/lib/libsfml-system.so.2.6"

