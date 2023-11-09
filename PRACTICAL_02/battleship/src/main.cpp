#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;



enum WarHead {
    EXPLOSIVE,
    NUCLEAR
};

const int MAXSHIPS = 3;
int XcordArray[MAXSHIPS];
int YcordArray[MAXSHIPS];

int enemyshipsXcords[MAXSHIPS];
int enemyshipsYcords[MAXSHIPS];

int pos_x = 0;
int pos_y = 0;

int code;
int codeInput;

WarHead selectWarhead() {
    srand(static_cast<unsigned>(time(0)));

    cout << "Choose your warhead" << '\n';
    cout << endl;
    cout << "N = Nuclear" << endl;
    cout << "E = Explosive" << endl;
    cout << endl;

    char input = cin.get();

    WarHead selected = WarHead::EXPLOSIVE;

    if (input == 'n') {
        selected = WarHead::NUCLEAR;
        cout << "You have selected Nuclear" << endl;
        code = (rand() % 8999) + 1000;
        cout << "Your launch code is: " << code << endl;
        cout << "Enter the code if you want to start the war: " << endl;
        cin >> codeInput;
        cout << endl;
    } else if (input == 'e') {
        cout << "You have selected Explosive" << endl;
        code = (rand() % 8999) + 1000;
        cout << "Your launch code is: " << code << endl;
        cout << "Enter the code if you want to start the war: " << endl;
        cin >> codeInput;
        cout << endl;
    }
    return selected;
}

void placeships() {
    int count = 1;
    for (int i = 0; i < MAXSHIPS; i++) {
        cout << "Enter X & Y position between 1 - 3 for ship " << count << endl;
        bool validInput = false;

        while (!validInput) {
            cin >> XcordArray[i] >> YcordArray[i];

            // Check if input is within the valid range
            if (XcordArray[i] >= 1 && XcordArray[i] <= 3 && YcordArray[i] >= 1 && YcordArray[i] <= 3) {
                validInput = true;

                // Check if the position matches a previously entered one
                bool duplicate = false;
                for (int j = 0; j < i; j++) {
                    if (XcordArray[i] == XcordArray[j] && YcordArray[i] == YcordArray[j]) {
                        duplicate = true;
                        break;
                    }
                }

                if (duplicate) {
                    cout << "You already have a ship there. Enter a different position." << endl;
                    validInput = false;
                }
            } 
            else {
                cout << "ERROR: Enter another position of X & Y between 1 - 3" << endl;
            }
        }

        cout << "Ship " << count << " position is X = " << XcordArray[i] << ", Y = " << YcordArray[i] << endl;
        count++;
    }
}

void Enemyships() {
    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < MAXSHIPS; i++) {
        int x, y;
        bool uniquePosition = false;

        while (!uniquePosition) {
            x = (rand() % 3) + 1;
            y = (rand() % 3) + 1;
            uniquePosition = true;

            // Check if the new position matches any previously placed enemy ship
            for (int j = 0; j < i; j++) {
                if (x == enemyshipsXcords[j] && y == enemyshipsYcords[j]) {
                    uniquePosition = false;
                    break;
                }
            }
        }

        enemyshipsXcords[i] = x;
        enemyshipsYcords[i] = y;

        cout << "Enemy Ship " << (i + 1) << " Position = X: " << x << ", Y: " << y << endl;
    }
}


void Firing() {
    cout << "Please enter the X & Y Position you want to shoot at." << endl;
    cin >> pos_x >> pos_y;

    // Check if input is within the valid range
    if (pos_x < 1 || pos_x > 3 || pos_y < 1 || pos_y > 3) {
        cout << "ERROR: Enter a valid position within the range 1 - 3" << endl;
        Firing(); // Re-prompt for input
    }
}

void checkHit() {
    bool hit = false;

    for (int i = 0; i < MAXSHIPS; i++) {
        if (pos_x == enemyshipsXcords[i] && pos_y == enemyshipsYcords[i]) {
            hit = true;
            enemyshipsXcords[i] = -1; // Mark the ship as hit
            enemyshipsYcords[i] = -1;
            break; // No need to check other ships
        }
    }

    if (hit) {
        cout << "You hit an enemy ship!" << endl;
    } else {
        cout << "You missed" << endl;
    }
}

void enemyFiring() {
    int ene_X = (rand() % 3) + 1; // Random number between 0 and 8
    int ene_Y = (rand() % 3) + 1; // Random number between 0 and 8

    bool hit = false;

    for (int i = 0; i < MAXSHIPS; i++) {
        if (ene_X == XcordArray[i] && ene_Y == YcordArray[i]) {
            hit = true;
            XcordArray[i] = -1; // Mark the player's ship as hit
            YcordArray[i] = -1;
            break; // No need to check other player's ships
        }
    }

    if (hit) {
        cout << "The enemy has sunk one of your battleships." << endl;
    } else {
        cout << "The enemy missed their shot." << endl;
    }
}

int main() {
    selectWarhead();
    placeships();
    Enemyships();

    int enemyShipsRemaining = MAXSHIPS;
    int playerShipsRemaining = MAXSHIPS;

    while (enemyShipsRemaining > 0 && playerShipsRemaining > 0) {
        Firing();
        checkHit();
        enemyFiring();

        // Check how many enemy and player ships remain
        enemyShipsRemaining = 0;
        playerShipsRemaining = 0;

        for (int i = 0; i < MAXSHIPS; i++) {
            if (enemyshipsXcords[i] != -1) {
                enemyShipsRemaining++;
            }
            if (XcordArray[i] != -1) {
                playerShipsRemaining++;
            }
        }
    }

    if (enemyShipsRemaining == 0) {
        cout << "You've sunk all enemy ships! You win!" << endl;
    } else {
        cout << "The enemy has sunk all your ships. You lose!" << endl;
    }

    return 0;
}