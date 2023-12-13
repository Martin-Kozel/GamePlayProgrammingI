#include <Defines.h>

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <cstdlib>
#include <Events.h>
#include <Debug.h>

//added cute_c2 for collisons
#define CUTE_C2_IMPLEMENTATION
#include <cute_c2.h>

using namespace std;
using namespace sf;
float VectorLength(sf::Vector2f);

sf::Text m_PlayerHP;
sf::Text m_EnemyHP;
sf::Text m_Attack;
sf::Text m_Throw;
sf::Text m_Dodge;
sf::Texture m_Kunai_Texture;
sf::Sprite m_Kunai_Sprite;
bool m_Graphics = true;
sf::Font Beadly;

void SetupText() {
	if (!Beadly.loadFromFile(FONT)) {
		cout << "error with font" << endl;
	}

	m_PlayerHP.setFont(Beadly);
	m_PlayerHP.setString("HEALTH = 100");
	m_PlayerHP.setPosition(20.0f, 450.0f);
	m_PlayerHP.setCharacterSize(30U);
	m_PlayerHP.setFillColor(sf::Color::Green);

	m_EnemyHP.setFont(Beadly);
	m_EnemyHP.setString("HEALTH = 100");
	m_EnemyHP.setPosition(550.0f, 450.0f);
	m_EnemyHP.setCharacterSize(30U);
	m_EnemyHP.setFillColor(sf::Color::Red);

	m_Attack.setFont(Beadly);
	m_Attack.setString("A : Attack '20 Dammage'");
	m_Attack.setPosition(20.0f, 550.0f);
	m_Attack.setCharacterSize(20U);
	m_Attack.setFillColor(sf::Color::Blue);
	m_Attack.setOutlineThickness(2.5f);
	m_Attack.setOutlineColor(sf::Color::White);

	m_Throw.setFont(Beadly);
	m_Throw.setString("S : Throw '10 Dammage'");
	m_Throw.setPosition(370.0f, 550.0f);
	m_Throw.setCharacterSize(20U);
	m_Throw.setFillColor(sf::Color::Blue);
	m_Throw.setOutlineThickness(2.5f);
	m_Throw.setOutlineColor(sf::Color::White);

	m_Dodge.setFont(Beadly);
	m_Dodge.setString("D :Dodge");
	m_Dodge.setPosition(720.0f, 550.0f);
	m_Dodge.setCharacterSize(20U);
	m_Dodge.setFillColor(sf::Color::Blue);
	m_Dodge.setOutlineThickness(2.5f);
	m_Dodge.setOutlineColor(sf::Color::White);

}


