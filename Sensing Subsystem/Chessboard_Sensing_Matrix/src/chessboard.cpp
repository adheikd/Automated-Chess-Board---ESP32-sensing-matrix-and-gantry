/*
    This C++ file defines functions that interact with the multiplexer and 
    hall effect sensors to determine the current state of the chessboard.
    These values will be stored in a 2D array.
*/
#include "chessboard.h"

// Spot for multiplexer definition? \/



// Initializes board state array as false
bool board[dim][dim] = {false};

uint8_t mux_sel[3] = {MUX_S0,MUX_S1,MUX_S2};
uint8_t cols[dim] = {HALL1,HALL2,HALL3};

int hallState = 0;

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
