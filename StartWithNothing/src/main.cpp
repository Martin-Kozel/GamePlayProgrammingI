#include <Defines.h>

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <Events.h>
#include <Debug.h>

using namespace std;
bool npcTurn{ false };
bool playerTurn{ true };

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Player Finite State Machine");

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

	Player player(player_animated_sprite);
	Player npc(player_animated_sprite);

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
				/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
				{
					m_Graphics = false;
				}*/

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
				{
					input.setCurrent(gpp::Events::Event::THROW_START_EVENT);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
				{
					input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
				}
				break;
				// Deal with KeyReleased
			case sf::Event::KeyReleased:
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
				break;

			default:
				input.setCurrent(gpp::Events::Event::NONE);
				break;
			}
			// Handle input to Player
			player.handleInput(input);
		}

		// Update AI
		ai.setCurrent(gpp::Events::Event::NONE);
		npc.handleInput(ai);
		npc.getAnimatedSprite().setScale(-1.0f, 1.0f);
		npc.getAnimatedSprite().setPosition(800.0f, 0.0f);

		// Update the Player
		player.update();
		
		// Update the NPC
		npc.update();

		// Clear screen
		window.clear();

		// Draw the Players Current Animated Sprite
		window.draw(player.getAnimatedSpriteFrame());

		// Draw the NPC's Current Animated Sprite
		window.draw(npc.getAnimatedSpriteFrame());

		// Update the window
		window.display();
	}



	return EXIT_SUCCESS;
};