#include <./include/Player.h>

Player::Player(){};
Player::~Player(){};

Player::Player(Vector2f position, String image)
{
	this->position = position;
	initialize(image);
}