#include "window.h"
//main.cpp need to enter into window main loop only!!!

int main() {
	Window app(1200, 800, "Burning pine");
	app.run();
	return 0;
}