#ifndef CLIMB_PAUSE_PLAYER_STATE_H
#define CLIMB_PAUSE_PLAYER_STATE_H

#include <Player.h>
#include <PlayerState.h>

class ClimbPausePlayerState : public PlayerState {
public:
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&);
	virtual void enter(Player&);
	virtual void exit(Player&);
};

#endif