#include "Driver.h"
#include "MemoryOperation.h"
#include "Hole.h"


#ifndef UTIL_H
#define UTIL_H

std::vector<MemoryOperation*>* getMemoryOperationsFromFile(const char*);
std::vector<MemoryOperation*>* copyVector(std::vector<MemoryOperation*>* vector);
void clearAndFreeVectorMO(std::vector<MemoryOperation*>* vector);
void clearAndFreeVectorHole(std::vector<Hole*>* vector);

#endif