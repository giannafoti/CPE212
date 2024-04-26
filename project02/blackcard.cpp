//Blackcard .cpp file

//including the h file
#include "blackcard.h"

//using class blackcard and taking in a value and then setting the color to black 
BlackCard::BlackCard(int v) : Card(v)
{
    SetColor("Black");
}

// using card description 
string BlackCard::Description() const
{
    return Card::Description() + ", Color =" + GetColor();
}