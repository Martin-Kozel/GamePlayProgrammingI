#include <./include/InputManager.h>

InputManager* InputManager::m_instance= nullptr;


InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

InputManager* InputManager::getInstance() {
	if (m_instance==nullptr) {
		m_instance = new InputManager();
	}
	return m_instance;
}

Command* InputManager::handleInput()
{
	int size = key_commands.size();
	for (int i = 0; i < size; i++) {
		if (Keyboard::isKeyPressed(key_commands[i].first)) {
			return key_commands[i].second;
		}
	}
	return NULL;
}

void InputManager::keyCommand(sf::Keyboard::Key key, Command * command)
{
	key_commands.push_back(std::pair<sf::Keyboard::Key, Command*>(key, command));
}