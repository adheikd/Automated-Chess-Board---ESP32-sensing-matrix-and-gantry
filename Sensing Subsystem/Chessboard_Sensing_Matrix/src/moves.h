/*
    This library file will declare functions pertaining to the calculation 
    of what types of move has been made in a given period of time
*/
#include <list>

//Used to represent whether a move is a piece being placed or lifted
enum Delta
{
    place,
    lift
};

// Represents a position
struct Position
{
    int row;
    int col;

    Position(int _row = 0, int _col = 0) :
             row(_row), col(_col) {}
};


//Used to represent a change of position; has indices for row, column, and 
struct PosChange
{
    Position pos;
    enum Delta direc;

    PosChange(Position _pos, enum Delta _direc = Delta::place) :
              pos(_pos), direc(_direc) {}
};

// Define the list of moves
extern std::list<PosChange> moveList;

// The different types of moves that can be made
enum MoveType
{
    shift,
    capture,
    invalid
};

struct Move
{
    Position startPos;
    Position endPos;
    MoveType type;

    Move(Position _startPos = Position(), Position _endPos = Position(), MoveType _type = invalid) :
         startPos(_startPos), endPos(_endPos), type(_type) {}
};

// Cleans the list of move changes such that it's more easily read
void clean_moves();

// Calculates what type of move is needed, and returns it
Move calculate_move();