
#include "bullet.h"
#include "player.h"
#include <iostream>
#include <SFML\Graphics.hpp>

Bullet::Bullet(){
	this->Load("bullet.png");
	this->setPosition(-10,-10);
}
void Bullet::Update(sf::RenderWindow* window){
	//this->velocity.x +=5;

	Entity::Update();
		
}

