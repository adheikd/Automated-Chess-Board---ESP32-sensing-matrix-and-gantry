/*
    This C++ file will define functions pertaining to the calculation 
    of what types of move has been made in a given period of time
*/
#include <list>
#include <map>
#include "moves.h"

std::list<PosChange> moveList = {};

void clean_moves()
{
    std::list<PosChange> workingList = {};

    for (PosChange p : moveList)
    {
        // If the working list is not yet of valid size, or the move is on a different position than the previous one...
        if (workingList.size() < 2 || (workingList.back().pos.row != p.pos.row || workingList.back().pos.col != p.pos.col))
        {
            // ...adds the most recent move to the list 
            workingList.push_back(p);
        }
        // Otherwise (if it's a reversed/unwanted move) then it pops the last move:
        else
        {
            workingList.pop_back();
        }
    }

    moveList.clear();

    for (PosChange p : workingList)
    {
        moveList.push_back(p);
    }
}

Move calculate_move()
{
    PosChange start = moveList.front();
    PosChange end = moveList.back();


    if (moveList.size() < 2 || moveList.front().direc == Delta::place)
    {
        // Returns default move (invalid, from A1 to A1)
        return Move();
    }
    // If the move is a simple position shift...
    else if (moveList.size() == 2)
    {
        return Move(start.pos,end.pos,MoveType::shift);
    }
    // If the move is a capture...
    else if (moveList.size() == 3)
    {
        return Move(start.pos,end.pos,MoveType::capture);
    }
    else { return Move(); }
}