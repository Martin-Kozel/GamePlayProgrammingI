#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Character.h"
#include "Troll.h"
#include "Orc.h"
#include "Weapons.h"

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator
    cout << endl; // just an empty line to separate the output
    Orc orc("Orc"); // Create an Orc character
    Troll troll("Troll"); // Create a Troll character

    Character* player; // Declare a pointer to the player character
    Character* enemy; // Declare a pointer to the enemy character

    int choice;
    cout << "Choose your character:" << endl;
    cout << "1. Orc" << endl;
    cout << "2. Troll" << endl;
    cout << endl;
    cin >> choice;

    if (choice == 1) {
        player = &orc;  // Assign the player pointer to the Orc character
        enemy = &troll; //Assign the enemy pointer to the trolll character
        cout << endl;
        cout << "You chose " << player->GetName() << ". Good luck!" << endl;
        cout << endl;
    }

    else if (choice == 2) {
        player = &troll;
        enemy = &orc;
        cout << endl;
        cout << "You chose " << player->GetName() << ". Good luck!" << endl;
        cout << endl;
    }

    else{
        cout << "Invalid choice." << endl;
        return 0;
    }

    Weapon sword(30, 2);
    Weapon shield(20, 1);
    Weapon bat(15, 1);

    // Game loop
    while (orc.IsAlive() && troll.IsAlive()) {   // Continue the loop as long as both characters are alive
        // Player's turn
        cout << "Your turn:" << endl;
        cout << endl;
        int choiceOfAction;
        cout << "Choose your action:" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Defend" << endl;;
        cout << endl;
        cin >> choiceOfAction;

        if (choiceOfAction == 1) { // If the player chooses to attack
            int weapon;
            cout << endl;
            cout << "Choose your weapon:" << endl;
            cout << "1. Sword" << endl;
            cout << "2. Bat" << endl;
            cout << endl;
            cin >> weapon;



            Weapon* selectedWeapon;
            if (weapon == 1) {
                selectedWeapon = &sword; // Assign the sword to the selected Weapon pointer
            }

            else if (weapon == 2) {
                selectedWeapon = &bat;  // Assign the bat to the selected Weapon pointer
            }

            // Update the enemy's health here
            int damage = selectedWeapon->GetPower(); // Get the selected weapon's power
            int currentEnemyHealth = enemy->GetHealth();
            int newEnemyHealth = currentEnemyHealth - damage;
            enemy->TakeDamage(damage);
            cout << endl;
            cout << enemy->GetName() << "'s health is now " << newEnemyHealth << endl;
        }
        else {
            player->Defend(&shield);
        }


        // NPC's turn
        cout << endl;
        cout << "NPC's turn:" << endl;
        // Implement NPC action selection based on cooldown rules and weapon choice
        if (enemy->IsAlive()) {
            int enemyWeaponChoice = (rand() % 2) + 1; // Randomly choose between Sword (1) and Shield (2)
            Weapon* npcSelectedWeapon = (enemyWeaponChoice == 1) ? &sword : &bat;

            // Check if the selected weapon is a sword and if the player is defending with a shield
            if (npcSelectedWeapon == &sword && player->IsDefendingWithShield()) {
                int damage = 0;
                player->TakeDamage(damage);
                cout << endl;
                cout << player->GetName() << " defends with a shield, taking " << damage << " damage." << endl;
                cout << endl;
            }
            else
            {
                int damage = npcSelectedWeapon->GetPower();
                player->TakeDamage(damage);
                cout << endl;
                cout << enemy->GetName() << " attacks " << player->GetName() << " with " << damage << " damage." << endl;
                cout << endl;
            }
        }

        // Update character health and check for game over conditions
        cout << "Player's Health: " << player->GetHealth() << endl;
        cout << "Enemy's Health: " << enemy->GetHealth() << endl;
        cout << endl;

        if (!player->IsAlive() || !enemy->IsAlive()) {
            break;
        }
    }

    // Game over message
    if (player->IsAlive()) {
        cout << "The player wins!" << endl;
    }
    else {
        cout << "The enemy wins!" << endl;
    }

    return 0;
}