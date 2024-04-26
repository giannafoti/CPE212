// red card .cpp file

//including the h file
#include "redcard.h"


//using class redcard and taking in a value and then setting the color to red 
RedCard::RedCard(int v) : Card(v)
{
    SetColor("Red");
}

//concatenating the color and using card description
string RedCard::Description() const
{
    return Card::Description() + ", Color =" + GetColor();
}