#include "Driver.h"
#include "MemoryOperation.h"
#include "Hole.h"
#include "UtilityFunctions.h"

#ifndef FIRSTFIT_H
#define FIRSTFIT_H

class FirstFit 
{
    private:
        unsigned int m_totalMemory = 1024;
        std::vector<MemoryOperation*>* m_memOpsVector;
        std::vector<Hole*>* m_holeVector;

    public:
        FirstFit(std::vector<MemoryOperation*>*);
        ~FirstFit();
        bool allocate(MemoryOperation* memOp, bool debug);
        void deallocate(MemoryOperation* memOp, bool debug);
        void printMemory();
        void runFirstFit(bool debug);
};


#endif