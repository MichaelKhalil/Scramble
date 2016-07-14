#pragma once

#include "entity.h"
#include <SFML/Graphics.hpp>
class Map : public Entity{

public:
	Map(sf::RenderWindow* window);
	void Update();

private:
};