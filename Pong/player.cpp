
#include "player.h"
#include "end.h"
#include "menu.h"
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Image.hpp>
#include <iostream>
#include <string>
//using namespace std;
Player::Player(){
	this->Load("ship.png");
	//this->map = map; 
	this->alphaLimit = 255;
	this->pixelColor = pixelColor;
	//this->mapImage = mapImage;
	this->texture = new sf::Texture();
	this->image = new sf::Image();
	//texture->loadFromFile("Graphics\map.png");
	//this->mapImage->
	this->image->loadFromFile("Graphics/map.png");
	
}
void Player::Update(sf::RenderWindow* window, Map* map){
	this->map = map;
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


	//collision with the map
	if(this->checkCollision(this->map) &&  image->getPixel(this->getPosition().x + this->getGlobalBounds().width/2, this->getPosition().y+this->getGlobalBounds().height/2).a == alphaLimit){
		//std::cout << "Success";

		dead = true;
		
	}
	Entity::Update();
}
