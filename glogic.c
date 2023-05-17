#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool isMoveValid(const char* move, char board[8][8]);

int main() {
  // Initialize the chess board
  char board[8][8] = {
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
  };

  // Print the initial state of the board
  printf("Initial state:\n");
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      printf("%c ", board[i][j]);
    }
    printf("\n");
  }

  // Play the game
  char player = 'W';
  while (true) {
    // Prompt the player for a move
    char move[5];
    printf("%c's move: ", player);
    scanf("%s", move);

    // Check if the move is valid
    if (!isMoveValid(move, board)) {
      printf("Invalid move\n");
      continue;
    }

    // Make the move
    int fromX = move[0] - 'a';
    int fromY = 8 - (move[1] - '0');
    int toX = move[2] - 'a';
    int toY = 8 - (move[3] - '0');
    board[toY][toX] = board[fromY][fromX];
    board[fromY][fromX] = ' ';

    // Print the new state of the board
    printf("New state:\n");
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        printf("%c ", board[i][j]);
      }
      printf("\n");
    }

    // Check if the game is over
    bool gameOver = true;
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if ((player == 'W' && islower(board[i][j])) ||
            (player == 'B' && isupper(board[i][j]))) {
          char move[5];
          sprintf(move, "%c%c%c%c", j + 'a', 8 - i + '0', j + 'a', 8 - i - 1 + '0');
          if (isMoveValid(move, board)) {
            gameOver = false;
            break;
          }
          sprintf(move, "%c%c%c%c", j + 'a', 8 - i + '0', j + 'a' + 1, 8 - i - 1 + '0');
          if (isMoveValid(move, board)) {
            gameOver = false;
           


bool isMoveValid(const char* move, char board[8][8]) {
  int fromX = move[0] - 'a';
  int fromY = 8 - (move[1] - '0');
  int toX = move[2] - 'a';
  int toY = 8 - (move[3] - '0');

  // Check if the from and to squares are the same
  if (fromX == toX && fromY == toY) {
    return false;
  }

  // Check if the piece at the from square belongs to the current player
  char piece = board[fromY][fromX];
  if ((piece == ' ' && toX != fromX) || (islower(piece) && board[7][fromX] != piece) ||
      (isupper(piece) && board[0][fromX] != piece)) {
    return false;
  }

  // Check if the move is legal for the piece type
  switch (toupper(piece)) {
    case 'P': // Pawn
      if (toX == fromX && board[toY][toX] == ' ') {
        // Moving straight ahead one square
        if ((toY == fromY + 1 && islower(piece)) || (toY == fromY - 1 && isupper(piece))) {
          return true;
        }
        // Moving straight ahead two squares from the starting position
        if (fromY == 1 && toY == 3 && islower(piece) && board[2][fromX] == ' ') {
          return true;
        }
        if (fromY == 6 && toY == 4 && isupper(piece) && board[5][fromX] == ' ') {
          return true;
        }
      } else if (abs(toX - fromX) == 1 && abs(toY - fromY) == 1 && board[toY][toX] != ' ') {
        // Capturing diagonally
        if ((toY == fromY + 1 && islower(piece)) || (toY == fromY - 1 && isupper(piece))) {
          return true;
        }
      }
      break;
    case 'R': // Rook
      if (toX == fromX || toY == fromY) {
        // Moving horizontally or vertically
        int stepX = (toX > fromX) ? 1 : ((toX < fromX) ? -1 : 0);
        int stepY = (toY > fromY) ? 1 : ((toY < fromY) ? -1 : 0);
        for (int x = fromX + stepX, y = fromY + stepY; x != toX || y != toY; x += stepX, y += stepY) {
          if (board[y][x] != ' ') {
            return false;
          }
        }
        return true;
      }
      break;
    case 'N': // Knight
      if ((abs(toX - fromX) == 1 && abs(toY - fromY) == 2) ||
          (abs(toX - fromX) == 2 && abs(toY - fromY) == 1)) {
        return true;
      }
      break;
  }
}

