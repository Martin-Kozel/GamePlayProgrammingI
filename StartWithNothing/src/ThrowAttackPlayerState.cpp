#include <Events.h>

#include <ThrowAttackPlayerState.h>

#include <RunRightPlayerState.h>
#include <IdlePlayerState.h>
#include <DiedPlayerState.h>

PlayerState *ThrowAttackPlayerState::handleInput(gpp::Events &input)
{
	if (input.getCurrent() == gpp::Events::Event::RUN_RIGHT_START_EVENT)
	{
		DEBUG_MSG("AttackPlayerState -> RunRightPlayerState");
		return new RunRightPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::THROW_STOP_EVENT)
	{
		DEBUG_MSG("AttackPlayerState -> IdlePlayerState");
		return new IdlePlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT)
	{
		DEBUG_MSG("ThrowAttackPlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	return nullptr;
}
void ThrowAttackPlayerState::update(Player &player)
{
	DEBUG_MSG("ThrowAttackPlayerState::update");
	DEBUG_MSG(typeid(player).name());
}

void ThrowAttackPlayerState::enter(Player &player)
{
	DEBUG_MSG("Entering AttackPlayerState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(sf::IntRect(6075, 0, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6452, 0, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6829, 0, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6075, 451, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6452, 451, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6829, 451, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6075, 902, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6452, 902, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6829, 902, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6075, 1353, 377, 451));

	player.getAnimatedSprite().setTime(seconds(0.03f));
}
void ThrowAttackPlayerState::exit(Player &player)
{
	DEBUG_MSG("Exiting ThrowAttackPlayerState");
	DEBUG_MSG(typeid(player).name());
}