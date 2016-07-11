#pragma once

#include "entity.h"
//#include <SFML/Graphics/View.hpp>
class Player : public Entity{

public:
	Player();
	void Update(sf::RenderWindow* window);
private:
	sf::View view1;
};