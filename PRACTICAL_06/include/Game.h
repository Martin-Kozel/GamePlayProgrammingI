#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include <./include/ConcreteCommands.h>
#include <./include/InputManager.h>

#include <./include/GameObject.h>

#include <./include/Player.h>
#include <./include/NPC.h>

class Game
{
public:
	Game();
	~Game();
	void run();

private:
	void initialize();
	void update();
	void draw();
	GameObject *player;
	GameObject *npc;
	int index = -1;
	std::vector<Command *> commands;
	sf::RenderWindow window;
};

#endif