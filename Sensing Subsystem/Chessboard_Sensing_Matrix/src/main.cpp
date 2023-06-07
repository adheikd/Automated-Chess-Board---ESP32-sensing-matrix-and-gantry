#include <Arduino.h>
#include <Mux.h>
#include "chessboard.h"
#include "mcu_interface.h"
#include "moves.h"

//
//  PIN DEFINITIONS
//

void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 15, 13);

  init_chessboard();
}

void loop() 
{ 
  // Prints board state to serial
  if (digitalRead(COM) == LOW)
  {
    // Clears the movelist at the start of a new move
    moveList.clear();

    // Continually refreshes the board state while the ENDMOVE button has 
    // not been pressed and the main board still wants a move 
    while (digitalRead(ENDMOVE) == HIGH && digitalRead(COM) == LOW)
    {
      refresh_state();
      print_move_list();

    }

    
    
    delay(500);
  }
}