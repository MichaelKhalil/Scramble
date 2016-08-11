#pragma once

#include "entity.h"
//#include "end.h"
#include "map.h"
#include "bullet.h"
#include "enemy.h"
//#include <SFML/Graphics/View.hpp>
class Player : public Entity{

public:
	Player();
	void Update(sf::RenderWindow* window, Map* map, Enemy* floater);
	int getLives();
	int getX();
	int getY();
private:
	sf::View view1;
	sf::Texture* texture;
	sf::Image* image;
	sf::Color* pixelColor;
	Map* map;
	sf::Uint8 alphaLimit;
	sf::Uint8 end;
	sf::Clock clock;
	sf::Clock fuelClock;
	Bullet *bullets[20];
	Enemy* floater;
	int bulletNum;
	bool canFire;
	bool canMove;
	//int lives;
};