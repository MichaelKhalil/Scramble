
#include "player.h"
#include "end.h"
#include "menu.h"
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Image.hpp>
#include <SFML\System\Clock.hpp>
#include <iostream>
#include <string>
#include <Windows.h>
//using namespace std;
Player::Player(){
	this->Load("ship.png");
	//this->map = map; 
	this->alphaLimit = 255;
	this->end = 0;
	this->pixelColor = pixelColor;
	//this->mapImage = mapImage;
	this->texture = new sf::Texture();
	this->image = new sf::Image();
	//this->lives = lives;
	//lives = 3;
	//sf::Time time1 = clock.getElapsedTime();
	canFire = false;
	//texture->loadFromFile("Graphics\map.png");
	//this->mapImage->
	bulletNum = 0;
	if(lives <= 0){
		score = 0;
	}
	if(lives <= 0){
		lives = 3;
		lastX = 400; lastY = 50;
	}
	this->image->loadFromFile("Graphics/map.png");
	//Bullet *bullet = new Bullet();
	
	for (int i = 0; i < 20; i++)
	{
		bullets[i] = new Bullet();
	}

}
void Player::Update(sf::RenderWindow* window, Map* map){
	this->map = map;

	sf::Time time = clock.getElapsedTime();
	sf::Time resetTime;
	


	sf::View currentView = window->getView();
	velocity.y = 3 * sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) - 3 * sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
	velocity.x = 3 * sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) - 3 * sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) + .7f;
	//velocity.x -= this->velocity.x-.7f;
	//velocity.y -= this->velocity.y-1.0f;
	//collision with top wall
	if(this->getPosition().y < 0){
		move(0, 3.0f);
	}
	//collision with bottom wall
	if(this->getPosition().y + this->getGlobalBounds().height > 600){
		move(0, -3.0f);
	}
	//collision with left wall
	if(this->getPosition().x < currentView.getCenter().x - window->getSize().x/2){
		move(3.0f, 0);
	}
	//collision with right wall
	if(this->getPosition().x + this->getGlobalBounds().width > currentView.getCenter().x + window->getSize().x/2){
		this->move(-3.0f, 0);
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) && canFire == true){
		Bullet *temp = new Bullet();
		bullets[bulletNum] = temp;
		bullets[bulletNum]->setPosition(this->getPosition().x + this->getGlobalBounds().width/2, this->getPosition().y+this->getGlobalBounds().height/2);
		bulletNum++;
		canFire = false;
		clock.restart();
		resetTime = clock.getElapsedTime();
	}
	for (int i = 0; i < 20; i++)
	{
		bullets[i]->move(5,0);
		window->draw(*bullets[i]);
	}

	if(canFire == false && time.asSeconds() - resetTime.asSeconds() > .2){
		canFire = true;
	}
	//this->bullet.move(5,0);
	//window->draw(bullet);
	//collision with the map
	if(this->checkCollision(this->map) &&  image->getPixel(this->getPosition().x + this->getGlobalBounds().width/2, this->getPosition().y+this->getGlobalBounds().height/2).a == alphaLimit){
		//std::cout << "Success";
		lives -= 1;
		lastX = this->getPosition().x; lastY = this->getPosition().y;
		dead = true;
		
	}
		
	if(image->getPixel(this->getPosition().x + (currentView.getCenter().x +399) - this->getPosition().x, 590).a <= end+10){
		//coreState.SetState(new end());	
		//this->lives -=1;
		dead = true;
	}
	Entity::Update();
	if(bulletNum >= 20){
		bulletNum = 0;
	}
}

int Player::getLives(){
	std::cout << lives;
	return lives;
}
int Player::getX(){
	std::cout << this->getPosition().x;
	return this->getPosition().x;
}
int Player::getY(){
	std::cout << this->getPosition().y;
	return this->getPosition().y;
}