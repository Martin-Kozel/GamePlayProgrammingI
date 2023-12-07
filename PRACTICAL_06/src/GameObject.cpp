#include <./include/GameObject.h>

GameObject::GameObject(){
}

GameObject::~GameObject(){
}

void GameObject::initialize(String image){
	if (!texture.loadFromFile(image + ".png"))
	{
		std::cout << "Image file not found";
	}
	sprite.setTexture(texture); 
	sprite.setPosition(sf::Vector2f(position.x, position.y));
}

void GameObject::update()
{
	sprite.setPosition(this->position);
}

void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void GameObject::setPosition(Vector2f position)
{
	this->position = position;
}

Vector2f GameObject::getPosition()
{
	return this->position;
}

void GameObject::moveUp()
{
	this->position.y -= 5;
}

void GameObject::moveDown()
{
	this->position.y += 5;
}

void GameObject::moveLeft()
{
	this->position.x -= 5;
}

void GameObject::moveRight()
{
	this->position.x += 5;
}

void GameObject::jump()
{
	std::cout << "JUMP" << std::endl;
	this->position.y -= 100;
}

void GameObject::sprint(float speed)
{
	std::cout << "SPRINTING AT SPEED:" << speed << std::endl;
	this->position.x += speed;
}
void GameObject::crouch()
{
	std::cout << "CROUCHING" << std::endl;
}

void GameObject::shield()
{
	std::cout << "SHIELD" << std::endl;
}

void GameObject::attack()
{
	std::cout << "ATTACK" << std::endl;
}