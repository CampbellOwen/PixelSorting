#include <SFML/Graphics.hpp>
#include <vector>
#include "PixelSorter.h"
#include "scene.h"
#include "utility.h"
#include <string>

int main(int /* argc */, char** /* argv */)
{
	sf::RenderWindow window(sf::VideoMode(1200, 1200), "Test", sf::Style::Default);
	sf::VertexArray points;
	sf::Texture renderTexture;
	sf::Sprite renderSprite;

	// window.setFramerateLimit(60);

	sf::Image img;
	img.loadFromFile("img/rusty.jpg");
	renderTexture.loadFromImage(img);
	renderSprite.setTexture(renderTexture);

	// Utility::resizeSprite(window, renderTexture, renderSprite);

	PixelSorter sorter(img);
	
	sf::View view = window.getDefaultView();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::Resized) {
				view.setSize({static_cast<float>(event.size.width), static_cast<float>(event.size.height)});
				window.setView(view);
				// Utility::resizeSprite(window, renderTexture, renderSprite);
			}
		}

		sorter.Update();
		renderTexture.update(img);
		// renderSprite.setTexture(renderTexture);

		window.clear();
		window.draw(renderSprite);
		window.display();
	}

	return 0;
}
