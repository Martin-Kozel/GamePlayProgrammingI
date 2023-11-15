#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

// Enum to represent types of warheads
enum WarHead 
{
    EXPLOSIVE,
    NUCLEAR
};

const int MAXSHIPS = 3;
int XcordArray[MAXSHIPS];
int YcordArray[MAXSHIPS];
int width[MAXSHIPS];
int height[MAXSHIPS];

int enemyshipsXcords[MAXSHIPS];
int enemyshipsYcords[MAXSHIPS];
int enemyshipsWidth[MAXSHIPS];
int enemyshipsHeight[MAXSHIPS];

int missileSelect;
int missileX;
int missileY;
int missileRadius;

int enemyMissileY;
int enemyMissileX;
int enemyMissileRadius = 1;

int pos_x = 0;
int pos_y = 0;

int code;  // Variable to store launch code
int codeInput;  // Variable to store user input for launch code

// Function to allow the player to select a warhead and input launch code
WarHead selectWarhead() 
{
    srand(static_cast<unsigned>(time(0)));

    cout << "Choose your warhead" << '\n';
    cout << endl;
    cout << "N = Nuclear" << endl;
    cout << "E = Explosive" << endl;
    cout << endl;

    char input = cin.get();

    WarHead selected = WarHead::EXPLOSIVE;

    // Check user input and set the selected warhead
    if (input == 'n') 
    {
        selected = WarHead::NUCLEAR;
        cout << "You have selected Nuclear" << endl;
        code = (rand() % 8999) + 1000;  // Generate a random launch code
        cout << "Your launch code is: " << code << endl;

        int attempts = 3;  // Number of allowed attempts for entering the code
        bool gameFinished = false;

        // Allow the user to input the launch code with multiple attempts
        do 
        {
            cout << "Enter the code if you want to start the war: " << endl;
            cin >> codeInput;
            cout << endl;

            // Check if the entered code matches the generated code
            if (codeInput != code) 
            {
                attempts--;
                cout << "Incorrect code. " << attempts << " attempts remaining." << endl;

                if (attempts == 0) 
                {
                    cout << "Out of attempts. Aborting launch. Game over." << endl;
                    gameFinished = true;
                    break;  // Exit the loop if no attempts remaining
                }
            } 
            else 
            {
                cout << "Code accepted. Launching!" << endl;
                break;  // Exit the loop if the code is correct
            }
        } while (!gameFinished);  // Continue the loop until the correct code is entered or no attempts remaining
    } 
    
    else if (input == 'e') 
    {
        cout << "You have selected Explosive" << endl;
        code = (rand() % 8999) + 1000;  // Generate a random launch code
        cout << "Your launch code is: " << code << endl;

        int attempts = 3;  // Number of allowed attempts for entering the code
        bool gameFinished = false;

        // Allow the user to input the launch code with multiple attempts
        do 
        {
            cout << "Enter the code if you want to start the war: " << endl;
            cin >> codeInput;
            cout << endl;

            // Check if the entered code matches the generated code
            if (codeInput != code) 
            {
                attempts--;
                cout << "Incorrect code. " << attempts << " attempts remaining." << endl;

                if (attempts == 0) 
                {
                    cout << "Out of attempts. Aborting launch. Game over." << endl;
                    gameFinished = true;
                    break;  // Exit the loop if no attempts remaining
                }
            } 
            else 
            {
                cout << "Code accepted. Launching!" << endl;
                break;  // Exit the loop if the code is correct
            }
        } while (!gameFinished);  // Continue the loop until the correct code is entered or no attempts remaining
    }
    return selected;
}

// Function to allow the player to input ship positions
void Ships() 
{
    srand((unsigned)time(0));

    int count = 1;

    // Loop to input ship positions
    for (int i = 0; i < MAXSHIPS; i++) 
    {
        cout << "Enter X & Y position between 1 - 3 for ship " << count << endl;
        bool validInput = false;

        // Loop to validate and input ship positions
        while (!validInput) 
        {
            cin >> XcordArray[i] >> YcordArray[i];
            width[i] = 1;
            height[i] = 1;

            // Check if input is within the valid range
            if (XcordArray[i] >= 1 && XcordArray[i] <= 3 && YcordArray[i] >= 1 && YcordArray[i] <= 3) 
            {
                validInput = true;

                // Check if the position matches a previously entered one
                bool duplicate = false;
                for (int j = 0; j < i; j++) 
                {
                    if (XcordArray[i] == XcordArray[j] && YcordArray[i] == YcordArray[j]) 
                    {
                        duplicate = true;
                        break;
                    }
                }

                if (duplicate) 
                {
                    cout << "You already have a ship there. Enter a different position." << endl;
                    validInput = false;
                }
            } 
            else 
            {
                cout << "ERROR: Enter another position of X & Y between 1 - 3" << endl;
            }
        }

        cout << "Ship " << count << " position is X = " << XcordArray[i] << ", Y = " << YcordArray[i] << endl;
        count++;
    }
}

