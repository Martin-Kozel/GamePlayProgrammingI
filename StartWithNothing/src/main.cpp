#include <Defines.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <cstdlib>
#include <Events.h>
#include <Debug.h>

#define CUTE_C2_IMPLEMENTATION
#include <cute_c2.h>

using namespace std;
using namespace sf;
float VectorLength(sf::Vector2f);
bool changeGraphic = true;
sf::Text m_PlayerHP;
sf::Text m_EnemyHP;
sf::Text m_Attack;
sf::Text m_Throw;
sf::Text m_Dodge;
sf::Text m_Gameover;
sf::Texture m_Kunai_Texture;
sf::Sprite m_Kunai_Sprite;
sf::Font Motley_Forces;


void SetupText() {
	if (!Motley_Forces.loadFromFile(FONT)) {
		cout << "error with font" << endl;
	}

	m_PlayerHP.setFont(Motley_Forces);
	m_PlayerHP.setString("You = 100 HP");
	m_PlayerHP.setPosition(20.0f, 450.0f);
	m_PlayerHP.setCharacterSize(30U);
	m_PlayerHP.setFillColor(sf::Color::Blue);

	m_EnemyHP.setFont(Motley_Forces);
	m_EnemyHP.setString("Enemy = 100 HP");
	m_EnemyHP.setPosition(550.0f, 450.0f);
	m_EnemyHP.setCharacterSize(30U);
	m_EnemyHP.setFillColor(sf::Color::Green);

	m_Attack.setFont(Motley_Forces);
	m_Attack.setString("A for attack(20)");
	m_Attack.setPosition(20.0f, 550.0f);
	m_Attack.setCharacterSize(20U);
	m_Attack.setFillColor(sf::Color::Red);
	m_Attack.setOutlineThickness(2.5f);
	m_Attack.setOutlineColor(sf::Color::White);

	m_Throw.setFont(Motley_Forces);
	m_Throw.setString("T for Kunai throw(10)");
	m_Throw.setPosition(370.0f, 550.0f);
	m_Throw.setCharacterSize(20U);
	m_Throw.setFillColor(sf::Color::Red);
	m_Throw.setOutlineThickness(2.5f);
	m_Throw.setOutlineColor(sf::Color::White);

	m_Dodge.setFont(Motley_Forces);
	m_Dodge.setString("J for jump(0)");
	m_Dodge.setPosition(720.0f, 550.0f);
	m_Dodge.setCharacterSize(20U);
	m_Dodge.setFillColor(sf::Color::Red);
	m_Dodge.setOutlineThickness(2.5f);
	m_Dodge.setOutlineColor(sf::Color::White);

}

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(1000, 600), "Player Finite State Machine");

	SetupText();

	sf::Texture background_texture;
	if (!background_texture.loadFromFile("./assets/Background.jpg")) {
		DEBUG_MSG("Failed to load background");
	}
	sf::Sprite backgroundSprite(background_texture);
	backgroundSprite.setScale(2.0f, 2.0f);

	// Load a player sprite to display
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

	sf::Vector2f m_PlayerColliderLocation;
	m_PlayerColliderLocation = sf::Vector2f{ 175.0f,230.0f };
	sf::Vector2f m_EnemyColliderLocation;
	m_EnemyColliderLocation = sf::Vector2f{ 610.0f,230.0f };

	//Playes Shapes
	sf::RectangleShape m_playerShape(sf::Vector2f(100, 200));
	m_playerShape.setPosition(75, 150);
	m_playerShape.setFillColor(sf::Color::Green);

	//Player Collider
	sf::CircleShape m_PlayerCollider(20);
	m_PlayerCollider.setFillColor(sf::Color::Blue);
	m_PlayerCollider.setPosition(m_PlayerColliderLocation);

	//Enemys variables
	Player npc(player_animated_sprite);
	npc.turn = false;
	npc.health = 100;
	sf::Vector2f m_EnemyLocation;
	m_EnemyLocation = sf::Vector2f{ 650.0f,150.0f };

	//Enemys Shapes
	sf::RectangleShape m_enemyShape(sf::Vector2f(100, 200));
	m_enemyShape.setPosition(m_EnemyLocation);
	m_enemyShape.setFillColor(sf::Color::Red);

	//Enemy Collider
	sf::CircleShape m_EnemyCollider(20);
	m_EnemyCollider.setFillColor(sf::Color::Yellow);
	m_EnemyCollider.setPosition(m_EnemyColliderLocation);


	//Setup Player Collidor
	c2Circle PlayerCollison;
	PlayerCollison.p = c2V(m_PlayerCollider.getPosition().x, m_PlayerCollider.getPosition().y);
	PlayerCollison.r = m_PlayerCollider.getRadius();

	//Setup Enemy Collider
	c2Circle EnemyCollison;
	EnemyCollison.p = c2V(m_EnemyCollider.getPosition().x, m_EnemyCollider.getPosition().y);
	EnemyCollison.r = m_EnemyCollider.getRadius();

	//Setup NPC AABB
	c2AABB aabb_npc;
	aabb_npc.min = c2V(m_enemyShape.getPosition().x, m_enemyShape.getPosition().y);
	aabb_npc.max = c2V(
		m_enemyShape.getPosition().x +
		m_enemyShape.getGlobalBounds().width,
		m_enemyShape.getPosition().y +
		m_enemyShape.getGlobalBounds().height);

	//Set Player AABB
	c2AABB aabb_player;
	aabb_player.min = c2V(m_playerShape.getPosition().x, m_playerShape.getPosition().y);
	aabb_player.max = c2V(
		m_playerShape.getPosition().x +
		m_playerShape.getGlobalBounds().width,
		m_playerShape.getPosition().y +
		m_playerShape.getGlobalBounds().height);



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
					changeGraphic = false;
				}
				if (player.turn == true) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					{
						input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
						player.attacking = true;
						npc.turn = true;
						player.turn = false;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
					{
						input.setCurrent(gpp::Events::Event::THROW_START_EVENT);
						player.throwing = true;
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
						changeGraphic = true;
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

		if (player.attacking == true || player.throwing == true)
		{
			m_PlayerColliderLocation.x += 1.0f;
			m_PlayerCollider.setPosition(m_PlayerColliderLocation);
			if (player.throwing == true)
			{
				if (!m_Kunai_Texture.loadFromFile(KUNAI_SPRITE)) {
					std::cout << "ERROR with Kunai" << std::endl;
				}
				m_Kunai_Sprite.setTexture(m_Kunai_Texture);
				m_Kunai_Sprite.setRotation(90.0f);
				m_Kunai_Sprite.setPosition(m_PlayerColliderLocation);
			}

			// Update the position of the player's collider before collision detection
			PlayerCollison.p = c2V(m_PlayerColliderLocation.x, m_PlayerColliderLocation.y);

			// Perform collision detection after updating the player's position
			collison = c2CircletoAABB(PlayerCollison, aabb_npc);

			if (collison || m_PlayerColliderLocation.x >= 1000)
			{
				m_PlayerColliderLocation = sf::Vector2f{ 175.0f, 230.0f };
				m_PlayerCollider.setPosition(m_PlayerColliderLocation);

				if (collison)
				{
					if (player.attacking == true)
					{
						if (npc.jumping == false)
						{
							npc.health = npc.health - 20;
						}
					}
					if (player.throwing == true)
					{
						if (npc.jumping == false)
						{
							npc.health = npc.health - 10;
						}
					}
					m_EnemyHP.setString("Enemy = " + std::to_string(npc.health) + "HP");
				}
				player.attacking = false;
				player.throwing = false;
				player.turn = false;
				player.jumping = false;
				npc.turn = true;
			}
		}
		// Update the NPC
		npc.update();

		if (npc.health <= 0) {
			npc.health = 0;
			m_EnemyHP.setString("HEALTH = " + std::to_string(npc.health));
			ai.setCurrent(gpp::Events::Event::DIED_EVENT);
			m_Gameover.setString("YOU WIN");
			m_Gameover.setPosition(400.0f, 100.0f);
		}

		if (npc.attacking == true || npc.throwing == true)
		{
			m_EnemyColliderLocation.x -= 1.0f;
			m_EnemyCollider.setPosition(m_EnemyColliderLocation);
			if (npc.throwing == true)
			{
				if (!m_Kunai_Texture.loadFromFile(KUNAI_SPRITE)) {
					std::cout << "ERROR with Kunai" << std::endl;
				}
				m_Kunai_Sprite.setTexture(m_Kunai_Texture);
				m_Kunai_Sprite.setScale(1.0f, -1.0f);
				m_Kunai_Sprite.setPosition(m_EnemyColliderLocation);
			}

			// Update the position of the player's collider before collision detection
			EnemyCollison.p = c2V(m_EnemyColliderLocation.x, m_EnemyColliderLocation.y);

			// Perform collision detection after updating the player's position
			collison2 = c2CircletoAABB(EnemyCollison, aabb_player);

			if (collison2 || m_EnemyColliderLocation.x <= 0)
			{
				m_EnemyColliderLocation = sf::Vector2f{ 610.0f,230.0f };
				m_EnemyCollider.setPosition(m_EnemyColliderLocation);

				if (collison2)
				{
					if (npc.attacking == true)
					{
						if (player.jumping == false) {
							player.health = player.health - 20;
						}
					}
					if (npc.throwing == true)
					{
						if (player.jumping == false) {
							player.health = player.health - 10;
						}
					}
					m_PlayerHP.setString("You = " + std::to_string(player.health) + "HP");
				}
				npc.attacking = false;
				npc.throwing = false;
				npc.turn = false;
				npc.jumping = false;
				player.turn = true;
			}
		}

		// Clear screen
		window.clear();
		

		// Draw the Player's Current Animated Sprite
		if (changeGraphic) {
			window.draw(backgroundSprite);
			window.draw(player.getAnimatedSpriteFrame());
			window.draw(npc.getAnimatedSpriteFrame());
			window.draw(m_PlayerHP);
			window.draw(m_EnemyHP);
			window.draw(m_Attack);
			window.draw(m_Dodge);
			window.draw(m_Throw);
		}
		else {
			window.draw(m_playerShape);
			window.draw(m_PlayerCollider);
			window.draw(m_enemyShape);
			window.draw(m_EnemyCollider);
		}
		

		// Update the window
		window.display();
	}



	return EXIT_SUCCESS;
};