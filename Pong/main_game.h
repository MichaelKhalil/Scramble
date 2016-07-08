#pragma once

#include "game_state.h"
#include "score.h"
#include "player.h"
#include "map.h"
class main_game : public tiny_state{
public:

	virtual void Initialize(sf::RenderWindow* window);
	virtual void Update(sf::RenderWindow* window);
	virtual void Render(sf::RenderWindow* window);
	virtual void Destroy(sf::RenderWindow* window);

private:

	Player* player;
	Score* score1;
	Score* highScore;
	sf::Font* font;
	Map* map;
};