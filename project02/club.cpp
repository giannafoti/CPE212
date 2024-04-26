// club .cpp file 

#include "club.h"

Club::Club(int v) : BlackCard(v)
{
    SetSuit('C');
}

string Club::Description() const
{
    return BlackCard::Description() + ", Suit =" + GetSuit();
}