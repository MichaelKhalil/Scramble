#pragma once

#include "game_state.h"
#include "score.h"
#include "player.h"
#include "map.h"
#include "mapI.h"
class main_game : public tiny_state{
public:

	virtual void Initialize(sf::RenderWindow* window);
	virtual void Update(sf::RenderWindow* window);
	virtual void Render(sf::RenderWindow* window);
	virtual void Destroy(sf::RenderWindow* window);

private:
	sf::View view1;
	Player* player;
	Score* score1;
	Score* highScore;
	int lastHighScore;
	sf::Font* font;
	Map* map;
	MapI* mapI;

};