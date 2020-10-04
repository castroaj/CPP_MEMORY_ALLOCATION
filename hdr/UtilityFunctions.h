#include "Driver.h"
#include "MemoryOperation.h"
#include "Hole.h"


#ifndef UTIL_H
#define UTIL_H

std::vector<MemoryOperation*>* getMemoryOperationsFromFile(const char*);
std::vector<MemoryOperation*>* copyVector(std::vector<MemoryOperation*>* vector);

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