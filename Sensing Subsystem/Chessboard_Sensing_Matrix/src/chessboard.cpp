/*
    This C++ file defines functions that interact with the multiplexer and 
    hall effect sensors to determine the current state of the chessboard.
    These values will be stored in a 2D array.
*/
#include "chessboard.h"

// Spot for multiplexer definition? \/


//
uint8_t mux_sel[3] = {MUX_S0,MUX_S1,MUX_S2};
uint8_t cols[dim] = {HALL1,HALL2,HALL3};


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

void refresh_state()
{
  int hallState = 0;

  for (int i = 0; i < dim; i++)
  {
    rowselect.write(HIGH,i);
    delay(20);
    for (int j = 0; j < dim; j++)
    {
      hallState = digitalRead(cols[j]);
      if (hallState == LOW) 
      {
        board[i][j] = true;
      }
      else
      {
        board[i][j] = false;
      }
    }
  }
}
