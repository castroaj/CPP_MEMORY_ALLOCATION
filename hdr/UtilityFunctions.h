/***********************************************************************
 * CS-450-PA2: Header file for general Utiliy functions that will be 
 *             used by assorted classes.
 * @file UtilityFunctions.h
 * @author Alexander Castro
 * @version 1.0 10/4/20
 ***********************************************************************/
#include "Driver.h"
#include "MemoryOperation.h"
#include "Hole.h"

#ifndef UTIL_H
#define UTIL_H

/**************************************************************************
 * Helper function that gets the memory requests from the file 
 * and stores them in a vector.
 * 
 * @param filename is the filename of the file that will be opened
 * @return a vector containing a list of pointers to each memory
 *         operation.
 ***************************************************************************/ 
std::vector<MemoryOperation*>* getMemoryOperationsFromFile(const char* filename);

/****************************************************************************
 * Helper function that copies an existing vector into a another heap 
 * allocated vector with each of of its contents also copied over.
 * 
 * @param filename vector that will be copied
 * @return a copy of the other vector
 *****************************************************************************/ 
std::vector<MemoryOperation*>* copyVector(std::vector<MemoryOperation*>* vector);

/******************************************************************************
 * Helper templated function that clears and frees the memory of a
 * given vector.
 * 
 * @param vector is a Type T vector that will be clear and freed
 ******************************************************************************/ 
template<typename T>
void clearAndFreeVector(T vector)
{
    for (unsigned int i = 0; i < vector->size(); i++) {
        delete vector->at(i);;
    }

    vector->clear();
    vector->resize(0);
    vector->shrink_to_fit();
    delete vector;
}

/********************************************************************************
 * Helper templated function prints the contents that are currently
 * in memory. Vector's type must have a toString function.
 * 
 * @param vector is a Type T vector that will be printed to the console
 *********************************************************************************/ 
template<typename T>
void printMemory(T vector)
{
    using namespace std;

    cout << "Here is what memory looks like:" << endl;
    for (unsigned int i = 0; i < vector->size(); i++)
    {
        vector->at(i)->toString();
    }
}

#endif