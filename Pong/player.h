#pragma once

#include "entity.h"
//#include "end.h"
#include "map.h"
#include "bullet.h"
//#include <SFML/Graphics/View.hpp>
class Player : public Entity{

public:
	Player();
	void Update(sf::RenderWindow* window, Map* map);
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
	Bullet *bullets[20];
	int bulletNum;
	bool canFire;
	//int lives;
};