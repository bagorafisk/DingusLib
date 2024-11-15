#include "Renderer.h"
#include <string>

int main() {
	Renderer renderer("Dingus", 800, 600);

	while (!renderer.windowShouldClose()) {
		renderer.beginDrawing();
		renderer.clear(Color(18, 18, 18));
		renderer.drawRectangle(0.0f, 0.0f, -100.0f, -100.0f, WHITE);
		renderer.endDrawing();
	}

	return 0;
}