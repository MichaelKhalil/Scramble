#pragma once

#include "entity.h"
#include "map.h"
#include "game_state.h"
#include "score.h"
//#include "player.h"
//#include "bullet.h"
//#include <SFML/Graphics/View.hpp>
class Enemy : public Entity{

public:
	Enemy(int enemyType, int dir, bool enemyDead);
	void Update(sf::RenderWindow* window, Map* map);
	void kill();
private:
	Map* map;
	sf::Texture* texture;
	sf::Image* image;
	Score* score1;
	sf::Font* font;
	sf::Uint8 alphaLimit;
	//Bullet* bullet;
	int enemyType;
	int dir;
	bool enemyDead;
};