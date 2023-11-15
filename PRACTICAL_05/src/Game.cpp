#include <./include/Game.h>
#include <SFML/Graphics.hpp>

using namespace sf;

#define CUTE_C2_IMPLEMENTATION
#include <./include/cute_c2.h>

sf::RenderWindow* window = new RenderWindow(sf::VideoMode(800, 600), "Launching...");


sf::Texture player_texture;
sf::Texture npc_texture;

sf::Sprite player_sprite;
sf::Sprite npc_sprite;

Game::Game(){}

void Game::initialize()
{
	player = new Player();
	npc = new NPC();

	window->setSize(sf::Vector2u(640, 480));
	window->setTitle("Game");

	player->x = 0;
	player->y = 0;
	player->w = 0;
	player->h = 0;
	player->r = 0;

	npc->x = 0;
	npc->y = 0;
	npc->w = 0;
	npc->h = 0;
	npc->r = 0;

	player_texture.loadFromFile(".//images//player//Player.png");
	npc_texture.loadFromFile(".//images//npc//npc.png");

	player_sprite.setTexture(player_texture);
	npc_sprite.setTexture(npc_texture);
}

void Game::run()
{
	initialize();

	while (window->isOpen())
	{
		update();
		draw();
	}
}

void Game::update()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();

		player->update();
		npc->update();

		//Setup NPC AABB
		c2AABB aabb_npc;
		aabb_npc.min = c2V(npc_sprite.getPosition().x, npc_sprite.getPosition().y);
		aabb_npc.max = c2V(
			npc_sprite.getPosition().x +
			npc_sprite.getGlobalBounds().width, 
			npc_sprite.getPosition().y +
			npc_sprite.getGlobalBounds().height);
			
		//Setup Player AABB
		c2AABB aabb_player;
		aabb_player.min = c2V(player_sprite.getPosition().x,player_sprite.getPosition().y);
		aabb_player.max = c2V(player_sprite.getGlobalBounds().width, player_sprite.getGlobalBounds().height);
		
		if(c2AABBtoAABB(aabb_npc, aabb_player)){
			cout << "NPC and Player are in Collision" << endl;
		} else{
			cout << "No Collision" << endl;
		}

		// Move the player
		player_sprite.move(sf::Vector2f(1.0f, 1.0f));
	}

}

void Game::draw()
{
	window->clear();
	window->draw(player_sprite);
	window->draw(npc_sprite);
	//player->draw();
	//npc->draw();
	window->display();
}


