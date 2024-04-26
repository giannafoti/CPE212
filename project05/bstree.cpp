// ****************************************
// Program Title: Project05
// Project File: bstree.cpp
// Name: Gianna Foti
// Course Section: CPE-212-01
// Due Date: 11/05/23
// Program description: trees ya'll
// ****************************************
#include <iostream>
#include <new>
#include "bstree.h"
using namespace std;

//Public Functions

template<typename SomeType>
BSTree<SomeType>::BSTree()
{
    rootPtr = NULL;
}
// BSTree()
// Default constructor initializes root pointer to NULL
template<typename SomeType>
BSTree<SomeType>::BSTree(const BSTree<SomeType>& someTree)
{
    CopyTree(rootPtr, someTree.rootPtr);
}
// BSTree()
// Copy constructor for BSTree
// Hint: calls CopyTree


template<typename SomeType>
void BSTree<SomeType>::operator=(const BSTree<SomeType>& originalTree)
{
    if (this != &originalTree)
    {
        MakeEmpty();
        CopyTree(rootPtr, originalTree.rootPtr);
    }
}
// operator=()
// Overloaded assignment operator for BSTree.
// Hint: calls CopyTree


template<typename SomeType>
BSTree<SomeType>::~BSTree()
{
    Destroy(rootPtr);
}
// ~BSTree()
// Destructor deallocates all tree nodes
// Hint: calls the private helper function Destroy
template<typename SomeType>
void BSTree<SomeType>::InsertItem(SomeType item)
{
    try
    {
        Insert(rootPtr, item);
    }
    catch (const bad_alloc&)
    {
        throw FullBSTree();
    }
    catch (const FoundInBSTree&)
    {
        throw FoundInBSTree();
        
    }
}
// InsertItem()
// Inserts item into BSTree; if tree already full, throws FullBSTree exception
// If item is already in BSTree, throw FoundInBSTree exception
// Hint: calls the private helper function Insert
template<typename SomeType>
SomeType BSTree<SomeType>::DeleteItem(SomeType item)
{
    if (rootPtr == NULL)
    {
        throw EmptyBSTree();
    }

    try 
    {
        Delete(rootPtr, item);
        return item;
    }
    catch (const NotFoundBSTree&)
    {
        throw NotFoundBSTree();
    }
}
// DeleteItem()
// Deletes item from BSTree if item is present AND returns object via function return value
// If tree is empty, throw the EmptyBSTree exception
// If tree is not empty and item is NOT present, throw NotFoundBSTree
// Hint: calls the private helper function Delete


template<typename SomeType>
void BSTree<SomeType>::MakeEmpty()
{
    Destroy(rootPtr);
}
// MakeEmpty()
// Deallocates all BSTree nodes and sets root pointer to NULL
// Hint: calls the private helper function Destroy
template<typename SomeType>
int BSTree<SomeType>::Size() const
{
    return CountNodes(rootPtr);
}
// Size()
// Returns total number of data values stored in tree
template<typename SomeType>
bool BSTree<SomeType>::IsFull() const
{
    BSTreeNode<SomeType>* newNode;
    try
    {
        newNode= new BSTreeNode<SomeType>;
        delete newNode;
        return false;
    }
    catch( bad_alloc )
    {
       return true;
    }
}
// IsFull()
// Returns true if BSTree is full; returns false otherwise
template<typename SomeType>
bool BSTree<SomeType>::IsEmpty() const
{
    if(rootPtr==NULL)
    {
        return true; 
    }
    else
    {
        return false; 
    }
}
// IsEmpty()
// Returns true if BSTree is empty; returns false otherwise
template<typename SomeType>
SomeType BSTree<SomeType>::Min() const
{
    if (rootPtr == NULL) 
    {
        throw EmptyBSTree();
    } 
    else 
    {
        BSTreeNode<SomeType>* temp = rootPtr;
        while (temp->leftPtr != NULL) {
            temp = temp->leftPtr;
        }
        return temp->data;
    }
}
// Min()
// Returns minimum value in tree; throws EmptyBSTree if tree is empty
template<typename SomeType>
SomeType BSTree<SomeType>::Max() const
{
if (rootPtr == NULL) {
        throw EmptyBSTree();
    } 
    else 
    {
        BSTreeNode<SomeType>* temp = rootPtr;
        while (temp->rightPtr != NULL) {
            temp = temp->rightPtr;
        }
        return temp->data;
    }
}
// Max()
// Returns maximum value in tree; throws EmptyBSTree if tree is empty




template<typename SomeType>
int BSTree<SomeType>::TotalLevels() const
{
    if (rootPtr == NULL) 
    {
        throw EmptyBSTree();
    }
    return LevelCount(rootPtr);

}
// TotalLevels()
// Returns the maximum level value for current tree contents
// Levels are numbered 0, 1, ..., N-1. This function returns N
// Throws EmptyBSTree if empty
// Hint: calls the private helper function LevelCount
template<typename SomeType>
int BSTree<SomeType>::Level(SomeType item) const
{
    if (rootPtr == NULL) 
    {
        throw EmptyBSTree();
    }
    try 
    {
        return FindLevel(rootPtr, item);
    } 
    catch (const NotFoundBSTree&) 
    {
        throw NotFoundBSTree();
    }

}
// Level()
// Returns the level within the BSTree at which the value item is found
// If tree is empty, throws EmptyBSTree
// If tree is not empty and item is not found, throws NotFoundBSTree
// Hint: calls the private helper funtion FindLevel
/************** End of Functions You Must Implement ****************/


