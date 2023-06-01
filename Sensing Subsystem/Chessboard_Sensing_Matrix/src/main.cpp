#include <Arduino.h>
#include <Mux.h>
#include <chessboard.h>
#include <uart.h>
#include <moves.h>

//
//  PIN DEFINITIONS
//

HardwareSerial debug = Serial;
HardwareSerial processor = Serial2;

void setup() 
{
  debug.begin(115200);
  processor.begin(115200, SERIAL_8N1, 15, 13);
  
  // Set LED pin mode
  //pinMode(LED,OUTPUT);

  init_chessboard();
}

void loop() 
{
  refresh_state();
  
  // Prints board state to serial
  //print_board_state(debug);
  /*
  for (int i = 0; i < dim; i++)
  {
    for (int j = 0; j < dim; j++)
    {
      if (board[i][j])
      {
        debug.print("T");
      }
      else
      {
        debug.print("F");
      }
    }
    debug.println();
  }*/
  
  debug.println();

  delay(50);
}