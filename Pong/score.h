#pragma once

#include <SFML/Graphics.hpp>

class Score : public sf::Text{
public:
	Score(sf::Font &font, unsigned int size);
	void IncrementScore();
	void setScore(int number);
	void addScore(int number);
	void Update();
	long long value;
private:
	
};