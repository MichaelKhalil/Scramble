#pragma once

#include "entity.h"


class Bomb : public Entity{

public:
	Bomb();
	void Update(sf::RenderWindow* window);
	void reset();
	void standby();
	
private:
	sf::Texture* texture;
	bool wait;

};