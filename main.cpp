#include "include/global.h"
#include <raylib.h>
#include "include/maze.h"
#include "include/race.h"

int main() {
    InitWindow(WIN_SIZE_X, WIN_SIZE_Y, "RayTrix");
    SetTargetFPS(120);

    Race race;
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_D))
            race.mazefyDepthFirst(GetMousePosition());
        BeginDrawing();
            ClearBackground(BG_COLOR);
            race.draw();
        EndDrawing();
    }
}
