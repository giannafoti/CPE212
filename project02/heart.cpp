// heart .cpp file&

#include "heart.h"

Heart::Heart(int v) : RedCard(v)
{
    SetSuit('H');
}

string Heart::Description() const
{
    return RedCard::Description() + ", Suit =" + GetSuit();
}