
#include "map.h"
#include <iostream>
#include <SFML\Graphics.hpp>
Map::Map(sf::RenderWindow* window){
	this->Load("map.png");
	//this->velocity.x -= 1;
	//this->setColor(sf::Color::Blue);
	//this->setColor(sf::Color(0,255,0,255));
}
void Map::Update(){
	//std::cout << this->getColor().r;
	//Entity::Update();
	
}
