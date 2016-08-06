#pragma once

#include "entity.h"
#include "map.h"
#include "bullet.h"
//#include <SFML/Graphics/View.hpp>
class Enemy : public Entity{

public:
	Enemy(int enemyType, int dir, bool enemyDead);
	void Update(sf::RenderWindow* windowz, Map* map);

private:
	Map* map;
	sf::Texture* texture;
	sf::Image* image;
	sf::Uint8 alphaLimit;
	Bullet* bullet;
	int enemyType;
	int dir;
	bool enemyDead;
};