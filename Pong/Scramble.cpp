
#include <Windows.h>
#include "game_state.h"
#include "menu.h"

game_state coreState; 
bool quitGame = false;
bool dead = false;
bool success = false;
int score = 0;
int lives = 3;
int fuel = 1000;
int lastX = 0, lastY = 0;
int lastHighScore = 0;
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Scramble");

	sf::View view1;
	coreState.SetWindow(&window);
	coreState.SetState(new menu());


	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;

		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);
		coreState.Update();
		coreState.Render();

		window.display();
		if(quitGame){
			window.close();
		}
		Sleep(5);
	}

	return 0;
}