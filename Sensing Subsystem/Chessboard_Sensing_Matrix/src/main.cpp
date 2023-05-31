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
  print_board_state(debug);
  delay(500);
}