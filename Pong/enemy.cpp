
#include "enemy.h"

#include <iostream>
#include <string>
#include <Windows.h>
//using namespace std;
Enemy::Enemy(int enemyType, int dir, bool enemyDead){

	this->image = new sf::Image();
	this->alphaLimit = 255;
	this->image->loadFromFile("Graphics/map.png");

	this->dir = dir;
	this->enemyDead = false;
	this->enemyType = enemyType;

	//enemy types:
	//0 -> floaters
	//1 -> sitters
	if(this->enemyType == 0)
		this->Load("floater.png");
	if(this->enemyType == 1)
		this->Load("sitter.png");

	this->font = new sf::Font();
	this->font->loadFromFile("font.ttf");
	this->score1 = new Score(*font, 64U);
	this->buffer = new sf::SoundBuffer();
	this->sound = new sf::Sound(*this->buffer);
	this->sound->setBuffer(*this->buffer);
}
void Enemy::Update(sf::RenderWindow* window, Map* map){
	this->map = map;
	//floater
	if(this->enemyType == 0){
		//move up until end of screen, move down until hits the map
		if(this->dir == 0){
			//velocity.y -= .005;
			this->setPosition(this->getPosition().x, this->getPosition().y-3);
		}
		if(this->dir == 1){
			this->setPosition(this->getPosition().x, this->getPosition().y+3);
		}
		if(this->getPosition().y <= 0){
			this->dir = 1;
		}
		if(this->checkCollision(this->map) &&  image->getPixel(this->getPosition().x + this->getGlobalBounds().width, this->getPosition().y+this->getGlobalBounds().height).a == alphaLimit){
			//velocity.y = 0;
			this->dir = 0;
		}
		
	}

	Entity::Update();
	//dead
		if(this->enemyDead){
			this->setPosition(-100,-100);
			this->dir = 2;
		}
		
}

void Enemy::kill(){
	
	//floater
	if(this->enemyType == 0){
		fuel += 200;
		score += 1000;
	}
	//sitter
	if(this->enemyType == 1){
		fuel += 400;
		score += 2000;
	}

	this->buffer->loadFromFile("Sounds/kill.flac");
	this->sound->play();
	this->enemyDead = true;
}
//sitters move to player when you approach
void Enemy::excite(int playerX, int playerY){
	if(this->getPosition().x - playerX < 300 &&  this->getPosition().x - playerX > - 300 && this->getPosition().y - playerY < 200 &&  this->getPosition().y - playerY > - 200){
		if(this->getPosition().x - playerX > 0){
			this->move(-1,0);
		}
		else{
			this->move(1,0);
		}
		if(this->getPosition().y - playerY > 0){
			this->move(0,-1);
		}
		else{
			this->move(0,1);
		}
		this->buffer->loadFromFile("Sounds/takeoff.wav");
		this->sound->play();
	}
}