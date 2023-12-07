#ifndef CONCRETE_COMMANDS_H
#define CONCRETE_COMMANDS_H

#include <./include/Command.h>

class JumpCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		previous = gameobject->getPosition();
		gameobject->jump();
	}
	virtual void undo(GameObject *gameobject)
	{
		gameobject->setPosition(previous);
	}
	Command *copy()
	{
		return new JumpCommand(*this);
	}

private:
	Vector2f previous;
};

class ShieldCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		previous = gameobject->getPosition();
		gameobject->shield();
	}
	virtual void undo(GameObject *gameobject)
	{
		gameobject->setPosition(previous);
	}
	Command *copy()
	{
		return new ShieldCommand(*this);
	}

private:
	Vector2f previous;
};

class AttackCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		previous = gameobject->getPosition();
		gameobject->attack();
	}
	virtual void undo(GameObject *gameobject)
	{
		gameobject->setPosition(previous);
	}
	Command *copy()
	{
		return new AttackCommand(*this);
	}

private:
	Vector2f previous;
};

class SprintCommand : public Command
{
public:
	SprintCommand(float speed = 50.0f) : speed(speed) {}

	virtual void execute(GameObject *gameobject)
	{
		previous = gameobject->getPosition();
		gameobject->sprint(speed);
	}
	virtual void undo(GameObject *gameobject)
	{
		gameobject->setPosition(previous);
	}
	Command *copy()
	{
		return new SprintCommand(*this);
	}

	void setSpeed(float speed)
	{
		this->speed = speed;
	}

private:
	Vector2f previous;
	float speed;
};

class CrouchCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		previous = gameobject->getPosition();
		gameobject->crouch();
	}
	virtual void undo(GameObject *gameobject)
	{
		gameobject->setPosition(previous);
	}
	Command *copy()
	{
		return new CrouchCommand(*this);
	}

private:
	Vector2f previous;
};

class MoveUpCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		previous = gameobject->getPosition();
		gameobject->moveUp();
	}
	virtual void undo(GameObject *gameobject)
	{
		gameobject->setPosition(previous);
	}
	Command *copy()
	{
		return new MoveUpCommand(*this);
	}

private:
	Vector2f previous;
};

class MoveDownCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		previous = gameobject->getPosition();
		gameobject->moveDown();
	}
	virtual void undo(GameObject *gameobject)
	{
		gameobject->setPosition(previous);
	}
	Command *copy()
	{
		return new MoveDownCommand(*this);
	}

private:
	Vector2f previous;
};

class MoveLeftCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		previous = gameobject->getPosition();
		gameobject->moveLeft();
	}
	virtual void undo(GameObject *gameobject)
	{
		gameobject->setPosition(previous);
	}
	Command *copy()
	{
		return new MoveLeftCommand(*this);
	}

private:
	Vector2f previous;
};

class MoveRightCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		previous = gameobject->getPosition();
		gameobject->moveRight();
	}
	virtual void undo(GameObject *gameobject)
	{
		gameobject->setPosition(previous);
	}
	Command *copy()
	{
		return new MoveRightCommand(*this);
	}

private:
	Vector2f previous;
};

#endif // !CONCRETE_COMMANDS_H