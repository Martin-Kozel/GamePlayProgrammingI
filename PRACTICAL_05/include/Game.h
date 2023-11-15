#ifndef GAME_H
#define GAME_H

#include <./include/Player.h>
#include <./include/NPC.h>

class Game
{
	public:
		Game();
		void run();
	private:
		void initialize();
		void update();
		void draw();
		Player* player;
		NPC* npc;
};

#endif