/*
    This C++ file defines functions that interact with the multiplexer and 
    hall effect sensors to determine the current state of the chessboard.
    These values will be stored in a 2D array.
*/
#include <chessboard.h>

void init_chessboard()
{
    // Set pins for multiplexer channels/row powering
  pinMode(MUX_EN,OUTPUT);
  digitalWrite(MUX_EN,LOW);
  for (int i = 0; i<dim; i++)
  {
    pinMode(mux_sel[i],OUTPUT);
  }
  

  // Set pins for columns/hall effect GPIOS
  for (int i = 0; i<dim; i++)
  {
    pinMode(cols[i],INPUT);
  }

  // Initializes board state array as false
  for (int i = 0; i<dim; i++)
  {
    for (int j = 0; j<dim; j++)
    {
      board[i][j] = false;
    }
  }
}
