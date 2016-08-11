
#include "enemy.h"

#include <iostream>
#include <string>
#include <Windows.h>
//using namespace std;
Enemy::Enemy(int enemyType, int dir, bool enemyDead){
	this->Load("floater.png");
	this->image = new sf::Image();
	this->alphaLimit = 255;
	this->image->loadFromFile("Graphics/map.png");
	//types:
	//0 -> floaters
	//1 -> sitters
	this->dir = dir;
	this->enemyDead = false;
	this->enemyType = enemyType;

	this->font = new sf::Font();
	this->font->loadFromFile("font.ttf");
	this->score1 = new Score(*font, 64U);
}
void Enemy::Update(sf::RenderWindow* window, Map* map){
	this->map = map;
	if(this->enemyType == 0){
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
	//if(this->checkCollision(this->map)){
	//		this->enemyDead = true;
	//	}

		if(enemyDead){
			this->setPosition(-100,-100);
			this->dir = 2;
		}
		
}

void Enemy::kill(){
	//function seems to call twice, reason is unsure, fuel increments halved to accomodate
	//floater

	if(this->enemyType == 0){
		fuel += 200;
		score += 1000;
	}
//	std::cout << "\n";
	//std::cout << score;

	this->enemyDead = true;
}

