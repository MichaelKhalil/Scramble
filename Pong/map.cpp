
#include "map.h"


Map::Map(){
	this->Load("map.png");
	//this->velocity.x -= 1;
}
void Map::Update(){
	Entity::Update();
}
