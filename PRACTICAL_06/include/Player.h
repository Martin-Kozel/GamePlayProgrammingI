#ifndef PLAYER_H
#define PLAYER_H

#include <./include/GameObject.h>

class Player : public GameObject
{
public:
	Player();
	Player(Vector2f, String);
	~Player();
};
#endif