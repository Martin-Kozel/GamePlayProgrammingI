#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <./include/GameObject.h>

using namespace std;

class Player : public GameObject
{
public:
	Player();
	~Player();
	void initialize();
	void update();
	void draw();
};
#endif