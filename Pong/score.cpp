#include "score.h"
#include <iostream>

Score::Score(sf::Font &font, unsigned int size) : sf::Text("score: 0", font, size){
	this->value = 0;
	
}
void Score::IncrementScore(){
	this->value += 1;
}

void Score::setScore(int number){
	this->value = number;
}

void Score::addScore(int number){
	this->value += number;
}

void Score::Update(){
	//std::cout << std::to_string(this->value);
	this->setString(std::to_string(this->value));
}