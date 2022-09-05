
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

class App_Structure
{
protected:

	// The view can be used to show
	// only a part of the whole app
	//----------------------------//
	sf::View APP_View;
	//----------------------------//

	// The APP_Clock is used to 
	// calculate Delta_Time
	//----------------------------//
	sf::Clock APP_Clock;
	//----------------------------//

	// Delta Time is the time between frames
	// used for accurate object manipulation
	//----------------------------//
	float Delta_time = 0;
	//----------------------------//

	// Variable used to calculate DT
	//----------------------------//
	float LastFrame_time = 0;
	//----------------------------//

	// The actual APP
	//----------------------------//
	sf::RenderWindow* window;
	//----------------------------//

	// This vector can be used inside onDraw
	// window->draw(Drawable_Layers[i])
	// to draw objects more easily
	//---------------------------//
	std::vector<sf::Drawable*> Drawable_Layers;
	//---------------------------//

	// Override this function to initialize 
	// everything on the creation of the app
	virtual void onCreate()
	{
		window->setFramerateLimit(70);
		window->setVerticalSyncEnabled(false);

	}

	// Override this function to change
	// what is being drawn to the window
	virtual void onDraw()
	{
		window->clear();
		for (auto& Item : Drawable_Layers)
		{

			window->draw(*Item);
			delete(Item);

		}
		Drawable_Layers.clear();
		window->display();

	}

	// Override this function to free memory 
	// when the app is being closed
	virtual void onClose()
	{
		delete(window);
	}


	// Override to set new events
	virtual void onEvent()
	{


		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
		}


	}

	// Override what the app will do 
	virtual void onUpdate()
	{

	}


public:

	App_Structure(sf::VideoMode mode, const sf::String& title,
		sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& 
		settings = sf::ContextSettings())
	{
		window = new sf::RenderWindow(mode,
			title, style, settings);


	}
	App_Structure(sf::WindowHandle handle,
		const sf::ContextSettings& settings = sf::ContextSettings())
	{
		window = new sf::RenderWindow(handle, settings);


	}


	// Start the main loop of the app
	void Start()
	{
		onCreate();
		while (window->isOpen())
		{
			Delta_time = (APP_Clock.getElapsedTime().asMilliseconds() -
				LastFrame_time + 0.00001f) / 1000.f;
			LastFrame_time = (float) APP_Clock.getElapsedTime().asMilliseconds();

			onEvent();
			onUpdate();
			onDraw();
		}
		onClose();

	}

};


class App :public App_Structure
{

	virtual void onCreate()override
	{
		window->setFramerateLimit(60);
		window->setVerticalSyncEnabled(false);

	}

	virtual void onUpdate()override
	{

		sf::RectangleShape* item = new sf::RectangleShape(sf::Vector2f(100, 100));
		Drawable_Layers.push_back(item);
	}

public:
	using App_Structure::App_Structure;

};




struct _Vector3D
{
	// Coordinates of the Vector
	float x, y, z;
	
	_Vector3D()
	{
		x = 0; y = 0; z = 0;
	}

	// Constructor with specified inputs
	_Vector3D(float X , float Y , float Z = 0)
	{
		x = X;
		y = Y;
		z = Z;
	}

	/* Distance from a vector to another vector
	*/
	float DistanceTo(_Vector3D Vector)
	{
		return (float)sqrt(pow(x - Vector.x, 2) 
				   +pow(y - Vector.y, 2) 
				   +pow(z - Vector.z, 2));
	}

	// The angle Between 2 vectors (0-180 degrees)
	float AngleTo(_Vector3D vector)
	{
		float Theta = (x * vector.x + y * vector.y + z * vector.z) /
			(getMagnitude() * vector.getMagnitude());
		return  acosf(Theta);

	}

	// Get the size of the vector 
	float getMagnitude()
	{

		return sqrtf(x * x + y * y + z * z);
	}

	/* Compute the Cross Product of two vectors
	The return is a 3D vector */
	_Vector3D CrossProduct(_Vector3D R_Vector)
	{
		return _Vector3D(
			(y * R_Vector.z - z * R_Vector.y),
			-(x * R_Vector.z - z * R_Vector.x),
			(x * R_Vector.y - y * R_Vector.x));
	}

	// Compute the dot Product of two vectors
	float DotProduct(_Vector3D R_Vector)
	{
		return (x * R_Vector.x + y * R_Vector.y + z * R_Vector.z);
	}

	// Return the 3D projection of vectorA on vectorB
	// *the size of A on B*
	_Vector3D Proj_OnVec(_Vector3D R_Vector)
	{
		return R_Vector * (DotProduct(R_Vector) /(float) pow(R_Vector.getMagnitude(), 2));
	}

	// Convert the Vector to 0-1 
	// only the size changes , not the directior 
	_Vector3D Normalize()
	{

		float magnitude = getMagnitude();
		return _Vector3D(x / magnitude, y / magnitude,
			z / magnitude);
	}

	// Custom operators to ease calculations
	//----------------------------------//
	friend _Vector3D operator+(_Vector3D L_Vec, _Vector3D R_Vec)
	{
		return _Vector3D(L_Vec.x + R_Vec.x, L_Vec.y + R_Vec.y,
			L_Vec.z + R_Vec.z);
	}
	friend _Vector3D operator-(_Vector3D L_Vec, _Vector3D R_Vec)
	{
		return _Vector3D(L_Vec.x - R_Vec.x, L_Vec.y - R_Vec.y,
			L_Vec.z - R_Vec.z);
	}
	friend _Vector3D operator/(_Vector3D L_Vec, float Constant)
	{
		return _Vector3D(L_Vec.x / Constant, L_Vec.y / Constant,
			L_Vec.z / Constant);
	}
	friend _Vector3D operator/(float Constant, _Vector3D L_Vec)
	{
		return _Vector3D(L_Vec.x / Constant, L_Vec.y / Constant,
			L_Vec.z / Constant);
	}
	friend _Vector3D operator*(_Vector3D L_Vec, float Constant)
	{
		return _Vector3D(L_Vec.x * Constant, L_Vec.y * Constant,
			L_Vec.z * Constant);
	}
	friend _Vector3D operator*(float Constant, _Vector3D L_Vec)
	{
		return _Vector3D(L_Vec.x * Constant, L_Vec.y * Constant,
			L_Vec.z * Constant);
	}
	//-----------------------------------//

	// Cout operator oveloading (Custom Print)
	friend std::ostream& operator<<(std::ostream& os, _Vector3D vec)
	{
		return os << "[" << vec.x << "," << vec.y << ","
			<< vec.z << "]";
	}


};
