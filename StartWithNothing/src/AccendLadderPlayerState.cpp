#include <Events.h>

#include <AccendLadderPlayerState.h>

#include <ClimbUpPlayerState.h>
#include <RunRightPlayerState.h>
#include <DiedPlayerState.h>

PlayerState* AccendLadderPlayerState::handleInput(gpp::Events &input)
{
	if (input.getCurrent() == gpp::Events::Event::MOVE_UP_START_EVENT)
	{
		DEBUG_MSG("AccendLadderPlayerState -> ClimbUpPlayerState");
		return new ClimbUpPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::RUN_RIGHT_START_EVENT)
	{
		DEBUG_MSG("AccendLadderPlayerState -> RunRightPlayerState");
		return new RunRightPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT)
	{
		DEBUG_MSG("AccendLadderPlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	return nullptr;
}
void AccendLadderPlayerState::update(Player &player)
{
	DEBUG_MSG("AccendLadderPlayerState::update");
	DEBUG_MSG(typeid(player).name());
}
void AccendLadderPlayerState::enter(Player &player)
{
	DEBUG_MSG("Entering AccendLadderPlayerState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(sf::IntRect(1608, 464, 282, 464));

	player.getAnimatedSprite().setTime(seconds(0.05f));
}
void AccendLadderPlayerState::exit(Player &player)
{
	DEBUG_MSG("Exiting AccendLadderPlayerState");
	DEBUG_MSG(typeid(player).name());
}