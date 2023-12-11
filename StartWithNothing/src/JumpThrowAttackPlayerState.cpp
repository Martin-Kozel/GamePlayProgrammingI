#include <Events.h>

#include <JumpThrowAttackPlayerState.h>

#include <RunRightPlayerState.h>
#include <GlidePlayerState.h>
#include <DiedPlayerState.h>

PlayerState* JumpThrowAttackPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("JumpThrowAttackPlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::THROW_STOP_EVENT)
	{
		DEBUG_MSG("JumpThrowAttackPlayerState -> GlidePlayerState");
		return new GlidePlayerState();
	}
	return nullptr;
}
void JumpThrowAttackPlayerState::update(Player& player) {
	DEBUG_MSG("JumpThrowAttackPlayerState::update");
	DEBUG_MSG(typeid(player).name());
}
void JumpThrowAttackPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering JumpThrowAttackPlayerState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(sf::IntRect(4596, 0, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(4956, 0, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(5316, 0, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(4596, 431, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(4956, 431, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(5316, 431, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(4596, 862, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(4956, 862, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(5316, 862, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(4596, 1293, 360, 431));

	player.getAnimatedSprite().setTime(seconds(0.05f));
}
void JumpThrowAttackPlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting JumpThrowAttackPlayerState");
	DEBUG_MSG(typeid(player).name());
}