// Function to randomly generate enemy ship positions
void Enemyships() 
{
    srand(static_cast<unsigned>(time(0)));

    // Loop to generate enemy ship positions
    for (int i = 0; i < MAXSHIPS; i++) 
    {
        int x, y;
        bool uniquePosition = false;

        // Loop to ensure unique enemy ship positions
        while (!uniquePosition) 
        {
            x = (rand() % 3) + 1;
            y = (rand() % 3) + 1;
            uniquePosition = true;

            // Check if the new position matches any previously placed enemy ship
            for (int j = 0; j < i; j++) 
            {
                if (x == enemyshipsXcords[j] && y == enemyshipsYcords[j]) 
                {
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

// Function to allow the player to input firing position
void Firing() 
{
    cout << "Please enter the X & Y Position you want to shoot at." << endl;
    cin >> pos_x >> pos_y;

    // Check if input is within the valid range
    if (pos_x < 1 || pos_x > 3 || pos_y < 1 || pos_y > 3) 
    {
        cout << "ERROR: Enter a valid position within the range 1 - 3" << endl;
        Firing(); // Re-prompt for input
    }
}

// Function to check if a ship is hit
void checkHit() 
{
    bool hit = false;
    bool enemyHit = false;

    int ene_X = (rand() % 3) + 1; // Random number between 1 and 3
    int ene_Y = (rand() % 3) + 1; // Random number between 1 and 3

    // Loop to check if player or enemy ships are hit
    for(int i = 0; i <= MAXSHIPS; i++) 
    {
        double playerDistanceSquared = (enemyshipsXcords[i] - pos_x) * (enemyshipsXcords[i] - pos_x) + 
                                        (enemyshipsYcords[i] - pos_y) * (enemyshipsYcords[i] - pos_y);
        double enemyDistanceSquared = (XcordArray[i] - ene_X) * (XcordArray[i] - ene_X) + 
                                        (YcordArray[i] - ene_Y) * (YcordArray[i] - ene_Y);

        // Check if player or enemy ship is hit based on distance
        if(playerDistanceSquared <= missileRadius) 
        {
            hit = true;
            enemyshipsXcords[i] = -1; // Mark the ship as hit
            enemyshipsYcords[i] = -1;
            break; // No need to check other ships
        }
        else if(enemyDistanceSquared <= missileRadius) 
        {
            enemyHit = true;
            XcordArray[i] = -1; // Mark the ship as hit
            YcordArray[i] = -1;
            break; // No need to check other ships
        }
    }

    // Print messages based on whether a ship is hit
    if (hit) 
    {
        cout << "You hit an enemy ship!" << endl;
    } 
    else 
    {
        cout << "You missed" << endl;
    }

    if (enemyHit) 
    {
        cout << "The enemy has sunk one of your battleships." << endl;
    } 
    else 
    {
        cout << "The enemy missed their shot." << endl;
    }
}

int main() 
{
    // Call functions to initialize the game
    selectWarhead();
    Ships();
    Enemyships();

    // Variables to track remaining ships for player and enemy
    int enemyShipsRemaining = MAXSHIPS;
    int playerShipsRemaining = MAXSHIPS;

    // Main game loop
    while (enemyShipsRemaining > 0 && playerShipsRemaining > 0) 
    {
        // Player's turn
        Firing();
        checkHit();

        // Check how many enemy and player ships remain
        enemyShipsRemaining = 0;
        playerShipsRemaining = 0;

        for (int i = 0; i < MAXSHIPS; i++) 
        {
            if (enemyshipsXcords[i] != -1) 
            {
                enemyShipsRemaining++;
            }
            if (XcordArray[i] != -1) 
            {
                playerShipsRemaining++;
            }
        }
    }

    // Print game outcome based on remaining ships
    if (enemyShipsRemaining == 0) 
    {
        cout << "You've sunk all enemy ships! You win!" << endl;
    } else 
    {
        cout << "The enemy has sunk all your ships. You lose!" << endl;
    }

    return 0;
}
