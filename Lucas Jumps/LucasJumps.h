#ifndef LUCAS_JUMPS_H
#define LUCAS_JUMPS_H

#include <windows.h>     // For setting console text colors (Windows-specific).
#include <conio.h>       // For console input/output functions.
#include <iostream>      // For standard input/output streams.
using namespace std;

class LucasJumps {
private:
    char board[7];       // Array representing the game board with 7 positions for tokens.
    bool gameOver;       // Boolean flag indicating whether the game is over.

    int ROWS = 7;       // Row size to avoid magic numbers

    // Constants representing color codes (Windows console colors).
    const int BLUE = 9;
    const int RED = 12;
    const int WHITE = 7;

    // Private member functions for internal game logic.
    void setTextColor(int color);      // Sets the console text color.
    bool canMoveForward(int position); // Checks if the token at 'position' can move forward.
    bool canJump(int position);        // Checks if the token at 'position' can jump over another token.
    bool checkGameOver();              // Checks if the game has reached a terminal state.


public:
    LucasJumps();                      // Constructor to initialize the game board and setup.

    // Public member functions accessible from outside the class.
    bool isValidMove(int position);    // Checks if a move at the given position is valid.
    char getToken(int position);       // Returns the token character at a specific position.
    bool isGameOver() const { return gameOver; } // Checks if the game is over (const for safety).
    bool makeMove(int position);       // Executes a move at the specified position if valid.
    void displayBoard();               // Displays the current board state to the console.
    bool isSolved();                   // Checks if the puzzle is in a solved state.
    void displayTitle();
    void displayIntroduction();
};

#endif // LUCAS_JUMPS_H
