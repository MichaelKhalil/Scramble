#include "end.h"
#include "main_game.h"
#include "menu.h"
#include <iostream>
void end::Initialize(sf::RenderWindow* window){

	//Read font from folder
	this->font = new sf::Font();
	this->font->loadFromFile("font.ttf");


	this->back = new sf::Text("Game Over", *this->font, 100U);
	back->setColor(sf::Color::Red);
	this->back->setOrigin(this->back->getGlobalBounds().width/2, this->back->getGlobalBounds().height/2);
	this->back->setPosition(400, 100);

	this->yourScore = new sf::Text("Your Score:", *this->font, 64U);
	yourScore->setColor(sf::Color::White);
	this->yourScore->setOrigin(this->yourScore->getGlobalBounds().width/2, this->yourScore->getGlobalBounds().height/2);
	this->yourScore->setPosition(300, 250);

	this->playerScore = new Score(*font, 64U);
	this->playerScore->setPosition(450, 225);
	this->playerScore->setScore(score);

	this->bestScore = new sf::Text("Best Score:", *this->font, 64U);
	bestScore->setColor(sf::Color::White);
	this->bestScore->setOrigin(this->bestScore->getGlobalBounds().width/2, this->bestScore->getGlobalBounds().height/2);
	this->bestScore->setPosition(300, 350);

	if(score > lastHighScore){
		lastHighScore = score;
	}

	this->highScore = new Score(*font, 64U);
	this->highScore->setPosition(450, 325);
	this->highScore->setScore(lastHighScore);


}
void end::Update(sf::RenderWindow* window){
	playerScore->Update();
	highScore->Update();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
		window->setView(window->getDefaultView());
		coreState.SetState(new menu());
	}
}
void end::Render(sf::RenderWindow* window){
	window->draw(*this->playerScore);
	window->draw(*this->back);
	window->draw(*this->yourScore);
	window->draw(*this->bestScore);
	window->draw(*this->highScore);
	//handle between changing states, either set state to game or signify quit	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)){
			coreState.SetState(new main_game());
	}
}
//cleanup
void end::Destroy(sf::RenderWindow* window){
	delete this->font;
	delete this->back;
	delete this->bestScore;
	delete this->highScore;
	delete this->playerScore;
	delete this->yourScore;
}
