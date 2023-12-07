#ifndef JUMP_PLAYER_STATE_H
#define JUMP_PLAYER_STATE_H

#include <Player.h>
#include <PlayerState.h>

class JumpPlayerState : public PlayerState {
public:
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&);
	virtual void enter(Player&);
	virtual void exit(Player&);
private:
	sf::Clock m_clock;
};

#endif