int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(1000, 600), "Player Finite State Machine");

	SetupText();

	// Load a sprite to display
	sf::Texture player_texture;
	if (!player_texture.loadFromFile(PLAYER_SPRITES))
	{
		DEBUG_MSG("Failed to load file");
		if (!player_texture.loadFromFile(ERROR_SPRITES))
		{
			return EXIT_FAILURE;
		}
	}

	// Setup Players Default Animated Sprite
	AnimatedSprite player_animated_sprite(player_texture);

	//Players varibles
	Player player(player_animated_sprite);
	player.health = 100;
	player.turn = true;
	player.attacking = false;
	player.throwing = false;
	player.jumping = false;

	sf::Vector2f m_PlCoLocation;
	m_PlCoLocation = sf::Vector2f{ 175.0f,230.0f };
	sf::Vector2f m_EnCoLocation;
	m_EnCoLocation = sf::Vector2f{ 610.0f,230.0f };

	//Playes Shapes
	sf::RectangleShape m_playerBody(sf::Vector2f(100, 200));
	m_playerBody.setPosition(75, 150);
	m_playerBody.setFillColor(sf::Color::Green);

	//Player Collider
	sf::CircleShape m_PlCollider(20);
	m_PlCollider.setFillColor(sf::Color::Blue);
	m_PlCollider.setPosition(m_PlCoLocation);

	//Enemys variables
	Player npc(player_animated_sprite);
	npc.turn = false;
	npc.health = 100;
	sf::Vector2f m_EnLocation;
	m_EnLocation = sf::Vector2f{ 650.0f,150.0f };

	//Enemys Shapes
	sf::RectangleShape m_enemyBody(sf::Vector2f(100, 200));
	m_enemyBody.setPosition(m_EnLocation);
	m_enemyBody.setFillColor(sf::Color::Red);

	//Enemy Collider
	sf::CircleShape m_EnCollider(20);
	m_EnCollider.setFillColor(sf::Color::Yellow);
	m_EnCollider.setPosition(m_EnCoLocation);


	//Setup Player Collidor
	c2Circle PlayerCollison;
	PlayerCollison.p = c2V(m_PlCollider.getPosition().x, m_PlCollider.getPosition().y);
	PlayerCollison.r = m_PlCollider.getRadius();

	//Setup Enemy Collider
	c2Circle EnemyCollison;
	EnemyCollison.p = c2V(m_EnCollider.getPosition().x, m_EnCollider.getPosition().y);
	EnemyCollison.r = m_EnCollider.getRadius();

	//Setup NPC AABB
	c2AABB aabb_npc;
	aabb_npc.min = c2V(m_enemyBody.getPosition().x, m_enemyBody.getPosition().y);
	aabb_npc.max = c2V(
		m_enemyBody.getPosition().x +
		m_enemyBody.getGlobalBounds().width,
		m_enemyBody.getPosition().y +
		m_enemyBody.getGlobalBounds().height);

	//Set Player AABB
	c2AABB aabb_player;
	aabb_player.min = c2V(m_playerBody.getPosition().x, m_playerBody.getPosition().y);
	aabb_player.max = c2V(
		m_playerBody.getPosition().x +
		m_playerBody.getGlobalBounds().width,
		m_playerBody.getPosition().y +
		m_playerBody.getGlobalBounds().height);



	bool collison = c2CircletoAABB(PlayerCollison, aabb_npc);
	bool collison2 = c2CircletoAABB(EnemyCollison, aabb_player);

	gpp::Events input;
	gpp::Events ai;

	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				// Close window : exit
				window.close();
				break;
				// Deal with KeyPressed
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
				{
					m_Graphics = false;
				}
				if (player.turn == true) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					{
						input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
						npc.turn = true;
						player.turn = false;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
					{
						input.setCurrent(gpp::Events::Event::THROW_START_EVENT);
						npc.turn = true;
						player.turn = false;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
					{
						input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
						npc.turn = true;
						player.turn = false;
					}
					break;
				}
				// Deal with KeyReleased
			case sf::Event::KeyReleased:
				if (player.turn == true) {
					if (event.key.code == sf::Keyboard::A)
					{
						input.setCurrent(gpp::Events::Event::ATTACK_STOP_EVENT);
					}
					if (event.key.code == sf::Keyboard::T)
					{
						input.setCurrent(gpp::Events::Event::THROW_STOP_EVENT);
					}
					if (event.key.code == sf::Keyboard::J)
					{
						input.setCurrent(gpp::Events::Event::FALL_DOWN_EVENT);
					}
					if (event.key.code == sf::Keyboard::Space) {
						m_Graphics = true;
					}
					break;
				}
			default:
				input.setCurrent(gpp::Events::Event::NONE);
				break;
			}
			// Handle input to Player
			player.handleInput(input);
		}

		// Update AI
		if (npc.health > 0 && npc.turn) {

			int weapon = rand() % 5 + 1;

			switch (weapon) {
			case 1:
				ai.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
				npc.attacking = true;
				break;
			case 2:
				ai.setCurrent(gpp::Events::Event::THROW_START_EVENT);
				npc.throwing = true;
				break;
			case 3:
				ai.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
				break;
			case 4:
				ai.setCurrent(gpp::Events::Event::ATTACK_STOP_EVENT);
				break;
			case 5:
				ai.setCurrent(gpp::Events::Event::THROW_STOP_EVENT);
				break;
			default:
				ai.setCurrent(gpp::Events::Event::NONE);
				break;
			}

			// Execution
			npc.handleInput(ai);
			npc.turn = false;
			player.turn = true;
		}

		npc.getAnimatedSprite().setScale(-1.0f, 1.0f);
		npc.getAnimatedSprite().setPosition(800.0f, 0.0f);

		// Update the Player
		player.update();

		
		// Update the NPC
		npc.update();

		// Clear screen
		window.clear();
		window.draw(m_PlayerHP);
		window.draw(m_EnemyHP);
		window.draw(m_Attack);
		window.draw(m_Dodge);
		window.draw(m_Throw);

		// Draw the Player's Current Animated Sprite
		if (m_Graphics) {
			window.draw(player.getAnimatedSpriteFrame());
		}
		else {
			window.draw(m_playerBody);
			window.draw(m_PlCollider);
		}

		// Draw the NPC's Current Animated Sprite
		if (m_Graphics) {
			window.draw(npc.getAnimatedSpriteFrame());
		}
		else {
			window.draw(m_enemyBody);
			window.draw(m_EnCollider);
		}
		

		// Update the window
		window.display();
	}



	return EXIT_SUCCESS;
};