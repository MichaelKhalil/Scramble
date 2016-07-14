
#include "mapI.h"
#include <iostream>
#include <SFML\Graphics.hpp>
MapI::MapI(sf::RenderWindow* window){
	//this->Load("map.png");
	//this->velocity.x -= 1;
	//this->setColor(sf::Color::Blue);
	//this->setColor(sf::Color(0,255,0,255));
	this->mapImage->loadFromFile("Graphics/map.png");
}
void MapI::Update(){
	//std::cout << this->getColor().r;
	//Entity::Update();
	
}
