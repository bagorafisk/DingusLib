#include "Renderer.h"
#include <string>

int main() {
	Renderer renderer("Dingus", 800, 600);

	while (!renderer.windowShouldClose()) {
		renderer.drawRectangle(100.0f, 100.0f, 100.0f, 100.0f, Color(255, 255, 0));
	}

	return 0;
}