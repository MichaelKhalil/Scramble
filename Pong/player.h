#pragma once

#include "entity.h"
//#include "end.h"
#include "map.h"
//#include <SFML/Graphics/View.hpp>
class Player : public Entity{

public:
	Player();
	void Update(sf::RenderWindow* window, Map* map);
private:
	sf::View view1;
	sf::Texture* texture;
	sf::Image* image;
	sf::Color* pixelColor;
	Map* map;
	sf::Uint8 alphaLimit;
};