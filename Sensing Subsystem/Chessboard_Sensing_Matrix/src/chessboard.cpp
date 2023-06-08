/*
    This C++ file defines functions that interact with the multiplexer and 
    hall effect sensors to determine the current state of the chessboard.
    These values will be stored in a 2D array.
*/
#include <chessboard.h>

// Spot for multiplexer definition? \/
using namespace admux;
Mux rowselect(Pin(MUX_SIG,OUTPUT,PinType::Digital),Pinset(MUX_S0,MUX_S1,MUX_S2), MUX_EN);

volatile bool board[dim][dim] = {0};
uint8_t mux_sel[3] = {MUX_S0,MUX_S1,MUX_S2};
uint8_t cols[dim] = {HALL1,HALL2,HALL3};


void init_chessboard()
{
    // Configures pins for multiplexer channels/row powering
  rowselect.enabled(false);
  
  // Configures pins for columns/hall effect GPIOS
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
  rowselect.enabled(true);
  int hallState = 0;
  bool prevState;
  delay(10);

  for (int i = 0; i < dim; i++)
  {
    rowselect.write(HIGH,i);
    delay(10);
    for (int j = 0; j < dim; j++)
    {
      hallState = digitalRead(cols[j]);
      prevState = board[i][j];
      PosChange lastMove = moveList.back();
      if (hallState == LOW) 
      {
        // If the spot was previously unoccupied, and the position is not hte  adds a 'place' PosChange to the movelist
        if (!prevState) { moveList.push_back( PosChange(Position(i,j),Delta::place) ); }
        board[i][j] = true;
        
      }
      else
      {
        // If the spot was previously occupied, adds a 'lift' PosChange to the movelist
        if (prevState) { moveList.push_back( PosChange(Position(i,j),Delta::lift) ); }
        board[i][j] = false;
      }
    }
  }

  rowselect.enabled(false);
}

