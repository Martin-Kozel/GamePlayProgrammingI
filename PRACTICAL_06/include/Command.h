#ifndef COMMAND_H
#define COMMAND_H

#include <./include/GameObject.h>

class Command
{
public:
	Command() {}
	virtual ~Command() {}
	virtual void execute(GameObject*) = 0;
	virtual void undo(GameObject*) = 0;
	virtual Command* copy() = 0; // used to Copy commands to a list (vector)
};

#endif // !COMMAND_H