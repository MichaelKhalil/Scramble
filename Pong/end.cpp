#include "end.h"
#include "main_game.h"

void end::Initialize(sf::RenderWindow* window){

	//Read font from folder
	this->font = new sf::Font();
	this->font->loadFromFile("font.ttf");
	//set title at top middle of start screen
	this->back = new sf::Text("Scramble", *this->font, 200U);
	this->back->setOrigin(this->back->getGlobalBounds().width/2, this->back->getGlobalBounds().height/2);
	//this->back->setPosition(window->getSize().x/2, window->getSize().y/8);
	this->back->setPosition(400, 100);
}
void end::Update(sf::RenderWindow* window){
	this->score1->Update();
	this->highScore->Update();
}
void end::Render(sf::RenderWindow* window){
	//change color on selection, default white to blue
	this->back->setColor(sf::Color::White);


	window->draw(*this->back);

	//handle between changing states, either set state to game or signify quit	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)){

			coreState.SetState(new main_game());
	}
}
//cleanup
void end::Destroy(sf::RenderWindow* window){
	delete this->font;
	delete this->back;

}
