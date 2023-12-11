#ifndef CLIMB_DOWN_PLAYER_STATE_H
#define CLIMB_DOWN_PLAYER_STATE_H

#include <Player.h>
#include <PlayerState.h>

class ClimbDownPlayerState : public PlayerState {
public:
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&);
	virtual void enter(Player&);
	virtual void exit(Player&);
};

#endif