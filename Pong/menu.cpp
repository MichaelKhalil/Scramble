#include "menu.h"
#include "main_game.h"

void menu::Initialize(sf::RenderWindow* window){
	//Selected decides which option is currently highlighted to be used
	this->selected = 0;
	//Read font from folder
	this->font = new sf::Font();
	this->font->loadFromFile("font.ttf");
	//set title at top middle of start screen
	this->title = new sf::Text("Scramble", *this->font, 200U);
	this->title->setOrigin(this->title->getGlobalBounds().width/2, this->title->getGlobalBounds().height/2);
	this->title->setPosition(window->getSize().x/2, window->getSize().y/8);
	//set play button
	this->play = new sf::Text("play", *this->font, 128U);
	this->play->setOrigin(this->play->getGlobalBounds().width/2, this->play->getGlobalBounds().height/2);
	this->play->setPosition(window->getSize().x/2, window->getSize().y/2);
	//set end button
	this->quit = new sf::Text("quit", *this->font, 128U);
	this->quit->setOrigin(this->quit->getGlobalBounds().width/2, this->quit->getGlobalBounds().height/2);
	this->quit->setPosition(window->getSize().x/2, (window->getSize().y/2)+(window->getSize().y/4));
}

void menu::Update(sf::RenderWindow* window){
	//change selection based on up or down key
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && !this->upKey){
		this->selected -= 1;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && !this->downKey){
		this->selected += 1;
	}
	//wrap around if at the top or bottom of menu
	if(this->selected > 1)
		this->selected = 0;
	if(this->selected < 0)
		this->selected = 1;

	this->upKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
	this->downKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
}
void menu::Render(sf::RenderWindow* window){
	//change color on selection, default white to blue
	this->play->setColor(sf::Color::White);
	this->quit->setColor(sf::Color::White);
	switch(this->selected){
	case 0:
		this->play->setColor(sf::Color::Blue);
		break;
	case 1:
		this->quit->setColor(sf::Color::Blue);

	}

	window->draw(*this->title);
	window->draw(*this->play);
	window->draw(*this->quit);
	//handle between changing states, either set state to game or signify quit	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)){
		switch(this->selected){
		case 0:
			coreState.SetState(new main_game());
			break;
		case 1:
			quitGame = true;
			break;
		}
	}
}
//cleanup
void menu::Destroy(sf::RenderWindow* window){
	delete this->font;
	delete this->title;
	delete this->play;
	delete this->quit;
}
