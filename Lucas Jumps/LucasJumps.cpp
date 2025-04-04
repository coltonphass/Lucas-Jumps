#pragma warning(disable:6031)           // Disable specific warning 6031 (unused return value from _getch).
#include "LucasJumps.h"
#include <iostream>
using namespace std;


LucasJumps::LucasJumps() {              // Constructor to initialize the game board and set the game as active (not over)
    gameOver = false;                   // Initially, the game is not over


    for (int i = 0; i < ROWS; i++) {    // Initialize the board: 'B' (Blue) tokens on left, '_' (empty space) in middle, 'R' (Red) tokens on right
        if (i < 3) {
            board[i] = 'B';
        }
        else if (i == 3) {
            board[i] = '_';
        }
        else {
            board[i] = 'R';
        }
    }
}


void LucasJumps::setTextColor(int color) {             // Private function to set the console text color based on the token's color
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get handle to console
    SetConsoleTextAttribute(hConsole, color);          // Set text color in console
}

char LucasJumps::getToken(int position) {              // Returns the token at a given position, or '_' if the position is invalid
    if (position < 0 || position >= ROWS) {
        return '_';                                    // Return empty space if position is out of bounds
    }
    return board[position];
}

bool LucasJumps::isValidMove(int position) {            // Checks if the move at the specified position is valid
    // Validate input and ensure the chosen position is within range and not empty
    if (cin.fail() || position < 0 || \
        position >= ROWS || board[position] == '_') {
        return false;
    }

    char piece = board[position];                     // Retrieve the token at the given position

    if (piece == 'B' || piece == 'R') {               // Check if the token is 'B' or 'R' and if it can move forward or jump
        return canMoveForward(position) || canJump(position);
    }

    return false;
}

bool LucasJumps::canMoveForward(int position) {     // Checks if a token can move one space forward
    if (board[position] == 'B' && position < 6) {
        return board[position + 1] == '_';          // 'B' moves right
    }
    if (board[position] == 'R' && position > 0) {
        return board[position - 1] == '_';          // 'R' moves left
    }
    return false;
}

bool LucasJumps::canJump(int position) {           // Checks if a token can jump over an adjacent token
    if (board[position] == 'B' && position < 5) {
        return board[position + 2] == '_' && board[position + 1] != '_'; // 'B' jumps right
    }
    if (board[position] == 'R' && position > 1) {
        return board[position - 2] == '_' && board[position - 1] != '_'; // 'R' jumps left
    }
    return false;
}


bool LucasJumps::makeMove(int position) {                  // Executes a move at the specified position if valid
    if (gameOver || !isValidMove(position)) return false;  // Exit if the game is over or if the move is invalid

    char temp = board[position];                            // Store the current token

    if (board[position] == 'B' && canMoveForward(position)) {          // Move or jump logic for 'B' token moving right
        board[position] = board[position + 1];
        board[position + 1] = temp;
    }
    else if (board[position] == 'B' && canJump(position)) {
        board[position] = board[position + 2];
        board[position + 2] = temp;
    }

    else if (board[position] == 'R' && canMoveForward(position)) {     // Move or jump logic for 'R' token moving left
        board[position] = board[position - 1];
        board[position - 1] = temp;
    }
    else if (board[position] == 'R' && canJump(position)) {
        board[position] = board[position - 2];
        board[position - 2] = temp;
    }

    gameOver = checkGameOver();                                     // Update the game-over status after the move
    return true;
}

bool LucasJumps::checkGameOver() {                                  // Checks if the game is over based on the board state
    if (isSolved()) return true;                                    // Game is over if the puzzle is solved

    for (int i = 0; i < ROWS; i++) {                                  // Check if any valid moves remain; if not, game is over
        if (board[i] != '_' && isValidMove(i)) {
            return false;
        }
    }

    return true;
}


bool LucasJumps::isSolved() {                                // Checks if the board is in the solved state
    return
        (board[0] == 'R' && board[1] == 'R' && board[2] == 'R' &&
            board[3] == '_' &&
            board[4] == 'B' && board[5] == 'B' && board[6] == 'B');
}

void LucasJumps::displayBoard() {
    system("cls");                                          // Clear the console for a fresh display
    displayTitle();

    // Top Border
    setTextColor(WHITE);
    cout << "+";
    for (int i = 0; i < ROWS; i++) {
        cout << "---+";
    }
    cout << "\n";

    // Row with index numbers
    cout << "| ";
    for (int i = 0; i < ROWS; i++) {
        cout << i << " | ";
    }
    cout << "\n";

    // Middle Border
    cout << "+";
    for (int i = 0; i < ROWS; i++) {
        cout << "---+";
    }
    cout << "\n";

    // Display each board position with colors and tokens
    cout << "| ";
    for (int i = 0; i < ROWS; i++) {
        if (board[i] == 'B') {
            setTextColor(BLUE); // Set color for Blue token
            cout << "O";
        }
        else if (board[i] == 'R') {
            setTextColor(RED); // Set color for Red token
            cout << "O";
        }
        else {
            setTextColor(WHITE); // Set color for Empty slot
            cout << "_";
        }
        setTextColor(WHITE); // Reset color
        cout << " | ";
    }
    cout << "\n";

    // Bottom Border
    cout << "+";
    for (int i = 0; i < ROWS; i++) {
        cout << "---+";
    }
    cout << "\n";
}

// AESTHETICS
void LucasJumps::displayIntroduction() {
    cout << "**************************************************\n";
    cout << "*        Welcome to Lucas Jumps Puzzle!          *\n";
    cout << "**************************************************\n\n";

    cout << "RULES:\n";
    cout << "*-----------------------------------------------------------------*\n";
    cout << "| Enter a position number to move the token at that position.     |\n";
    cout << "| Blue tokens move to the right, Red tokens move to the left.     |\n";
    cout << "| Your goal is to swap the positions of all the tokens.           |\n";
    cout << "*-----------------------------------------------------------------*\n";
    cout << "Press any key to start...\n";
    _getch();
}


void LucasJumps::displayTitle() {
    setTextColor(WHITE);

    cout << R"(
  ___       ___  ___  ________  ________  ________              ___  ___  ___  _____ ______   ________  ________      
|\  \     |\  \|\  \|\   ____\|\   __  \|\   ____\            |\  \|\  \|\  \|\   _ \  _   \|\   __  \|\   ____\     
\ \  \    \ \  \\\  \ \  \___|\ \  \|\  \ \  \___|_           \ \  \ \  \\\  \ \  \\\__\ \  \ \  \|\  \ \  \___|_    
 \ \  \    \ \  \\\  \ \  \    \ \   __  \ \_____  \        __ \ \  \ \  \\\  \ \  \\|__| \  \ \   ____\ \_____  \   
  \ \  \____\ \  \\\  \ \  \____\ \  \ \  \|____|\  \      |\  \\_\  \ \  \\\  \ \  \    \ \  \ \  \___|\|____|\  \  
   \ \_______\ \_______\ \_______\ \__\ \__\____\_\  \     \ \________\ \_______\ \__\    \ \__\ \__\     ____\_\  \ 
    \|_______|\|_______|\|_______|\|__|\|__|\_________\     \|________|\|_______|\|__|     \|__|\|__|    |\_________\
                                           \|_________|                                                  \|_________|
    )" << endl;
}