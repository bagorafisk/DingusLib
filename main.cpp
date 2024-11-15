#include "Renderer.h"
#include <string>
#include <cmath>

int main() {
    Renderer renderer("Dingus", 800, 600);

    while (!renderer.windowShouldClose()) {
        renderer.beginDrawing();
        renderer.clear(Color(18, 18, 18));

        renderer.drawRectangle(250.0f, 100.0f, 100.0f, 100.0f, Color(0, 255, 0));    // Green
        renderer.drawRectangle(400.0f, 100.0f, 100.0f, 100.0f, Color(0, 0, 255));    // Blue
        renderer.drawRectangle(100.0f, 100.0f, 100.0f, 100.0f, WHITE);               // White

        renderer.endDrawing();
    }

    return 0;
}
