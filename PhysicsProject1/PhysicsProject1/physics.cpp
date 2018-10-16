// Author Ethan Fagan
// date started: 17/09/2018
//------------------------------------------------------------------------
//
//------------------------------------------------------------------------

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Insert physics here");

	sf::CircleShape shape(5);
	shape.setOrigin(5, 5);
	shape.setFillColor(sf::Color::Red);
	const int MAX_SHAPE_HEIGHT = 30;
	int timeelapsed = 0;

	sf::RectangleShape rectangle;
	rectangle.setFillColor(sf::Color::Yellow);
	rectangle.setSize(sf::Vector2f(800.0f,20.0f));


	float maxHeight = 0.0;
	float currenHeight = 0.0;
	float previousHeight = 0.0;

	float maxDistance = 0.0;
	float currentDistance = 0.0;
	float previousDistance = 0.0;

	float finalX = 0;
	float finalY = 0;

	sf::Font font;
	sf::Text timeDisplays[4];

	if (!font.loadFromFile("batmfa__.ttf"))
	{
		std::cout << "fuq" << std::endl;
	}

	for (int i = 0; i < 4; i++)
	{
		timeDisplays[i].setFont(font);
		timeDisplays[i].setFillColor(sf::Color::Magenta);
		timeDisplays[i].setScale(0.5f, 0.5f);
	}
	timeDisplays[0].setPosition(150, 50);
	timeDisplays[1].setPosition(150, 100);
	timeDisplays[2].setPosition(150, 150);
	timeDisplays[3].setPosition(150, 200);
	
	

	bool grounded = false;

	sf::Vector2f velocity(0, 0);
	sf::Vector2f position(150, 400);
	sf::Vector2f rectanglePosition(0, 410);

	float pixelsToMeters = 20;

	sf::Vector2f gravity(0.0f, 9.8f);

	float timeChange = (1.0f / 60.0f);


	sf::Clock clock;

	const float FPS = 60.0f;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	clock.restart();

	while (window.isOpen())
	{
		//read keyboard input
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				velocity = sf::Vector2f(0, 0);
				position = sf::Vector2f(150, 400);
				finalX = 0;
				finalY = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
			{
				if (position.y + 5.0f < rectanglePosition.y || velocity.y > 5.0f)
				{
					finalX--;
					finalY++;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
			{
				if (position.y + 5.0f < rectanglePosition.y || velocity.y > 5.0f)
				{
					finalX++;
					finalY--;
				}
				
			}
			if ((timeelapsed > 0 && timeelapsed < MAX_SHAPE_HEIGHT) || timeelapsed == 0)
			{
					timeelapsed++;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						velocity = sf::Vector2f(finalX, finalY);
					}

			}
	
		}
		
		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();
		//update every 60th of a second
		if (timeSinceLastUpdate > timePerFrame)
		{
			
			window.clear();
			timeelapsed++;
			// update position and velocity here using equations in lab sheet using timeChange as  timeSinceLastUpdate.asSeconds().
			timeDisplays[1].setString("Velocity will be " + std::to_string(finalX) + std::to_string(finalY));

			if (position.y + 5.0f < rectanglePosition.y || velocity.y < 5.0f)
			{

				position = position + (velocity * timeSinceLastUpdate.asSeconds()) + (0.5f * gravity * (timeSinceLastUpdate.asSeconds() * timeSinceLastUpdate.asSeconds()));
				velocity = velocity + gravity * timeSinceLastUpdate.asSeconds();
				
				timeDisplays[0].setString("Time Elapsed : " + std::to_string(timeelapsed /60) + " seconds ");
				timeDisplays[2].setString("Max height reached : " + std::to_string(maxHeight));
				timeDisplays[3].setString("Max Distance reached : " + std::to_string(maxDistance));
			}
			else
			{
				velocity.y = (-0.90 * velocity.y);
				timeelapsed = 0;
			}

			//update shape on screen
			shape.setPosition(position);
			rectangle.setPosition(rectanglePosition);	
			for (int i = 0; i < 4; i++)
			{
				window.draw(timeDisplays[i]);
			}

			window.draw(rectangle);
			window.draw(shape);

			window.display();
			timeSinceLastUpdate = sf::Time::Zero;
		}

	}

	return 0;
}
