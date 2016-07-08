#include "main_game.h"
#include "menu.h"

void main_game::Initialize(sf::RenderWindow* window){
	//load font
	this->font = new sf::Font();
	this->font->loadFromFile("font.ttf");

	//init the scoreboard above the game
	this->score1 = new Score(*font, 64U);
	this->score1->setPosition(window->getSize().x/4, 0);
	this->highScore = new Score(*font, 64U);
	this->highScore->setPosition(window->getSize().x/2, 0);

	this->player = new Player();
	this->player->setPosition(window->getSize().x/2, window->getSize().y/2);

	this->map = new Map();
}
//update objects
void main_game::Update(sf::RenderWindow* window){
	this->map->Update();
	this->player->Update();
	this->score1->Update();
	this->highScore->Update();
	//escape sends back to main menu, resets score
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
		coreState.SetState(new menu());
	}	
}
//draw objects
void main_game::Render(sf::RenderWindow* window){
	window->draw(*this->map);
	window->draw(*this->score1);
	window->draw(*this->highScore);
	window->draw(*this->player);
	

} 
//cleanup
void main_game::Destroy(sf::RenderWindow* window){
	delete this->score1;
	delete this->highScore;
	delete this->player;
	delete this->map;
}

