#include <raylib.h>
#include "include/global.h"
#include "include/race.h"

int main() {
    InitWindow(WIN_SIZE_X, WIN_SIZE_Y, "RayTrix");
    SetTargetFPS(60);

    Race race;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_R))
            race.reset();

        if (IsKeyPressed(KEY_D)) {
            SetTargetFPS(RUNNING_FPS);
            race.mazefyDepthFirst();
            SetTargetFPS(DEFAULT_FPS);
        }

        if (IsKeyPressed(KEY_B)) {
            SetTargetFPS(RUNNING_FPS);
            race.mazefyBinaryTree();
            SetTargetFPS(DEFAULT_FPS);
        }

        if (IsKeyDown(KEY_P) || IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            race.setPathfinderPosition();

        if (IsKeyPressed(KEY_O) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            SetTargetFPS(RUNNING_FPS);
            race.findWay();
            SetTargetFPS(DEFAULT_FPS);
        }

        BeginDrawing();
            ClearBackground(BG_COLOR);
            race.draw();
        EndDrawing();
    }
}
