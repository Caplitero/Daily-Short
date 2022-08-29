


#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>


class _Vector2D
{

public:
	float x, y;
	_Vector2D()
	{
		x = 0;
		y = 0;
	}
	_Vector2D(float X, float Y) {
		x = X;
		y = Y;
	}

	friend _Vector2D operator-(_Vector2D L_vec,
		_Vector2D R_vec)
	{
		return(_Vector2D(L_vec.x - R_vec.x,
			L_vec.y - R_vec.y));
	}

	friend _Vector2D operator+(_Vector2D L_vec,
		_Vector2D R_vec)
	{
		return(_Vector2D(L_vec.x + R_vec.x,
			L_vec.y + R_vec.y));
	}

	friend _Vector2D operator*(_Vector2D L_vec,
		_Vector2D R_vec)
	{
		return _Vector2D(L_vec.x * R_vec.x,
			L_vec.y * R_vec.y);
	}

	friend _Vector2D operator*(_Vector2D L_vec,
		float Constant)
	{
		return _Vector2D(L_vec.x * Constant,
			L_vec.y * Constant);
	}

	friend _Vector2D operator+=(_Vector2D& L_vec,
		_Vector2D R_vec)
	{
		return L_vec = L_vec + R_vec;
	}

	friend _Vector2D operator/(_Vector2D L_vec,
		float Constant)
	{
		return _Vector2D(L_vec.x / Constant,
			L_vec.y / Constant);
	}



};



class _Square :public sf::Drawable {
public:
	_Vector2D Size;
	_Vector2D Position;//The center of the object
	sf::Color Color = sf::Color::White;

	_Square() {}
	_Square(_Vector2D size = _Vector2D(0, 0),
		_Vector2D position = _Vector2D(0, 0))
	{
		Size = size;
		Position = position;
	}
	_Square(float _SizeX, float _SizeY,
		float PosX = 0, float PosY = 0)
	{
		Size = _Vector2D(_SizeX, _SizeY);
		Position = _Vector2D(PosX, PosY);

	}
	void setSize(_Vector2D newSize)
	{
		Size = newSize;
	}
	void setPosition(_Vector2D newPosition)
	{
		Position = newPosition;
	}

	void setPosition(float x, float y)
	{
		Position = _Vector2D(x, y);
	}

	void move(float x, float y)
	{
		Position += _Vector2D(x, y);
	}
	void move(_Vector2D MoveVec)
	{
		Position += MoveVec;
	}

	bool checkCollision(_Square _Object)
	{
		return Position.x - Size.x / 2 <
			_Object.Position.x + _Object.Size.x / 2
			&& Position.x + Size.x / 2 >
			_Object.Position.x - _Object.Size.x / 2
			&& Position.y - Size.y / 2 <
			_Object.Position.y + _Object.Size.y / 2
			&& Position.y + Size.y / 2 >
			_Object.Position.y - _Object.Size.y / 2;

	}

	void draw(sf::RenderTarget& target,
		sf::RenderStates states) const
	{
		sf::VertexArray Varray;
		Varray.setPrimitiveType(sf::Quads);
		Varray.resize(4);
		Varray[0].position = sf::Vector2f(\
			Position.x - Size.x / 2,
			Position.y - Size.y / 2);
		Varray[1].position = sf::Vector2f(\
			Position.x + Size.x / 2,
			Position.y - Size.y / 2);
		Varray[2].position = sf::Vector2f(\
			Position.x + Size.x / 2,
			Position.y + Size.y / 2);
		Varray[3].position = sf::Vector2f(\
			Position.x - Size.x / 2,
			Position.y + Size.y / 2);

		Varray[0].color = Varray[1].color =
			Varray[2].color = Varray[3].color = Color;

		target.draw(Varray);

	}

};

sf::VideoMode mode(640, 840);
const float PI = 3.14f;
sf::Mouse Mouse;

int main() {

	sf::Clock clock;

	//Create window
	sf::RenderWindow window(mode, "sfml");
	window.setFramerateLimit(60);

	//Create the objects
	_Square rectangle
	(100,
		100,
		window.getSize().x / 2,
		window.getSize().y / 2);
	_Square Rect2(100.f, 100.f);


	float starting = clock.getElapsedTime()
		.asMilliseconds();


	//Game loop
	while (window.isOpen())
	{
		//Find time between frames (dt)
		float ending = clock.getElapsedTime()
			.asMilliseconds() + 0.00001;
		float dt = (ending - starting) / 1000;
		starting = ending;


		Rect2.setPosition(Mouse.\
			getPosition(window).x,
			Mouse.getPosition(window).y);
		if (Rect2.checkCollision(rectangle))\
			Rect2.Color = sf::Color::Red;
		else Rect2.Color = sf::Color::White;

		//Event loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//update object position


		//draw on the screen
		window.clear();
		window.draw(Rect2);
		window.draw(rectangle);
		window.display();


	}
	return 0;

}