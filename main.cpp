#include "DingusLib.h"
#include <string>
#include "DingusMath.h"
#include <cmath>
#include <iostream>

int main() {
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;

    Vector2 pos(350.0f, 100.0f);
    Vector2 vel(10.0f, 0.0f);

    Renderer renderer("Dingus", WINDOW_WIDTH, WINDOW_HEIGHT);

    Shader defaultShader("Shaders/default.vert", "Shaders/default.frag");

    while (!renderer.windowShouldClose()) {
        renderer.beginDrawing();
        renderer.clear(DINGUSGRAY);

        if (pos.y < WINDOW_HEIGHT) {
            vel.y += 1.0f;
        }
        if (pos.y + 100.0f > WINDOW_HEIGHT) {
            vel.y *= -0.9f;
        }
        if (pos.x < 0 || pos.x + 100.0f > WINDOW_WIDTH) {
            vel.x *= -1;
        }

        pos.add(vel);
        
        renderer.drawCircle(100.0f, 100.0f, 50.0f, WHITE, defaultShader);
        renderer.drawRectangle(pos.x, pos.y, 100.0f, 100.0f, BLUE, defaultShader);
        renderer.drawRectangle(350.0f, 100.0f, 100.0f, 100.0f, GREEN, defaultShader);
        renderer.drawRectangle(150.0f, 100.0f, 100.0f, 100.0f, RED, defaultShader);

        renderer.endDrawing();
    }

    return 0;
}