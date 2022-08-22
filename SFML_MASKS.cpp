



#include <SFML/Graphics.hpp>
sf::VideoMode mode(640, 840);

int main() {

	sf::Image image;
	sf::Texture texture2;
	sf::Texture texture;
	sf::RectangleShape sprite1;
	sf::RectangleShape sprite2;

	//Create window
	sf::RenderWindow window(mode, "sfml");

	//Load our image
	image.loadFromFile("image.jpg");

	//Create first sprite
	texture.loadFromImage(image);
	sprite1.setPosition(sf::Vector2f(200, 0));
	sprite1.setSize(sf::Vector2f(200, 200));
	sprite1.setTexture(&texture);

	//Set White As Mask
	//the color becomes transparent
	image.createMaskFromColor(sf::Color::White);

	//Create second sprite
	sprite2.setSize(sf::Vector2f(200, 200));
	texture2.loadFromImage(image);
	sprite2.setTexture(&texture2);

	//Game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		//Draw the objects
		window.draw(sprite1);
		window.draw(sprite2);
		window.display();


	}
	return 0;

}


