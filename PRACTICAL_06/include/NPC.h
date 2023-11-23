#ifndef NPC_H
#define NPC_H

#include <./include/GameObject.h>

class NPC : public GameObject
{
public:
	NPC();
	NPC(Vector2f, String);
	~NPC();
};
#endif