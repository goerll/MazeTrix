#include <raylib.h>
#include "include/global.h"
#include "include/race.h"

int main() {
    InitWindow(WIN_SIZE_X, WIN_SIZE_Y, "RayTrix");
    SetTargetFPS(120);

    Race race;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_R))
            race.reset();

        if (IsKeyPressed(KEY_D))
            race.mazefyDepthFirst();

        if (IsKeyPressed(KEY_B))
            race.mazefyBinaryTree();

        if (IsKeyDown(KEY_P))
            race.setPathfinderPosition();

        if (IsKeyPressed(KEY_O)) {
            race.findWay();
        }

        BeginDrawing();
            ClearBackground(BG_COLOR);
            race.draw();
        EndDrawing();
    }
}
