#pragma once

#include "game_state.h"
#include "score.h"
#include "player.h"
#include "map.h"
#include "bullet.h"
#include "enemy.h"
class main_game : public tiny_state{
public:

	virtual void Initialize(sf::RenderWindow* window);
	virtual void Update(sf::RenderWindow* window);
	virtual void Render(sf::RenderWindow* window);
	virtual void Destroy(sf::RenderWindow* window);

private:
	sf::View view1;
	Player* player;
	int lastHighScore;
	sf::Font* font;
	Map* map;
	Bullet* bullet;
	Score* score1;
	Score* highScore;
	sf::Text* lifeText;
	Score* lifeNum;
	Score* fuelNum;

	Enemy* floater;
	Enemy* floater1;
	Enemy* floater2;
	Enemy* floater3;

	Enemy* sitter;
	Enemy* sitter1;
	Enemy* sitter2;
	Enemy* sitter3;
	Enemy* sitter4;
	Enemy* sitter5;
	Enemy* sitter6;
	Enemy* sitter7;
};