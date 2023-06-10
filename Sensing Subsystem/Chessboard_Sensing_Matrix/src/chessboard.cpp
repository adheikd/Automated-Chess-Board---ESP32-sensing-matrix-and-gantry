/*
    This C++ file defines functions that interact with the multiplexer and 
    hall effect sensors to determine the current state of the chessboard.
    These values will be stored in a 2D array.
*/
#include <chessboard.h>

// Multiplexer definition; all pins included in this line are defined correctly by the Mux library
using namespace admux;
Mux rowselect(Pin(MUX_SIG,OUTPUT,PinType::Digital),Pinset(MUX_S0,MUX_S1,MUX_S2), MUX_EN);
// ** For some reason, channel 5 and 6 (rows 6 and 7 on the board) got swapped on the PCB; 
//    they are physically rewired to correct this but it could also be done in code

volatile bool board[dim][dim] = {0};
uint8_t mux_sel[3] = {MUX_S0,MUX_S1,MUX_S2};
uint8_t cols[dim] = {HALL1,HALL2,HALL3,HALL4,HALL5,HALL6,HALL7,HALL8};


void init_chessboard()
{
  // Sets mux as initially disabled
  rowselect.enabled(false);

  // Configures pins for columns/hall effect GPIOS
  for (int i = 0; i<dim; i++)
  {
    pinMode(cols[i],INPUT);
  }

  // Initializes board state array as false
  // ** This causes any placed pieces on startup to be seen as moves, would need to be addressed
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
    delay(300);
    for (int j = 0; j < dim; j++)
    {
      hallState = digitalRead(cols[j]);
      prevState = board[i][j];
      PosChange lastMove = moveList.back();
      board[i][j] = hallState == LOW;
      
      if (board[i][j] && !prevState)
      {
        moveList.push_back( PosChange(Position(i,j),Delta::place) );
      }
      if (!board[i][j] && prevState)
      {
        moveList.push_back( PosChange(Position(i,j),Delta::lift) );
      }
    }
  }

  rowselect.enabled(false);
}

