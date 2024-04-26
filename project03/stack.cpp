// ****************************************
// Program Title: Project03
// Project File: stack.cpp
// Name: Gianna Foti
// Course Section: CPE-212-01
// Due Date: 10/01/23
// program description: Description of
// What the program does.
// ****************************************
#include <iostream>
#include <new>
#include "stack.h"
using namespace std;
// Parameterized constructor dynamically allocates an empty stack array
// that may hold no more than n elements and initializes other private variables
Stack::Stack(int n)
{
    array = new int[n];
    num = n;
    top = -1;
}
// Destructor deallocates all dynamically-allocated memory
// associated with the object

Stack::~Stack()
{
    delete[] array;
}
// Pushes integer n onto top of stack. If stack is full, attempts to
// resize stack and then push n. If unable to resize, throws StackFull exception.
void Stack::Push(int n)
{
    if (IsFull())
    {
        Resize(n);
    }
    else
    {
        array[++top] = n;
    }
}
// Removes top integer from stack
// If stack is empty, throws StackEmpty exception
void Stack::Pop()
{
    if (IsEmpty())
    {
        throw StackEmpty();
    }
    top--;
}
// Returns true if stack is empty; false otherwise
bool Stack::IsEmpty() const
{
    return (top == -1);
}
// Returns true if stack is full; false otherwise
bool Stack::IsFull() const
{
    return(top == (num-1));
}
// Removes all items from stack leaving an empty, but usable stack with capacity num
// If stack is already empty, MakeEmpty() does nothing
void Stack::MakeEmpty()
{
    top =-1;
}
// Returns value of top integer on stack WITHOUT modifying the stack
// If stack is empty, throws StackEmpty exception
int Stack::Top() const
{
    if (IsEmpty())
    {
        throw StackEmpty();
    }
    return array[top];
}
// Returns number of items on stack WITHOUT modifying the stack
int Stack::Size() const
{
    return top + 1;
}
// Returns value of largest integer on stack WITHOUT modifying the stack
// If stack is empty, throws StackEmpty
int Stack::Max () const
{
    if (IsEmpty())
    {
        throw StackEmpty ();
    }
    int maxVal = array [0];
    for (int i = 1; i <= top; i++)
    {
        if (array[i] > maxVal)
        {
            maxVal = array[i];
        }
    }
    return maxVal;
}
// Returns value of smallest integer on stack WITHOUT modifying the stack
// If stack is empty, throws StackEmpty
int Stack::Min() const
{
    if (IsEmpty())
    {
        throw StackEmpty();
    }
    int minVal = array [0];
    for (int i = 1; i <= top; i++)
    {
        if (array[i] < minVal)
        {
        minVal = array[i];
        }
    }
    return minVal;
}
// Returns stack value n levels down from top of stack. Peek(0) = Top()
// If position n does not exist, throws StackInvalidPeek
int Stack::Peek(unsigned int n) const
{
    if (n >= static_cast<unsigned int>(Size()))
    {
        throw StackInvalidPeek();
    }
    return array[top - n];
}
// Returns total num of elements that maybe stored in stack array
int Stack::Capacity () const
{
    return num;
}
// Resize function
void Stack::Resize(int n)
{
    try
    {
        int newCapacity = 2 * num;
        int* newArray = new int[newCapacity];
        for (int i = 0; i <= top; i++)
        {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        num = newCapacity;
        array[++top] = n;
    }
    catch (bad_alloc)
    {
        throw StackFull();
    }
}
