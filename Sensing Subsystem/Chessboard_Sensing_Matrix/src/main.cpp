#include <Arduino.h>
#include <Mux.h>
#include <chessboard.h>
#include <uart.h>
#include <moves.h>

//
//  PIN DEFINITIONS
//



void setup() 
{
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 15, 13);

  HardwareSerial debug = Serial;
  HardwareSerial processor = Serial2;
  
  // Set LED pin mode
  pinMode(LED,OUTPUT);
  //pinMode(HALL1,INPUT);

  HardwareSerial debug = Serial;
  init_chessboard();
}

void loop() 
{
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
  
  // Prints board state to serial
  
  print_board_state();
  delay(500);
  
}