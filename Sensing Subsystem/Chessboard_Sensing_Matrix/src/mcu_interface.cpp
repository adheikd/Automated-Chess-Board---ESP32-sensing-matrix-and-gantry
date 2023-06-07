/*
    This C++ file defines functions that control operations over UART to the main processor, including:
        - Sending when a move has been made, and describing the move
        - Sending the state of the board

    A GPIO will be set to low/high to indicate when a move is expected to occur
*/
#include "moves.h"
#include <chessboard.h>
#include <mcu_interface.h>



void init_interface()
{
  pinMode(COM,INPUT);
  pinMode(ENDMOVE,INPUT);
}

void print_board_state_debug()
{
  for (int i = 0; i < dim; i++)
  {
    for (int j = 0; j < dim; j++)
    {
      if (board[i][j])
      {
        Serial.print("T");
      }
      else
      {
        Serial.print("F");
      }
    }
    Serial.println();
  }
  
  Serial.println('\n');
}

void print_board_state_interface()
{
  for (int i = 0; i < dim; i++)
  {
    for (int j = 0; j < dim; j++)
    {
      if (board[i][j])
      {
        Serial2.print("T");
      }
      else
      {
        Serial2.print("F");
      }
    }
    Serial2.println();
  }
  
  Serial2.println('\n');
}

void print_move_list()
{
  Serial.println(moveList.size());
  for (PosChange m : moveList)
  {
    Serial.print(m.row);
    Serial.print(", ");
    Serial.print(m.col);
    Serial.print(", ");
    switch (m.direc)
    {
      case Delta::lift: 
      {
        Serial.print("Lift");
        break;
      }
      case Delta::place: 
      {
        Serial.print("Place");
        break;
      }
      default:
      {}
    }
    Serial.println();
  }
  Serial.println('\n');
  
}

char char_index(int n)
{
    assert(n >= 0 && n <= 25);
    return "abcdefghijklmnopqrstuvwxyz"[n];
}