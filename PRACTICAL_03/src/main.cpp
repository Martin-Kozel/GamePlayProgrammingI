#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Character.h"
#include "Orc.h"
#include "Troll.h"

using namespace std;

int main() 
{
    // srand(static_cast<unsigned>(time(nullptr)));

    Orc orc("Orc");
    Troll troll("Troll");

    Character* player;
    // Character* enemy;

    int choice;
    cout << "Choose your class:\n1. Orc\n2. Troll\n";
    cin >> choice;

    if(choice == 1) 
    {
        player = &orc;
        // enemy = &troll;
        cout << "You chose " << player->GetName() <<endl;
    }

    else 
    {
        player = &troll;
        // enemy = &orc;
        cout << "You chose " << player->GetName() << endl;
    }

//     cout << "Welcome to the battle between Orcs & Trolls!\n";

//     while(player->IsAlive() && enemy->IsAlive()) 
//     {
//         cout << "Choose your action:\n1. Attack\n2. Quit\n";
//         cin >> choice;

//         if(choice == 1) {
//             player->Attack(enemy);
//         }

//         else if(choice == 2) {
//             cout << "You quit the game\n";
//             break;
//         }

//         if(enemy->IsAlive()) {
//             enemy->Attack(player);
//         }
//     }

//     if(player->IsAlive())
//     {
//         cout << "Congratulations!" << player->GetName() << "wins!" << endl;
//     }

//     else
//     {
//         cout<< "Game over." << enemy->GetName() << "wins!" <<endl;
//     }

    return 0;
}