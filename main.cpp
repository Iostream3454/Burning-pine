#include<SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>


int main() {
	sf::RenderWindow win(sf::VideoMode({ 200, 200 }), "SFML Works");
	tgui::Gui gui{ win };
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Cyan);

	while(win.isOpen()){
		while (const std::optional event = win.pollEvent())
		{
			gui.handleEvent(*event);

			if (event->is<sf::Event::Closed>())
				win.close();
		}
	}
}