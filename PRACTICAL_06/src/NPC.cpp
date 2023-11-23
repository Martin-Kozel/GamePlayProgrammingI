#include <./include/NPC.h>

NPC::NPC(){};
NPC::~NPC(){};

NPC::NPC(Vector2f position, String image)
{
	this->position = position;
	initialize(image);
}