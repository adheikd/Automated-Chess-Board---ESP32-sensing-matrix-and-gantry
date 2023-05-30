/*
    This library file declares functions that interact with the multiplexer and 
    hall effect sensors to determine the current state of the chessboard.
    These values will be stored in a 2D array.
*/
#include <Arduino.h>
#include <Mux.h>

// For PCB, to be changed to:
/*
#define HALL1 12
#define HALL2 14
#define HALL3 27
#define HALL4 26
#define HALL5 25
#define HALL6 33
#define HALL7 32
#define HALL8 35
*/
#define HALL1 27
#define HALL2 14
#define HALL3 12

// For PCB, to be changed to:
/*
#define MUX_S0 5
#define MUX_S1 17
#define MUX_S2 16
*/
#define MUX_S0 17
#define MUX_S1 5
#define MUX_S2 18

// For PCB, change to:
/*
#define MUX_EN 19
#define MUX_SIG 18
*/
#define MUX_EN 19
#define MUX_SIG 16

// Communications pin - main processor sets this value low when it wants a move to be made
#define COM 36
#define ENDMOVE 37


using namespace admux;
Mux rowselect(Pin(MUX_SIG,OUTPUT,PinType::Digital),Pinset(MUX_S0,MUX_S1,MUX_S2));

// Arrays for easily reading values from MUX

// The size of the chessboard
#define dim 3
// 2D array; contains each board's state
volatile bool board[dim][dim];

//uint8_t mux_sel[3];
//uint8_t cols[dim];


/*
    Initializes the multiplexer object and sensor input GPIOs
*/
void init_chessboard();

/*
    Refreshes the state of the board; if any changes were detected, adds the data to the list of moves 
*/
void refresh_state();