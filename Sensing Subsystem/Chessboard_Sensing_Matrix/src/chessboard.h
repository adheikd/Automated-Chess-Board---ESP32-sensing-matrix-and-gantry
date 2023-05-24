/*
    This library file declares functions that interact with the multiplexer and 
    hall effect sensors to determine the current state of the chessboard.
    These values will be stored in a 2D array.
*/
#include <Arduino.h>
#include <Mux.h>


#define LED 2 
#define HALL1 27
#define HALL2 14
#define HALL3 12

// Swap order for PCB version - will make more sense on layout
#define MUX_S0 17
#define MUX_S1 5
#define MUX_S2 18

#define MUX_EN 19
#define MUX_Z 16

// For reading GPIO values
int hallState;

using namespace admux;
Mux rowselect(Pin(MUX_Z,OUTPUT,PinType::Digital),Pinset(MUX_S0,MUX_S1,MUX_S2));

// Arrays for easily reading values from MUX

// The size of the chessboard
#define dim 3
// 2D array; contains each board's state, each row represents the 
bool board[dim][dim];
uint8_t mux_sel[3];
uint8_t cols[dim];


/*
    Initializes the multiplexer object and sensor input GPIOs
*/
void init_chessboard();