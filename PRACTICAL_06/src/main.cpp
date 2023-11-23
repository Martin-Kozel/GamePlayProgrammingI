#include <./include/Game.h>

int main(void)
{
	Game *game = new Game();
	game->run();
	delete game; // Cleanup memory
	return 0;
}