#include "Application.h"
#include "Player.h"
int main() {
	/*sf::RenderWindow window(sf::VideoMode(1800, 1000), "Test");
	window.setFramerateLimit(100);
	window.setKeyRepeatEnabled(true);
	Player player;

	while (window.isOpen())
	{
		sf::Event _event;
		while (window.pollEvent(_event))
		{
			switch (_event.type)
			{
			case sf::Event::Closed:
					window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				player.moveUp();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				player.moveLeft();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				player.moveDown();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				player.moveRight();
			}
		}
		window.clear();
		player.Draw(window);
		window.display();
	
		
	}*/




	Application app;
	while (app.GetWindow()->IsOpen()) {
		app.Update();
		app.Render();
	}
	return 0;
}