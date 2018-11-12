#include <SFML/Graphics.hpp>
#include <vector>
#include "PixelSorter.h"
#include "wipe.h"
#include "scene.h"
#include "utility.h"
#include <string>
#include <iostream>

int main(int /* argc */, char** /* argv */)
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Test", sf::Style::Default);

	// window.setFramerateLimit(60);

	std::string imgPath = "img/painting.jpg";

	Wipe scene(imgPath);
	sf::Texture texture;
	sf::Sprite sprite;
	texture.loadFromFile(imgPath);
	sprite.setTexture(texture);
	Utility::resizeSprite(window, texture, sprite);

	auto scale = sprite.getScale();
	auto local = sprite.getLocalBounds();
	auto global = sprite.getGlobalBounds();

	std::cout << "Scale {" << scale.x << ", " << scale.y << "}" << std::endl;
	std::cout << "Local Bounds {" << local.width << ", " << local.height << "}" << std::endl;
	std::cout << "Global Bounds {" << global.width << ", " << global.height << "}" << std::endl;
	
	sf::View view = window.getDefaultView();
	view.setSize({static_cast<float>(texture.getSize().x), static_cast<float>(texture.getSize().y)});

	bool done = false;

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
				
		window.clear();
		if (!scene.Update(texture) && !done) {
			done = true;
			sf::Image img = texture.copyToImage();
			img.saveToFile("output/curr_out.png");
		}
		// std::cout << "Size {" << texture.getSize().x << ", " << texture.getSize().y << "}" << std::endl;
		window.draw(sprite);
		window.display();
	}

	return 0;
}
