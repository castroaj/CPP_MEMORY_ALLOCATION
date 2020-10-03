#include "Driver.h"
#include "MemoryOperation.h"
#include "Hole.h"
#include "UtilityFunctions.h"

#ifndef BESTFIT_H
#define BESTFIT_H

class BestFit
{
private:
    unsigned int m_totalMemory = 1024;
    std::vector<MemoryOperation*>* m_memOpsVector;
    std::vector<Hole*>* m_holeVector;

public:
    BestFit(std::vector<MemoryOperation*>*);
    ~BestFit();
    bool allocate(MemoryOperation* memOp, bool debug);
    void deallocate(MemoryOperation* memOp, bool debug);
    void printMemory();
    void runBestFit(bool debug);
};

#endif