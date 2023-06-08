/*
    This C++ file defines functions that control operations over UART to the main processor, including:
        - Sending when a move has been made, and describing the move
        - Sending the state of the board

    A GPIO will be set to low/high to indicate when a move is expected to occur
*/
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
  for (PosChange m: moveList)
  {
    Serial.print(m.pos.row);
    Serial.print(", ");
    Serial.print(m.pos.col);
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

// Turns an index into a letter, in alphabetical order, starting with 0 -> a
char char_index(int n)
{
  assert(n >= 0 && n <= 25);
  return "abcdefghijklmnopqrstuvwxyz"[n];
}

void send_move(Move newMove)
{
  switch (newMove.type)
  {
    case MoveType::invalid:
    {
      Serial.println("invalid");
      break;
    }
    case MoveType::shift:
    {
      Serial.printf("shift %c%u %c%u",char_index(newMove.startPos.col),newMove.startPos.row,
                                      char_index(newMove.endPos.col), newMove.endPos.row);
      break;
    }
    case MoveType::capture:
    {
      Serial.printf("capture %c%u %c%u",char_index(newMove.startPos.col),newMove.startPos.row,
                                        char_index(newMove.endPos.col), newMove.endPos.row);
      break;
    }
  }
}