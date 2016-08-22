
#include "bomb.h"
#include "player.h"
#include <iostream>
#include <SFML\Graphics.hpp>

Bomb::Bomb(){
	this->Load("bomb.png");
	setPosition(0,0);
	//velocity.x = 2.5f;
	//velocity.y = 0.0f;
	wait = false;
}
//bomb movement
void Bomb::Update(sf::RenderWindow* window){
	if(wait == true){
		velocity.x = 2.5f;
		velocity.y += 0.1f;
	}
	else{
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		setPosition(0,0);
	}
	Entity::Update();
}

void Bomb::reset(){
	velocity.x = 0.0f;
	velocity.y = 0.0f;
}
//wait until bomb hits something before being able to shoot again
void Bomb::standby(){
	wait = !wait;
}