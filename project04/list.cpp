// ****************************************
// Program Title: Project04
// Project File: list.cpp
// Name: Gianna Foti
// Course Section: CPE-212-01
// Due Date: 10/22/23
// program description: Description of
// What the program does.
// ****************************************

#include <iostream>
#include <new>
#include "list.h"

using namespace std;

// Constructor
List::List()
{
    head = NULL; // Initialize the head pointer to NULL
    num = 0;     // Initialize the number of words to 0, aka empty
}

// Destructor
List::~List()
{
    while (head != NULL)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Append a word to the end of the list
void List::Append(string newword)
{
    try 
    {
        Node* newNode = new Node;
        newNode->word = newword;
        newNode->next = NULL;
        
        if (head == NULL) 
        {
            head = newNode;
        } 
        else 
        {
            Node* temp = head;
            while (temp->next != NULL) 
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        num++;
    } 
    catch (const bad_alloc&) 
    {
        throw ListFull();
    }
}

// Insert a word at a specified position
void List::InsertAt(int pos, string newword) 
{
    // if the position is out of range, throw
    if (pos < 0) 
    {
        throw ListBadPosition();
    }
    // if the position is full, throw
    if (pos > num) 
    {
        throw ListBadPosition();
    }

    if (pos == num) 
    {
        Append(newword);
    } 
    else 
    {
        Node* newNode = new Node;
        newNode->word = newword;
        if (pos == 0) 
        {
            newNode->next = head;
            head = newNode;
        }
        else 
        {
            Node* temp = head;
            for (int i = 0; i < pos - 1; i++) 
            {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
        num++;
    }
}

// Delete the first instance of a word
void List::Delete(string someword)
{
    Node* current = head;
    Node* previous = NULL;

    while (current != NULL)
    {
        if (current->word == someword)
        {
            if (previous == NULL)
            {
                head = current->next; // If the word is in the head node
            }
            else
            {
                previous->next = current->next;
            }

            delete current; // Deallocate the node
            num--; // Decrement the number of words in the list
            return;
        }
        previous = current;
        current = current->next;
    }
    throw ListNotFound(); // Word not found, throw ListNotFound object
}

// Replace the first instance of an old word with a new word
void List::Replace(string oldword, string newword)
{
    Node* current = head;
    while (current != NULL)
    {
        if (current->word == oldword)
        {
            current->word = newword; // Replace the word
            return;
        }
        current = current->next;
    }
    throw ListNotFound(); // Old word not found, throw ListNotFound object
}

// Get the number of words in the list
int List::Length() const
{
    return num;
}

// Check if a word is in the list
bool List::Find(string someword) const
{
    Node* current = head;
    while (current != NULL)
    {
        if (current->word == someword)
        {
            return true; // Word found
        }
        current = current->next;
    }
    return false; // Word not found
}

