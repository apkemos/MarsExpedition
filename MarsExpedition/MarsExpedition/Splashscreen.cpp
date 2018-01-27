#include "Stdafx.h"
#include "Sim.h"
#include "SplashScreen.h"
#include <SFML/Window/Event.hpp>
void SplashScreen::Show(sf::RenderWindow & renderWindow)
{
	sf::Texture image;
	if(image.loadFromFile("images/mars_exp.png") != true)
	{
		return;
	}

	sf::Sprite sprite(image);

	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	while(true)
	{
		while(renderWindow.pollEvent(event))
		{
            if (event.type == sf::Event::Closed){Sim::getWindow().close();}
			if(event.type == sf::Event::KeyPressed
				|| event.type == sf::Event::MouseButtonPressed)
			{
			    Sim::Map_Initialization();
				return;
			}
		}
	}
}
