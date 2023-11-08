#include <iostream>
#include <cstdlib>
#include <ctime> // include real time
#include "Character.h"
#include "Troll.h"
#include "Orc.h"
#include "Weapons.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Make numbers random, thanks to time

    cout << endl;

    // Create the fighters
    Orc orc("Orc");
    Troll troll("Troll");

    Character* playerCharacter; // Make a pointer for the player
    Character* enemyCharacter;  // Another pointer for the enemy

    int playerChoice;

    // Ask to pick a warrior
    cout << "Choose your warrior:" << endl;
    cout << "1. Orc" << endl;
    cout << "2. Troll" << endl;
    cout << endl;
    cin >> playerChoice;

    if (playerChoice == 1) {
        playerCharacter = &orc;   // I chose Orc for the player
        enemyCharacter = &troll;  // Troll is the enemy

        cout << endl;
        cout << "You select " << playerCharacter->GetName() << ". Good luck!" << endl;
        cout << "-----------------------------------------------------------------------------" << endl; // end of the roound
    } else if (playerChoice == 2) {
        playerCharacter = &troll; // Troll is my warrior
        enemyCharacter = &orc;   // Orc is the enemy

        cout << endl;
        cout << "You take " << playerCharacter->GetName() << ". Wish good luck!" << endl;
        cout << "-----------------------------------------------------------------------------" << endl; // end of the round
    } else {
        cout << "Invalid choice." << endl;
        return 0;
    }

    // Get weapons
    Weapon playerSword(30, 2);
    Weapon playerShield(20, 1);
    Weapon playerBat(15, 1);

    while (orc.IsAlive() && troll.IsAlive()) {
        cout << "Your turn:" << endl;
        cout << endl;

        int playerActionChoice;

        // Choose attack or defend
        cout << "What will you do?" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Defend" << endl;
        cout << endl;
        cin >> playerActionChoice;

        if (playerActionChoice == 1) {
            int playerWeaponChoice;
            cout << endl;
            cout << "Choose your weapon:" << endl;
            cout << "1. Sword" << endl;
            cout << "2. Bat" << endl;
            cout << endl;
            cin >> playerWeaponChoice;

            if (playerWeaponChoice == 1) {
                // Player chooses sword
                Weapon* selectedPlayerWeapon = &playerSword;

                // Damage to enemy
                int damage = selectedPlayerWeapon->GetPower();
                int enemyHealth = enemyCharacter->GetHealth();
                int updatedEnemyHealth = enemyHealth - damage;
                enemyCharacter->TakeDamage(damage);
                cout << endl;
                cout << enemyCharacter->GetName() << " has less health now: " << updatedEnemyHealth << endl;
            } 
            else if (playerWeaponChoice == 2) {
                // Player chooses bat
                Weapon* selectedPlayerWeapon = &playerBat;

                // Hurt the enemy
                int damage = selectedPlayerWeapon->GetPower();
                int enemyHealth = enemyCharacter->GetHealth();
                int updatedEnemyHealth = enemyHealth - damage;
                enemyCharacter->TakeDamage(damage);
                cout << endl;
                cout << enemyCharacter->GetName() << " has less health now: " << updatedEnemyHealth << endl;
            } 
            else {
                cout << "Invalid choice." << endl;
            }
        } 
        else {
            playerCharacter->Defend(&playerShield);
        }

        cout << endl;
        cout << "Enemy's turn:" << endl;

        if (enemyCharacter->IsAlive()) {
            // Randomly choose the enemy's weapon (sword or bat)
            int enemyWeaponChoice = (rand() % 2) + 1;
            Weapon* enemySelectedWeapon = (enemyWeaponChoice == 1) ? &playerSword : &playerBat;

            if (enemySelectedWeapon == &playerSword && playerCharacter->IsDefendingWithShield()) {
                // I use the shield, no damage for me
                int damage = 0;
                playerCharacter->TakeDamage(damage);
                cout << endl;
                cout << playerCharacter->GetName() << " hides behind a shield, taking " << damage << " damage." << endl;
                cout << endl;
            } 
            else {
                // hurts enemy
                int damage = enemySelectedWeapon->GetPower();
                playerCharacter->TakeDamage(damage);
                cout << endl;
                cout << enemyCharacter->GetName() << " attacks " << playerCharacter->GetName() << " for " << damage << " damage." << endl;
                cout << endl;
            }
        }

        // Show the health
        cout << "Your Health: " << playerCharacter->GetHealth() << endl;
        cout << "Enemy's Health: " << enemyCharacter->GetHealth() << endl;
        cout << "-----------------------------------------------------------------------------" << endl; // end of the round

        // Check if the game is over
        if (!playerCharacter->IsAlive() || !enemyCharacter->IsAlive()) {
            break;
        }
    }

    // Game over message
    if (playerCharacter->IsAlive()) {
        cout << "You win!" << endl;
    } 
    else {
        cout << "Enemy wins!" << endl;
    }

    return 0;
}
