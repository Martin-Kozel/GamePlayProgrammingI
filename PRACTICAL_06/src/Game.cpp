#include <./include/Game.h>

Game::Game() : window(sf::VideoMode(800, 600), "SFML Command Pattern") {

}

Game::~Game(){
    // Cleanup pointers
    delete player;
    delete npc;
}

void Game::initialize()
{
    // Pointer to Concrete Commands
    Command *moveUp = new MoveUpCommand();
    Command *moveDown = new MoveDownCommand();
    Command *moveLeft = new MoveLeftCommand();
    Command *moveRight = new MoveRightCommand();

    // Map Keys to Commands
    InputManager::getInstance()->keyCommand(Keyboard::W, moveUp);
    InputManager::getInstance()->keyCommand(Keyboard::S, moveDown);
    InputManager::getInstance()->keyCommand(Keyboard::A, moveLeft);
    InputManager::getInstance()->keyCommand(Keyboard::D, moveRight);

    // Init Player with Position and Texture
    player = new Player(Vector2f(100, 100), "./images/player/Player");
    // Init NPC with Position and Texture
    npc = new NPC(Vector2f(300, 200), "./images/npc/npc");
}

void Game::run()
{
    initialize();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::EventType::KeyPressed)
            {
                Command *command = InputManager::getInstance()->handleInput();

                // Excute command (Keys or Buttons not implemented could have an indication too in an else block)
                if (command)
                {
                    command->execute(player); // Excute command in Concrete Command
                    commands.push_back(command->copy()); // Required for Undo and Redo Copies Command to Commands List
                    index++;
                    commands.erase(commands.begin() + index + 1, commands.end()); // Remove command for Undo Redo list
                }

                else if (Keyboard::isKeyPressed(Keyboard::U) && index > 0)
                {
                    commands[index]->undo(player); // Execute Undo
                    index--;
                }

                else if (Keyboard::isKeyPressed(Keyboard::R) && (commands.begin() + index + 1) != commands.end())
                {
                    commands[index]->execute(player); // Execute Redo
                    index++;
                }
                else{
                    std::cout << "Command, Key or Button not Mapped" << std::endl;
                }
            }
        }

        update();
        draw();
    }
}

void Game::update()
{
    player->update();
    npc->update();
}

void Game::draw()
{
    window.clear(sf::Color::Black);
    player->draw(window);
    npc->draw(window);
    window.display();
}