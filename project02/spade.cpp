// spade .cpp file 

#include "spade.h"

Spade::Spade(int v) : BlackCard(v)
{
    SetSuit('S');
}

string Spade::Description() const
{
    return BlackCard::Description() + ", Suit =" + GetSuit();
}