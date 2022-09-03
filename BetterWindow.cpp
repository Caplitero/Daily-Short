


#include <SFML/Graphics.hpp>
#include <iostream>

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
		sf::Uint32 style = sf::Style::Default
		, const sf::ContextSettings& \
		settings = sf::ContextSettings()) 
	{
		window = new sf::RenderWindow(mode, 
			title, style, settings);
		
		
	}
	App_Structure(sf::WindowHandle handle, 
		const sf::ContextSettings& settings \
		= sf::ContextSettings()) 
	{
		window = new sf::RenderWindow(handle, settings);
		
		
	}
	
	

	// Start the main loop of the app
	void Start() 
	{
		onCreate();
		while (window->isOpen())
		{
			Delta_time = (APP_Clock.getElapsedTime()\
				.asMilliseconds() -
				LastFrame_time+0.00001)/1000;
			LastFrame_time = APP_Clock.getElapsedTime()\
				.asMilliseconds();

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
		
		sf::RectangleShape* item = new sf::RectangleShape\
			(sf::Vector2f(100, 100));
		Drawable_Layers.push_back(item);
	}

public :
	using App_Structure::App_Structure;
	
};

int main()
{
	
	App app(sf::VideoMode(640, 840), "SFML GAME");
	app.Start();
	
	


	return 0;
}