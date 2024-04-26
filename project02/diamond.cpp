// diamond .cpp file

#include "diamond.h"

Diamond::Diamond(int v) : RedCard(v)
{
    SetSuit('D');
}

string Diamond::Description() const
{
    return RedCard::Description() + ", Suit =" + GetSuit();
}