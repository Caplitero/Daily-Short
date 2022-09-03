


#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "AppFunc.h"


class _RectangleBox :public sf::Drawable {
protected: 
	bool Tangible = 0;

public:
	_Vector2D Size;
	_Vector2D Position;//The center of the object
	sf::Color Color = sf::Color::White;
	
	

	_RectangleBox() {}
	_RectangleBox(_Vector2D size = _Vector2D(0, 0),
		_Vector2D position = _Vector2D(0, 0))
	{
		Size = size;
		Position = position;
	}
	_RectangleBox(float _SizeX, float _SizeY,
		float PosX = 0, float PosY = 0)
	{
		Size = _Vector2D(_SizeX, _SizeY);
		Position = _Vector2D(PosX, PosY);

	}
	void setSize(_Vector2D newSize)
	{
		Size = newSize;
	}
	void setTangible(bool Setting)
	{
		Tangible = Setting;
	}
	bool isTangible()
	{
		return Tangible;
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

	void onCollision()
	{

	}

	void checkCollision(_Vector2D offset, _RectangleBox & _Object)
	{
		float L = Position.x - Size.x / 2 + offset.x -\
			(_Object.Position.x + _Object.Size.x / 2) ;
		float R = Position.x + Size.x / 2 + offset.x -\
			(_Object.Position.x - _Object.Size.x / 2) ;
		float U = Position.y - Size.y / 2 + offset.y -\
			(_Object.Position.y + _Object.Size.y / 2) ;
		float D = Position.y + Size.y / 2 + offset.y - \
			(_Object.Position.y - _Object.Size.y / 2) ;
		_Object.Color = sf::Color::White; // Visual test
	
		if ((L < 0 && R>0 && U < 0 && D>0))
		{

			_Object.onCollision();
			if (_Object.isTangible() && isTangible()) {
				_Object.Color = sf::Color::Red; // Visual test
				_Vector2D Relative = Position -
					_Object.Size / 2 - _Object.Position - Size / 2;
				_Vector2D Dist = Size / 2 + _Object.Size / 2;

				if ((-Relative.x >= Size.x + _Object.Size.x) &&
					offset.x > 0)
				{

					Position.x = _Object.Position.x - Dist.x;
					offset.x = 0;
				}
				else
					if (L - offset.x > 0 && offset.x < 0)
					{
						Position.x = _Object.Position.x +
							Dist.x + 0.001;
						offset.x = 0;
					}

				if (-Relative.y >= Size.y + _Object.Size.y
					&& offset.y > 0)
				{

					Position.y = _Object.Position.y - Dist.y;
					offset.y = 0;
				}
				else
					if (U - offset.y > 0 && offset.y < 0)
					{

						Position.y = _Object.Position.y + 
							Dist.y + 0.001;
						offset.y = 0;
					}




				move(offset);
			}
			else move(offset);


		}
		else move(offset);

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


class _Wall : public _RectangleBox
{
	
public:
	using _RectangleBox::_RectangleBox;
	

};

class _Player : public _RectangleBox
{

public:
	using _RectangleBox::_RectangleBox;

};



sf::VideoMode mode(640, 840);
const float PI = 3.14f;
const float Speed = 300;
const float Degrees45 = 0.7071;
sf::Mouse Mouse;

_Vector2D VelocityCalc(float Delta_Time)
{
	_Vector2D vel = _Vector2D(0, 0);
	if (sf::Keyboard::isKeyPressed\
		(sf::Keyboard::A))vel.x -= Speed;
	if (sf::Keyboard::isKeyPressed\
		(sf::Keyboard::D))vel.x += Speed;
	if (sf::Keyboard::isKeyPressed\
		(sf::Keyboard::S))vel.y += Speed;
	if (sf::Keyboard::isKeyPressed\
		(sf::Keyboard::W))vel.y -= Speed;
	if (vel.x && vel.y)vel = vel * 0.7071;
	return vel*Delta_Time;

}



int main() {

	sf::Clock clock;

	//Create window
	sf::RenderWindow window(mode, "sfml");
	window.setFramerateLimit(60);

	//Create the objects
	_Wall rectangle
	(150,
		100,
		window.getSize().x / 2,
		window.getSize().y / 2);
	_Player Rect2(100.f, 100.f);


	float starting = clock.getElapsedTime()
		.asMilliseconds();

	rectangle.setTangible(1);
	


	//Game loop
	while (window.isOpen())
	{
		//Find time between frames (dt)
		float ending = clock.getElapsedTime()
			.asMilliseconds() + 0.00001;
		float dt = (ending - starting) / 1000;
		starting = ending;

		Rect2.setTangible(1);
		Rect2.checkCollision(VelocityCalc(dt),\
			rectangle);
		

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