#include <Events.h>

#include <ClimbUpPlayerState.h>

#include <ClimbPausePlayerState.h>
#include <ClimbDownPlayerState.h>
#include <DecendLadderPlayerState.h>


PlayerState* ClimbUpPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::MOVE_UP_STOP_EVENT)
	{
		DEBUG_MSG("ClimbUpPlayerState -> ClimbPausePlayerState");
		return new ClimbPausePlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::MOVE_DOWN_START_EVENT)
	{
		DEBUG_MSG("ClimbUpPlayerState -> ClimbDownPlayerState");
		return new ClimbDownPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::HIT_LADDER_TOP_EVENT)
	{
		DEBUG_MSG("ClimbUpPlayerState -> DecendLadderPlayerState");
		return new DecendLadderPlayerState();
	}
	
	return nullptr;
}
void ClimbUpPlayerState::update(Player& player) {
	DEBUG_MSG("ClimbUpPlayerState::update");
	DEBUG_MSG(typeid(player).name());
}
void ClimbUpPlayerState::enter(Player& player) 
{
	DEBUG_MSG("Entering ClimbUpPlayerState");

	// Climb Up Animated Sprite
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(sf::IntRect(1608, 1392, 282, 464));
	player.getAnimatedSprite().addFrame(sf::IntRect(2172, 928, 282, 464));
	player.getAnimatedSprite().addFrame(sf::IntRect(1890, 928, 282, 464));
	player.getAnimatedSprite().addFrame(sf::IntRect(1608, 928, 282, 464));
	player.getAnimatedSprite().addFrame(sf::IntRect(2172, 464, 282, 464));
	player.getAnimatedSprite().addFrame(sf::IntRect(1890, 464, 282, 464));
	player.getAnimatedSprite().addFrame(sf::IntRect(1608, 464, 282, 464));
	player.getAnimatedSprite().addFrame(sf::IntRect(2172, 0, 282, 464));
	player.getAnimatedSprite().addFrame(sf::IntRect(1890, 0, 282, 464));
	player.getAnimatedSprite().addFrame(sf::IntRect(1608, 0, 282, 464));
	
	player.getAnimatedSprite().setTime(seconds(0.05f));
}
void ClimbUpPlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting ClimbUpPlayerState");
	DEBUG_MSG(typeid(player).name());
}