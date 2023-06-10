#include <Arduino.h>
#include <Mux.h>
#include <mcu_interface.h>

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
  // Test that repeatedly prints the board state and movelist
  /*
  refresh_state();
  print_board_state_debug();

  clean_moves();
  print_move_list();
  delay(100);
  */

  // Main loop
  // When COM pin is put to low, main board wants a move to be sent...
  if (digitalRead(COM) == LOW)
  {
    // Clears the movelist at the start of a new move
    moveList.clear();

    // Continually refreshes the board state while the ENDMOVE button has 
    // not been pressed and the main board still wants a move 
    while (digitalRead(ENDMOVE) == HIGH && digitalRead(COM) == LOW)
    {
      refresh_state();
    }

    // Cleans up the movelist, and sends the move over serial calculated based off of the movelist variable
    clean_moves();
    send_move(calculate_move());
  }
}