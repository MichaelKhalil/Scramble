#pragma once

#include "game_state.h"
#include "score.h"
class end : public tiny_state{
public:

	virtual void Initialize(sf::RenderWindow* window);
	virtual void Update(sf::RenderWindow* window);
	virtual void Render(sf::RenderWindow* window);
	virtual void Destroy(sf::RenderWindow* window);
	
	
private:
	sf::Font* font;
	sf::Text* back;
	sf::Text* yourScore;
	sf::Text* bestScore;
	Score* playerScore;
	Score* highScore;
};