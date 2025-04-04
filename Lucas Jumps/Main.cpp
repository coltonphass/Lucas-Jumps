#pragma warning(disable:6031)       // Disable specific warning 6031 (unused return value from _getch). 

using namespace std;
#include <conio.h>                  // For _getch() function, which waits for a key press without displaying it on the console.
#include <iostream>                 // For input and output streams (cin, cout).
#include "LucasJumps.h"             // Custom header file for the LucasJumps game logic class.

int main() {
    LucasJumps game;                // Create an instance of the LucasJumps class to manage game logic and state.
    int position = 0;               // Variable to store the user's chosen position for token movement.
    game.displayIntroduction();

    // Main game loop - continues until the game is marked as over.
    while (!game.isGameOver()) {
        game.displayBoard();        // Display the current state of the game board.
        cout << "Enter position to move (0-6): "; // Prompt the user for a move.
        cin >> position;

        // Validate the move. If invalid, prompt the user again.
        while (!game.isValidMove(position)) {
            cout << "Invalid move! Try again.\n";
            cin.clear();            // Clear the error flag on cin in case of invalid input.
            cin.ignore(1000, '\n'); // Discard any invalid input from the input buffer.
            _getch();               // Wait for any key to continue.
            game.displayBoard();    // Re-display the board after an invalid move.

            cout << "Enter position to move (0-6): ";
            cin >> position;        // Ask for a new position.
        }

        game.makeMove(position);    // Make the move if it’s valid.
    }

    game.displayBoard();            // Game has ended; display the final board state.

    // Check if the game is successfully solved and display appropriate message.
    if (game.isSolved()) {
        cout << "Congratulations! You solved the puzzle!\n";
    }
    else {
        cout << "Game Over! The puzzle is in a 'gimped' state.\n";
    }

    // Exit message.
    cout << "Press any key to exit...";
    _getch();                       // Wait for a final key press before exiting.
    return 0;
}
