#pragma once

#include "entity.h"
class Bullet : public Entity{

public:
	Bullet();
	void Update(sf::RenderWindow* window);
	
private:
	sf::Texture* texture;

};