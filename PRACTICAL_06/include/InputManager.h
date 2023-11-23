#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <./include/Command.h>

// Singleton Input Manager

class InputManager
{
	
public:
	InputManager(InputManager &other) = delete;	   // Ensure not clonable
	void operator=(const InputManager &) = delete; // Ensure not assignable
	static InputManager *getInstance();			   // Public getInstance method, returns one instance of InputManager
	Command *handleInput();						   // returns the method mapped to input
	void keyCommand(sf::Keyboard::Key, Command *); // Map a Key to a Command
	
protected:
	InputManager();
	~InputManager();

private:
	static InputManager *m_instance;								   // instance of Input Manager
	std::vector<std::pair<sf::Keyboard::Key, Command *>> key_commands; // List of key to command mappings
};

#endif // !INPUT_MANAGER_H