



#include <SFML/Graphics.hpp>
#include <iostream>
sf::VideoMode mode(640, 840);

class Follower : public sf::RectangleShape {
	sf::Mouse* _mouse;
	sf::RenderWindow* _window;
public:

	Follower() :sf::RectangleShape() {
		_mouse = new sf::Mouse;
		_window = new sf::RenderWindow;

	}

	Follower(sf::Mouse* Mouse, sf::RenderWindow* Window)
		:sf::RectangleShape()
	{
		_mouse = Mouse;
		_window = Window;

	}



	void update(float DeltaTime)
	{
		sf::Vector2f center = sf::Vector2f(
			_mouse->getPosition(*_window)) -
			this->getSize() / 2.f;
		sf::Vector2f translation =
			center - this->getPosition();
		this->move(translation * DeltaTime * 2.f);

	}

};


sf::Mouse Mouse;

int main() {

	sf::Clock clock;
	//Create window
	sf::RenderWindow window(mode, "sfml");
	window.setFramerateLimit(60);

	Follower rect(&Mouse, &window);
	rect.setSize(sf::Vector2f(100, 100));
	float starting = clock.getElapsedTime()
		.asMilliseconds();

	//Game loop
	while (window.isOpen())
	{

		float ending = clock.getElapsedTime()
			.asMilliseconds() + 0.00001;
		float dt = (ending - starting) / 1000;
		starting = ending;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		rect.update(dt);

		window.clear();
		window.draw(rect);
		window.display();


	}
	return 0;

}