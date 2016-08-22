
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

	this->buffer = new sf::SoundBuffer();
	this->sound = new sf::Sound(*this->buffer);
	this->sound->setBuffer(*this->buffer);
}
void Player::Update(sf::RenderWindow* window, Map* map, Enemy* floater, Enemy* floater1, Enemy* floater2, Enemy* floater3, Enemy* sitter, Enemy* sitter1, Enemy* sitter2, Enemy* sitter3, Enemy* sitter4, Enemy* sitter5, Enemy* sitter6, Enemy* sitter7){
	this->floater = floater;
	this->floater1 = floater1;
	this->floater2 = floater2;
	this->floater3 = floater3;
	this->sitter = sitter;
	this->sitter1 = sitter1;
	this->sitter2 = sitter2;
	this->sitter3 = sitter3;
	this->sitter4 = sitter4;
	this->sitter5 = sitter5;
	this->sitter6 = sitter6;
	this->sitter7 = sitter7;
	this->map = map;
	this->bomb = bomb;
	sf::Time time = clock.getElapsedTime();
	sf::Time fuelTime;
	//for fire rate
	sf::Time resetTime;
	sf::View currentView = window->getView();
	//movement
	if(canMove){
	velocity.y = 3 * sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) - 3 * sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
	velocity.x = 3 * sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) - 3 * sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) + .9f;
	}
	else{
		velocity.y += .005;
		velocity.x += .001;
	}

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
	//bombs
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X) && canBomb == true){
		this->bomb->setPosition(this->getPosition().x + this->getGlobalBounds().width, this->getPosition().y + this->getGlobalBounds().height/2);
		this->bomb->reset();
		this->bomb->standby();
		canBomb = false;
		this->buffer->loadFromFile("Sounds/break.wav");
		this->sound->play();
	}
	this->bomb->Update(window);
	//bombs reseting
	if(image->getPixel(this->bomb->getPosition().x + this->bomb->getGlobalBounds().width/2, this->bomb->getPosition().y + this->bomb->getGlobalBounds().height/2).a == alphaLimit){
		this->bomb->standby();
		canBomb = true;
	}	
	window->draw(*this->bomb);

	//bullets
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) && canFire == true){
		Bullet *temp = new Bullet();
		bullets[bulletNum] = temp;
		bullets[bulletNum]->setPosition(this->getPosition().x + this->getGlobalBounds().width/2, this->getPosition().y+this->getGlobalBounds().height/2);
		bulletNum++;
		canFire = false;
		clock.restart();
	
		resetTime = clock.getElapsedTime();
		this->buffer->loadFromFile("Sounds/blip.wav");
		this->sound->play();
	}
	for (int i = 0; i < 20; i++)
	{
		bullets[i]->move(5,0);
		window->draw(*bullets[i]);
	}
	if(bulletNum >= 20){
		bulletNum = 0;
	}
	if(canFire == false && time.asSeconds() - resetTime.asSeconds() > .2){
		canFire = true;
	}
	 fuelTime = fuelClock.getElapsedTime();
	 //fuel depletion every second
		if((int)fuelTime.asSeconds() >= 1){
			fuel -= 100;
			fuelClock.restart();
			
		}
	//lock controls if there is no fuel
	if(fuel <= 0){
		canMove = false;
	}
	
	//cehck enemy collision with all bullets and bombs
	for (int i = 0; i < 20; i++)
	{
	
		if(this->floater->checkCollision(this->bullets[i]) || this->floater->checkCollision(this->bomb)){
			this->floater->kill();
		}
		if(this->floater1->checkCollision(this->bullets[i]) || this->floater1->checkCollision(this->bomb)){
			this->floater1->kill();
		}
		if(this->floater2->checkCollision(this->bullets[i]) || this->floater2->checkCollision(this->bomb)){
			this->floater2->kill();
		}
		if(this->floater3->checkCollision(this->bullets[i]) || this->floater3->checkCollision(this->bomb)){
			this->floater3->kill();
		}
		if(this->sitter->checkCollision(this->bullets[i]) || this->sitter->checkCollision(this->bomb)){
			this->sitter->kill();
		}
		if(this->sitter1->checkCollision(this->bullets[i]) || this->sitter1->checkCollision(this->bomb)){
			this->sitter1->kill();
		}
		if(this->sitter2->checkCollision(this->bullets[i]) || this->sitter2->checkCollision(this->bomb)){
			this->sitter2->kill();
		}
		if(this->sitter3->checkCollision(this->bullets[i]) || this->sitter3->checkCollision(this->bomb)){
			this->sitter3->kill();
		}
		if(this->sitter4->checkCollision(this->bullets[i]) || this->sitter4->checkCollision(this->bomb)){
			this->sitter4->kill();
		}
		if(this->sitter5->checkCollision(this->bullets[i]) || this->sitter5->checkCollision(this->bomb)){
			this->sitter5->kill();
		}
		if(this->sitter6->checkCollision(this->bullets[i]) || this->sitter6->checkCollision(this->bomb)){
			this->sitter6->kill();
		}
		if(this->sitter7->checkCollision(this->bullets[i]) || this->sitter7->checkCollision(this->bomb)){
			this->sitter7->kill();
		}
	}
	//sitters move when player is near
	this->sitter->excite(this->getPosition().x + this->getGlobalBounds().width/2, this->getPosition().y+this->getGlobalBounds().height/2);
	this->sitter1->excite(this->getPosition().x + this->getGlobalBounds().width/2, this->getPosition().y+this->getGlobalBounds().height/2);
	this->sitter2->excite(this->getPosition().x + this->getGlobalBounds().width/2, this->getPosition().y+this->getGlobalBounds().height/2);
	this->sitter3->excite(this->getPosition().x + this->getGlobalBounds().width/2, this->getPosition().y+this->getGlobalBounds().height/2);
	this->sitter4->excite(this->getPosition().x + this->getGlobalBounds().width/2, this->getPosition().y+this->getGlobalBounds().height/2);
	this->sitter5->excite(this->getPosition().x + this->getGlobalBounds().width/2, this->getPosition().y+this->getGlobalBounds().height/2);
	this->sitter6->excite(this->getPosition().x + this->getGlobalBounds().width/2, this->getPosition().y+this->getGlobalBounds().height/2);
	this->sitter7->excite(this->getPosition().x + this->getGlobalBounds().width/2, this->getPosition().y+this->getGlobalBounds().height/2);

	//if player hits the map player dies
	if(this->checkCollision(this->map) &&  image->getPixel(this->getPosition().x + this->getGlobalBounds().width/2, this->getPosition().y+this->getGlobalBounds().height/2).a == alphaLimit){
		this->death();
	}
	//if player hits enemy, dies
	if(this->checkCollision(this->floater) ||  this->checkCollision(this->floater1) || this->checkCollision(this->floater2) || this->checkCollision(this->floater3) || this->checkCollision(this->sitter) || this->checkCollision(this->sitter1) || this->checkCollision(this->sitter2) || this->checkCollision(this->sitter3) || this->checkCollision(this->sitter4) || this->checkCollision(this->sitter5) || this->checkCollision(this->sitter6) || this->checkCollision(this->sitter7)){
		this->death();
	}


	//if player reaches end of the image of the map
	if(image->getPixel(this->getPosition().x + (currentView.getCenter().x +399) - this->getPosition().x, 590).a <= end+10){
		this->buffer->loadFromFile("Sounds/success.wav");
		this->sound->play();
		success = true;
	}

	Entity::Update();
}
//players death
void Player::death(){
	this->buffer->loadFromFile("Sounds/crash.wav");
	this->sound->play();
	lives -= 1;
	lastX = this->getPosition().x;
	lastY = this->getPosition().y;
	dead = true;
}
