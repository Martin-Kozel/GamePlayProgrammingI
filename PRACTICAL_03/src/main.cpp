#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Character.h"
#include "Orc.h"
#include "Troll.h"

using namespace std;

// Function to handle the attack
int HandleAttack(Character* attacker, Character* opponent) {
    int damageDealt = 0;

    if (attacker->batPower > 0) {
        // Attacker is using a Bat
        damageDealt = 20;
    } else if (attacker->swordPower > 0) {
        // Attacker is using a Sword
        damageDealt = 20;
    } else {
        cout << "You cannot attack with your current weapon." << endl;
    }

    if (opponent->shieldPower > 0) {
        damageDealt -= 30; // Opponent's shield reduces damage
    }

    // Update the opponent's health
    opponent->SetHealth(opponent->GetHealth() - damageDealt);

    return damageDealt;
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    Orc orc("Orc");
    // Initialize Orc-specific attributes here

    Troll troll("Troll");
    // Initialize Troll-specific attributes here

    Character* player = nullptr;
    Character* enemy = nullptr;

    int choice;
    cout << "Choose your class:\n1. Orc\n2. Troll\n";
    cin >> choice;

    if (choice == 1) {
        player = &orc;
        enemy = &troll;
        cout << "You chose " << player->GetName() << endl;
    } else {
        player = &troll;
        enemy = &orc;
        cout << "You chose " << player->GetName() << endl;
    }

    int action;
    cout << "Choose your action:\n1. Attack\n2. Defend\n";
    cin >> action;

    if (action == 1) {
        // Handle the attack logic
        int damageDealt = HandleAttack(player, enemy);

        cout << "You attacked the opponent and dealt " << damageDealt << " damage." << endl;

        int gameResult = 0; // 0 for a draw, 1 if player wins, -1 if enemy wins

        if (damageDealt == 0) {
            gameResult = 0; // Draw - the player couldn't attack
        } else if (damageDealt > 0) {
            if (enemy->GetHealth() <= 0) {
                gameResult = 1; // Player wins
            } else {
                gameResult = -1; // Enemy still has health left
            }
        } else {
            gameResult = -1; // Enemy's shield absorbed the attack
        }

        if (gameResult == 1) {
            cout << "You defeated the opponent!" << endl;
            // Handle rewards or further game actions for the player's victory
        } else if (gameResult == -1) {
            cout << "The opponent still stands!" << endl;
            // Handle consequences for the player's defeat
        } else {
            cout << "It's a draw. No one won this time." << endl;
            // Handle draw condition, if necessary
        }
    } else if (action == 2) {
        // Handle the defense logic (not implemented here)
        // Implement game economy based on the rules for defense
    } else {
        cout << "Invalid choice. Please choose 1 for Attack or 2 for Defend." << endl;
    }

    return 0;
}
