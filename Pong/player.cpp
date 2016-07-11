
#include "player.h"
#include <iostream>


Player::Player(){
	this->Load("ship.png");
	

}
void Player::Update(sf::RenderWindow* window){
	
	sf::View currentView = window->getView();

	velocity.y = 3 * sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) - 3 * sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
	velocity.x = 3 * sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) - 3 * sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) + .7f;
	//velocity.x -= this->velocity.x-.7f;
	//velocity.y -= this->velocity.y-1.0f;

	if(this->getPosition().y < 0){
		move(0, 3.0f);
	}
	if(this->getPosition().y + this->getGlobalBounds().height > 600){
		move(0, -3.0f);
	}

	if(this->getPosition().x < currentView.getCenter().x - window->getSize().x/2){
		move(3.0f, 0);
	}
	if(this->getPosition().x + this->getGlobalBounds().width > currentView.getCenter().x + window->getSize().x/2){
		this->move(-3.0f, 0);
	}
	Entity::Update();
}
