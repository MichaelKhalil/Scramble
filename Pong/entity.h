#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

class Entity : public sf::Sprite{
public:
	Entity(){
		this->texture = new sf::Texture();
		this->buffer = new sf::SoundBuffer(); 
		this->blip = new sf::Sound();
	}

	void Load(std::string filename){
		this->texture->loadFromFile("Graphics/" + filename);
		this->setTexture(*this->texture);
	}
	void loadSound(std::string filename){
		this->buffer->loadFromFile("Sounds/" + filename);
	}

	virtual void Update(){
		this-> move(this->velocity);
	}

	bool checkCollision(Entity* entity){
		return this->getGlobalBounds().intersects(entity->getGlobalBounds());
	}

	~Entity(){
		delete this->texture;
		delete this->buffer;
		delete this->blip;
	}

protected:
	sf::Vector2f velocity;
private:
	sf::Texture* texture;
	sf::SoundBuffer* buffer;
	sf::Sound* blip;
};