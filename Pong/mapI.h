#pragma once

//#include "entity.h"
#include <SFML/Graphics.hpp>
class MapI : public sf::Image{

public:
	MapI(sf::RenderWindow* window);
	void Update();

private:
	sf::Image* mapImage;
};