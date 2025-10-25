#include "application.h"
//main.cpp need to enter into window main loop only!!!

int main() {
	try{
		Application app;
		app.run();
	}
	catch (const std::exception& ex) {
		std::cerr << "Fatal error: " << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}