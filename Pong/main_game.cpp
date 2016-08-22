#include "main_game.h"
#include "menu.h"
#include "end.h"
#include <iostream>
#include <SFML\Graphics.hpp>
void main_game::Initialize(sf::RenderWindow* window){
	//load font
	this->font = new sf::Font();
	this->font->loadFromFile("font.ttf");

	//init the scoreboard above the game
	this->score1 = new Score(*font, 64U);
	this->score1->setPosition(window->getPosition().x+50, 0);
	this->highScore = new Score(*font, 64U);
	this->highScore->setPosition(window->getSize().x/2, 0);
	//text for number of lives
	this->lifeText = new sf::Text("Lives:", *this->font, 50U);
	this->lifeText->setPosition(window->getPosition().x-150, 10);
	//number of lives
	this->lifeNum = new Score(*font, 50U);
	this->lifeNum->setPosition(window->getPosition().x-150, 10);
	//number of fuel, changes color default green
	this->fuelNum = new Score(*font, 50U);
	this->fuelNum->setPosition(window->getPosition().x - 350, window->getPosition().y - 150);
	this->fuelNum->setColor(sf::Color::Green);


	//initialize enemies
	this->floater = new Enemy(0, 1, false);
	this->floater->setPosition(1020,400);
	this->floater1 = new Enemy(0, 1, false);
	this->floater1->setPosition(1160,300);
	this->floater2 = new Enemy(0, 1, false);
	this->floater2->setPosition(2095, 300);
	this->floater3 = new Enemy(0, 1, false);
	this->floater3->setPosition(880, 100);

	this->sitter = new Enemy(1, 1, false);
	this->sitter->setPosition(1600,240);
	this->sitter1 = new Enemy(1, 1, false);
	this->sitter1->setPosition(2000,310);
	this->sitter2 = new Enemy(1, 1, false);
	this->sitter2->setPosition(730,310);
	this->sitter3 = new Enemy(1, 1, false);
	this->sitter3->setPosition(2463,170);
	this->sitter4 = new Enemy(1, 1, false);
	this->sitter4->setPosition(2540,240);
	this->sitter5 = new Enemy(1, 1, false);
	this->sitter5->setPosition(2650,310);
	this->sitter6 = new Enemy(1, 1, false);
	this->sitter6->setPosition(3000,380);
	this->sitter7 = new Enemy(1, 1, false);
	this->sitter7->setPosition(3500,240);

	this->view1.setSize(800,600);
	this->player = new Player();
	//handle where player spawns based on lives
	if(lives == 3){
	this->player->setPosition(window->getSize().x/2, 50);
	}
	if(lives < 3){
		player->setPosition(lastX-60, lastY-60);
		if(player->getPosition().x < 0 || player->getPosition().y < 0){
			player->setPosition(lastX, 0);
		}
	}
	
	this->view1.setCenter(this->player->getPosition().x, window->getSize().y/2);
	this->map = new Map(window);
	sf::View  defView = window->getView();
}
//update objects
void main_game::Update(sf::RenderWindow* window){
	view1.move(.9,0);
	score1->IncrementScore();
	score = this->score1->value;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)){
		Bullet *bullet = new Bullet();
		bullet->setPosition(this->player->getPosition().x, this->player->getPosition().y);
		bullet->Update(window);
	}
	
	this->highScore->setScore(score1->value);
	this->score1->setPosition(this->view1.getCenter().x+150, 0);
	this->lifeText->setPosition(this->view1.getCenter().x-150, 10);
	this->lifeNum->setPosition(this->view1.getCenter().x- 10, 10);
	this->fuelNum->setPosition(this->view1.getCenter().x - 300, 10);
	this->lifeNum->setScore(lives);
	this->fuelNum->setScore(fuel);

	window->setView(view1);
	
	this->map->Update();
	this->player->Update(window, map, floater, floater1, floater2, floater3, sitter, sitter1, sitter2, sitter3, sitter4, sitter5, sitter6, sitter7);
	

	this->floater->Update(window, map);
	this->floater1->Update(window, map);
	this->floater2->Update(window, map);
	this->floater3->Update(window, map);

	this->sitter->Update(window, map);
	this->sitter1->Update(window, map);
	this->sitter2->Update(window, map);
	this->sitter3->Update(window, map);
	this->sitter4->Update(window, map);
	this->sitter5->Update(window, map);
	this->sitter6->Update(window, map);
	this->sitter7->Update(window, map);

	this->score1->value = score;
	this->score1->Update();
	this->lifeNum->Update();
	this->fuelNum->Update();
	this->highScore->Update();
	//change fuel color based on remaining fuel
	if(fuel > 600){
		this->fuelNum->setColor(sf::Color::Green);
	}
	if(fuel < 600 && fuel > 300){
		this->fuelNum->setColor(sf::Color::Yellow);
	}

	if(fuel < 300){
		this->fuelNum->setColor(sf::Color::Red);
	}
	//if the player dies
	if(dead){
		fuel = 1000;
		if(lives == 3)
			score = this->score1->value;
		else
			score += this->score1->value;
		
		dead = false;
		window->setView(window->getDefaultView());
		coreState.SetState(new end());
	}
	//if the player wins
	if(success){

		lastX = window->getSize().x/2; lastY = 50;
		fuel = 1000;
		lives = 3;
		success = false;
		window->setView(window->getDefaultView());
		coreState.SetState(new end());
		score += this->score1->value;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
		window->setView(window->getDefaultView());
		coreState.SetState(new menu());
	}
	

}
//draw objects
void main_game::Render(sf::RenderWindow* window){
	window->draw(*this->map);
	window->draw(*this->lifeText);
	window->draw(*this->lifeNum);
	window->draw(*this->fuelNum);
	window->draw(*this->floater);
	window->draw(*this->floater1);
	window->draw(*this->floater2);
	window->draw(*this->floater3);
	window->draw(*this->sitter);
	window->draw(*this->sitter1);
	window->draw(*this->sitter2);
	window->draw(*this->sitter3);
	window->draw(*this->sitter4);
	window->draw(*this->sitter5);
	window->draw(*this->sitter6);
	window->draw(*this->sitter7);
	//window->draw(*this->bullet);
	//window->draw(*this->map);
	window->draw(*this->score1);
	//window->draw(*this->highScore);
	window->draw(*this->player);
	


} 
//cleanup
void main_game::Destroy(sf::RenderWindow* window){
	delete this->score1;
	delete this->highScore;
	delete this->player;
	delete this->map;
	delete this->lifeNum;
//	delete this->score1;
	delete this->floater;
	delete this->floater1;
	delete this->floater2;
	delete this->floater3;
	delete this->sitter;
	delete this->sitter1;
	delete this->sitter2;
	delete this->sitter3;
	delete this->sitter4;
	delete this->sitter5;
	delete this->sitter6;
	delete this->sitter7;
	delete this->fuelNum;
	delete this->lifeText;

}

