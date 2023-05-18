#include <Arduino.h>
#include "Mux.h"

//
//  PIN DEFINITIONS
//

#define LED 2 
#define HALL1 27
#define HALL2 14
#define HALL3 12

#define MUX_S0 17
#define MUX_S1 5
#define MUX_S2 18

#define MUX_EN 19
#define MUX_Z 16

// For reading GPIO values
int hallState = 0;

// Init multiplexer
using namespace admux;
Mux rowselect(Pin(MUX_Z,OUTPUT,PinType::Digital),Pinset(MUX_S0,MUX_S1,MUX_S2));

// Arrays for easily reading values from MUX

// The size of the chessboard
#define dim 3
bool board[dim][dim];
uint8_t mux_sel[3] = {MUX_S0,MUX_S1,MUX_S2};
uint8_t cols[dim] = {HALL1,HALL2,HALL3};

void setup() 
{
  Serial.begin(115200);
  // Set LED pin mode
  pinMode(LED,OUTPUT);
  //pinMode(HALL1,INPUT);

  // Set pins for multiplexer channels/row powering
  pinMode(MUX_EN,OUTPUT);
  digitalWrite(MUX_EN,LOW);
  for (int i = 0; i<dim; i++)
  {
    pinMode(mux_sel[i],OUTPUT);
  }
  

  // Set pins for columns/hall effect GPIOS
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
  
  delay(500);
  Serial.println();
  
}