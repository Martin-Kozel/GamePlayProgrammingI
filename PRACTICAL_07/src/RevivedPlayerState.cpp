#ifndef REVIVED_PLAYER_STATE_H
#define REVIVED_PLAYER_STATE_H

#include <Player.h>
#include <PlayerState.h>

class RevivedPlayerState : public PlayerState {
public:
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&);
	virtual void enter(Player&);
	virtual void exit(Player&);
private:
	sf::Clock m_clock;
};

#endif