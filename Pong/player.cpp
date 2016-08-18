
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

	this->bomb = new Bomb();
	//this->lives = lives;
	//lives = 3;
	//sf::Time time1 = clock.getElapsedTime();
	canFire = false;
	canMove = true;
	canBomb = true;
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
	sf::Time resetTime1;
	 resetTime1 = clock.getElapsedTime(); 
	 sf::Time fuelTime;
	 fuelTime = fuelClock.getElapsedTime();
}
void Player::Update(sf::RenderWindow* window, Map* map, Enemy* floater, Enemy* floater1, Enemy* sitter){
	this->floater = floater;
	this->floater1 = floater1;
	this->sitter = sitter;
	this->map = map;
	this->bomb = bomb;
	sf::Time time = clock.getElapsedTime();
	sf::Time fuelTime;
	//for fire rate
	sf::Time resetTime;
	//for fuel depletion
	//sf::Time resetTime1;


	sf::View currentView = window->getView();
	if(canMove){
	velocity.y = 3 * sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) - 3 * sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
	velocity.x = 3 * sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) - 3 * sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) + .7f;
	}
	else{
		velocity.y += .005;
		velocity.x += .001;
	}
	//velocity.x -= this->velocity.x-.7f;
	//velocity.y -= this->velocity.y-1.0f;
	//collision with top wall
	if(this->getPosition().y < 0){
		move(0, 3.0f);
	}
	//collision with bottom wall\

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
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X) && canBomb == true){
		this->bomb->setPosition(this->getPosition().x + 50, this->getPosition().y + 50);
		this->bomb->reset();
		this->bomb->standby();
		canBomb = false;
	}
	this->bomb->Update(window);

	if(image->getPixel(this->bomb->getPosition().x + this->bomb->getGlobalBounds().width/2, this->bomb->getPosition().y + this->bomb->getGlobalBounds().height/2).a == alphaLimit){
		this->bomb->standby();
		canBomb = true;
	}
	//this->bomb->move(0,10);
	
	window->draw(*this->bomb);

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
	// sf::Event event;
	 fuelTime = fuelClock.getElapsedTime();
//	while(window->pollEvent(event)){
		
		if((int)fuelTime.asSeconds() >= 2){
			fuel -= 100;
			fuelClock.restart();
			//fuelTime = fuelClock.getElapsedTime(); 
		}
	//}
	
	if(canFire == false && time.asSeconds() - resetTime.asSeconds() > .2){
		canFire = true;
	}
	for (int i = 0; i < 20; i++)
	{
	
		if(this->floater->checkCollision(this->bullets[i]) || this->floater->checkCollision(this->bomb)){
			this->floater->kill();
		}
		if(this->floater1->checkCollision(this->bullets[i]) || this->floater1->checkCollision(this->bomb)){
			this->floater1->kill();
		}
		if(this->sitter->checkCollision(this->bullets[i]) || this->sitter->checkCollision(this->bomb)){
			this->sitter->kill();
		}
	}
	
	this->sitter->excite(this->getPosition().x + this->getGlobalBounds().width/2, this->getPosition().y+this->getGlobalBounds().height/2);

	//this->bullet.move(5,0);
	//window->draw(bullet);
	//collision with the map

	if(fuel <= 0){
		canMove = false;
	}

	if(this->checkCollision(this->map) &&  image->getPixel(this->getPosition().x + this->getGlobalBounds().width/2, this->getPosition().y+this->getGlobalBounds().height/2).a == alphaLimit){
		//std::cout << "Success";
		lives -= 1;
		lastX = this->getPosition().x; lastY = this->getPosition().y;
		dead = true;
	}
	

	if(this->checkCollision(this->floater) ||  this->checkCollision(this->floater1) || this->checkCollision(this->sitter)){
		lives -= 1;
		lastX = this->getPosition().x; lastY = this->getPosition().y;
		dead = true;
	}



	if(image->getPixel(this->getPosition().x + (currentView.getCenter().x +399) - this->getPosition().x, 590).a <= end+10){
		//coreState.SetState(new end());	
		//this->lives -=1;
		//lastX = window->getSize().x/2; lastY = 50;
		success = true;
		//dead = true;
	}

	Entity::Update();
	if(bulletNum >= 20){
		bulletNum = 0;
	}
	
}
/*
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
}*/