// Private Functions 
template <typename SomeType>
void BSTree<SomeType>::Delete(BSTreeNode<SomeType>*& treePtr, SomeType& item)
// Delete()
// Recursive function that traverses the tree starting at treePtr to locate the data value to be removed
// Once located, DeleteNode is invoked to remove the value from the tree
// If tree is not empty and item is NOT present, throw NotFoundBSTree
{
    if (treePtr==NULL)
    {
        throw NotFoundBSTree();
    }
    else if (item < treePtr->data)
        Delete(treePtr->leftPtr, item); // Look in left subtree.
    else if (item > treePtr->data)
        Delete(treePtr->rightPtr, item); // Look in right subtree.
    else 
    {
        item = treePtr->data;
        DeleteNode(treePtr);
    }
}

template <typename SomeType>
void BSTree<SomeType>::DeleteNode(BSTreeNode<SomeType>*& treePtr)
// DeleteNode()
// Removes the node pointed to by treePtr from the tree
// Hint:  calls GetPredecessor and Delete

{
    BSTreeNode<SomeType>* temp;
    temp = treePtr;
    if (treePtr->leftPtr == NULL)
    {
        BSTreeNode<SomeType>* temp = treePtr;
        treePtr = treePtr->rightPtr;
        delete temp;
    }
    else if (treePtr->rightPtr == NULL)
    {
        BSTreeNode<SomeType>* temp = treePtr;
        treePtr = treePtr->leftPtr;
        delete temp;
    }
    else
    {
        treePtr -> data = GetPredecessor(treePtr->leftPtr);
        Delete(treePtr->leftPtr, treePtr->data); // Delete predecessor node.
    }
}


template <typename SomeType>
void BSTree<SomeType>::Insert(BSTreeNode<SomeType>*& ptr, SomeType item)
// Insert()
// Recursive function that finds the correct position of item and adds it to the tree
// Throws FoundInBSTree if item is already in the tree
{
    if (ptr == NULL) 
    {
        ptr = new BSTreeNode<SomeType>;
        ptr->data = item;
        ptr->leftPtr = NULL;
        ptr->rightPtr = NULL;
    } 
    else if (item < ptr->data) 
    {
        Insert(ptr->leftPtr, item);
    } 
    else if (item > ptr->data) 
    {
        Insert(ptr->rightPtr, item);
    } 
    else 
    {
        throw FoundInBSTree();
    }
}

template <typename SomeType>
void BSTree<SomeType>::Destroy(BSTreeNode<SomeType>*& ptr)
// Destroy()
// Recursively deallocates every node in the tree pointed to by ptr
{
    if (ptr == NULL)
    {
        return; 
    }

    if (ptr != NULL)
    {
        Destroy(ptr->leftPtr);
        Destroy(ptr->rightPtr);
        delete ptr; 
        ptr = NULL; 
    }
}

template <typename SomeType>
void BSTree<SomeType>::CopyTree(BSTreeNode<SomeType>*& copy, const BSTreeNode<SomeType>* originalTree)
// CopyTree()
// Recursively copies all data from original tree into copy
{
    if (originalTree == NULL)
        copy = NULL;
else
{
    copy = new BSTreeNode<SomeType>;
    copy->data = originalTree->data;
    CopyTree(copy->leftPtr, originalTree->leftPtr);
    CopyTree(copy->rightPtr, originalTree->rightPtr);
}
}

template <typename SomeType>
SomeType BSTree<SomeType>::GetPredecessor(BSTreeNode<SomeType>* treePtr) const
// GetPredecessor()
// Finds the largest data value in the tree pointed to by treePtr and returns that data value
// as the functions return value
{
    while (treePtr->rightPtr != NULL)
    {
        treePtr = treePtr->rightPtr;
    }
    return treePtr-> data; 
}

template <typename SomeType>
int BSTree<SomeType>::CountNodes(BSTreeNode<SomeType>* treePtr) const
// CountNodes()
// Recursive function that counts every node in the tree pointed to by treePtr and returns the
// count as the function return value
{
    if (treePtr == NULL)
    {
        return 0;
    }
else
    return CountNodes(treePtr->leftPtr) + CountNodes(treePtr->rightPtr) + 1;
}

template <typename SomeType>
int BSTree<SomeType>::LevelCount(BSTreeNode<SomeType>* treePtr) const
// LevelCount()
// Recursive function that traverses the entire tree to determine the total number of levels in the tree
{
    if (treePtr == NULL) 
    {
        return 0;
    }
    return 1 + max(LevelCount(treePtr->leftPtr), LevelCount(treePtr->rightPtr));
}

template <typename SomeType>
int BSTree<SomeType>::FindLevel(BSTreeNode<SomeType>* treePtr, SomeType item) const
// FindLevel()
// Recursive function that traverses the tree looking for item and returns the level where
// item was found
{
    if (treePtr == NULL) 
    {
        throw NotFoundBSTree();
    }
    if (item == treePtr->data) {
        return 0;
    } else if (item < treePtr->data) {
        return 1 + FindLevel(treePtr->leftPtr, item);
    } else {
        return 1 + FindLevel(treePtr->rightPtr, item);
    }
}




