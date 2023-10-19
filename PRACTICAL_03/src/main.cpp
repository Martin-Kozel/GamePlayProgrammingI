#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Character.h"
#include "Troll.h"
#include "Orc.h"
#include "Weapons.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Initialize the random number generator

    cout << endl;

    Orc orc("Orc");
    Troll troll("Troll");

    Character* playerCharacter; // Declare a pointer to the player character
    Character* enemyCharacter;  // Declare a pointer to the enemy character

    int playerChoice;

    // Prompt the user to choose a character
    cout << "Choose your character:" << endl;
    cout << "1. Orc" << endl;
    cout << "2. Troll" << endl;
    cout << endl;
    cin >> playerChoice;

    if (playerChoice == 1) {
        playerCharacter = &orc;   // Assign the player pointer to the Orc character
        enemyCharacter = &troll;  // Assign the enemy pointer to the Troll character

        cout << endl;
        cout << "You've selected " << playerCharacter->GetName() << ". Good luck!" << endl;
        cout << "-----------------------------------------------------------------------------" << endl;
    } else if (playerChoice == 2) {
        playerCharacter = &troll;
        enemyCharacter = &orc;

        cout << endl;
        cout << "You've selected " << playerCharacter->GetName() << ". Good luck!" << endl;
        cout << "-----------------------------------------------------------------------------" << endl;
    } else {
        cout << "Invalid choice." << endl;
        return 0;
    }

    Weapon playerSword(30, 2);
    Weapon playerShield(20, 1);
    Weapon playerBat(15, 1);

    while (orc.IsAlive() && troll.IsAlive()) {
        cout << "Your turn:" << endl;
        cout << endl;

        int playerActionChoice;

        // Prompt the player to choose an action (attack or defend)
        cout << "Choose your action:" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Defend" << endl;
        cout << endl;
        cin >> playerActionChoice;

        if (playerActionChoice == 1) {
            int playerWeaponChoice;
            cout << endl;
            cout << "Select your weapon:" << endl;
            cout << "1. Sword" << endl;
            cout << "2. Bat" << endl;
            cout << endl;
            cin >> playerWeaponChoice;

            if (playerWeaponChoice == 1) {
                // Assign the sword to the selected weapon pointer
                Weapon* selectedPlayerWeapon = &playerSword;

                // Calculate damage and update the enemy's health
                int damage = selectedPlayerWeapon->GetPower();
                int enemyHealth = enemyCharacter->GetHealth();
                int updatedEnemyHealth = enemyHealth - damage;
                enemyCharacter->TakeDamage(damage);
                cout << endl;
                cout << enemyCharacter->GetName() << "'s health is now " << updatedEnemyHealth << endl;
            } else if (playerWeaponChoice == 2) {
                Weapon* selectedPlayerWeapon = &playerBat;

                // Calculate damage and update the enemy's health
                int damage = selectedPlayerWeapon->GetPower();
                int enemyHealth = enemyCharacter->GetHealth();
                int updatedEnemyHealth = enemyHealth - damage;
                enemyCharacter->TakeDamage(damage);
                cout << endl;
                cout << enemyCharacter->GetName() << "'s health is now " << updatedEnemyHealth << endl;
            } else {
                cout << "Invalid weapon choice." << endl;
            }
        } else {
            playerCharacter->Defend(&playerShield);
        }

        cout << endl;
        cout << "Enemy's turn:" << endl;

        if (enemyCharacter->IsAlive()) {
            // Randomly select the enemy's weapon (sword or bat)
            int enemyWeaponChoice = (rand() % 2) + 1;
            Weapon* enemySelectedWeapon = (enemyWeaponChoice == 1) ? &playerSword : &playerBat;

            if (enemySelectedWeapon == &playerSword && playerCharacter->IsDefendingWithShield()) {
                // Player defends with a shield, takes no damage
                int damage = 0;
                playerCharacter->TakeDamage(damage);
                cout << endl;
                cout << playerCharacter->GetName() << " defends with a shield, taking " << damage << " damage." << endl;
                cout << endl;
            } else {
                // Calculate damage and update player's health
                int damage = enemySelectedWeapon->GetPower();
                playerCharacter->TakeDamage(damage);
                cout << endl;
                cout << enemyCharacter->GetName() << " attacks " << playerCharacter->GetName() << " for " << damage << " damage." << endl;
                cout << endl;
            }
        }

        // Display player and enemy health
        cout << "Player's Health: " << playerCharacter->GetHealth() << endl;
        cout << "Enemy's Health: " << enemyCharacter->GetHealth() << endl;
        cout << "-----------------------------------------------------------------------------" << endl;

        // Check for game over conditions
        if (!playerCharacter->IsAlive() || !enemyCharacter->IsAlive()) {
            break;
        }
    }

    // Game over message
    if (playerCharacter->IsAlive()) {
        cout << "Congratulations! You've won!" << endl;
    } else {
        cout << "The enemy has triumphed!" << endl;
    }

    return 0;
}
