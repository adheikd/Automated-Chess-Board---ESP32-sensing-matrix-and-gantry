/*
    This C++ file defines functions that control operations over UART to the main processor, including:
        - Sending when a move has been made, and describing the move
        - Sending the state of the board

    A GPIO will be set to low/high to indicate when a move is expected to occur
*/
#include <Arduino.h>
#include <chessboard.h>
#include <uart.h>

void print_board_state(HardwareSerial serialport)
{
  for (int i = 0; i < dim; i++)
  {
    for (int j = 0; j < dim; j++)
    {
      if (board[i][j])
      {
        serialport.print("T");
      }
      else
      {
        serialport.print("F");
      }
    }
    serialport.println();
  }
  
  serialport.println();
}
