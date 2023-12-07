#include <./include/Game.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>

using namespace sf;

#define CUTE_C2_IMPLEMENTATION
#include <./include/cute_c2.h>

sf::RenderWindow* window = new RenderWindow(sf::VideoMode(800, 600), "Launching...");


sf::Texture player_texture;
sf::Texture npc_texture;

sf::Sprite player_sprite;
sf::Sprite npc_sprite;



sf::RectangleShape player_rect(sf::Vector2f(100, 100));
sf::RectangleShape npc_rect(sf::Vector2f(100, 100));
sf::CircleShape npc_cir(50);

Game::Game(){}

void Game::initialize()
{
	player = new Player();
	npc = new NPC();
	npc_Cir = new NPC();

	window->setSize(sf::Vector2u(640, 480));
	window->setTitle("Game");

	player->x = 500;
	player->y = 0;
	player->w = 100;
	player->h = 100;
	player->r = 0;

	npc->x = 0;
	npc->y = 0;
	npc->w = 100;
	npc->h = 100;
	npc->r = 0;

	npc_Cir->x = 400;
	npc_Cir->y = 300;
	npc_Cir->w = 0;
	npc_Cir->h = 0;
	npc_Cir->r = 50;

	player_texture.loadFromFile(".//images//player//Player.png");
	npc_texture.loadFromFile(".//images//npc//npc.png");

	player_sprite.setTexture(player_texture);
	npc_sprite.setTexture(npc_texture);

	//setting player_rect to player cords
	player_rect.setPosition(player->x, player->y);
	player_rect.setFillColor(sf::Color::Green);
	//setting npc_rect to npc cords
	npc_rect.setPosition(npc->x, npc->y);
	npc_rect.setFillColor(sf::Color::Blue);
	//setting npc_cir to npc_Cir cords 
	npc_cir.setPosition(npc_Cir->x, npc_Cir->y);
	npc_cir.setFillColor(sf::Color::Yellow);
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

		//key input 
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Right)
			{
				player_rect.move(5.0f, 0.0f);
			}
			if (event.key.code == sf::Keyboard::Left)
			{
				player_rect.move(-5.0f, 0.0f);
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				player_rect.move(0.0f, 5.0f);
			}
			if (event.key.code == sf::Keyboard::Up)
			{
				player_rect.move(0.0f, -5.0f);
			}

		}


		//updates GameObjects indivually
		player->update();
		npc->update();
		npc_Cir->update();

		//Setup NPC AABB
		c2AABB aabb_npc;
		aabb_npc.min = c2V(npc_rect.getPosition().x, npc_rect.getPosition().y);
		aabb_npc.max = c2V(
			npc_rect.getPosition().x +
			npc_rect.getGlobalBounds().width, 
			npc_rect.getPosition().y +
			npc_rect.getGlobalBounds().height);
			
		//Setup Player AABB
		c2AABB aabb_player;
		aabb_player.min = c2V(player_rect.getPosition().x,player_rect.getPosition().y);
		aabb_player.max = c2V(player_rect.getGlobalBounds().width, player_rect.getGlobalBounds().height);

		//Setup NPC Circle
		c2Circle Circle_Npc;
		Circle_Npc.p = c2V(npc_cir.getPosition().x, npc_cir.getPosition().y);
		Circle_Npc.r = npc_cir.getRadius();

		//making bools out of the collisions there set to true by default 
		bool collisionAABB = c2AABBtoAABB(aabb_npc, aabb_player);
		bool collisionCircle = c2CircletoAABB(Circle_Npc, aabb_player);

		//if Collison Rect to Rect
		if (collisionAABB)
		{
			std::cout << "Collision with NPC Rectangle" << std::endl;
			player_rect.setFillColor(sf::Color::White);
			npc_rect.setFillColor(sf::Color::Green);
		}
		else if (collisionCircle) //if Collison Rect to Circle
		{
			std::cout << "Collison with NPC Circle" << std::endl;
			player_rect.setFillColor(sf::Color::Red);
			npc_cir.setFillColor(sf::Color::Cyan);
		}
		else if (!collisionCircle || !collisionAABB)//if no Collison with any object 
		{
			std::cout << "No Collision" << std::endl;
			player_rect.setFillColor(sf::Color::Magenta);
			npc_cir.setFillColor(sf::Color::Blue);
			npc_rect.setFillColor(sf::Color::Yellow);
		}
	}

}

void Game::draw()
{
	window->clear();
	window->draw(player_rect);
	window->draw(npc_rect);
	window->draw(npc_cir);
	//player->draw();
	//npc->draw();
	window->display();
}


