#include "Driver.h"
#include "MemoryOperation.h"
#include "Hole.h"
#include "UtilityFunctions.h"

#ifndef WORSTFIT_H
#define WORSTFIT_H

class WorstFit 
{
    private:
        unsigned int m_totalMemory = 1024;
        std::vector<MemoryOperation*>* m_memOpsVector;
        std::vector<Hole*>* m_holeVector;

    public:
        WorstFit(std::vector<MemoryOperation*>*);
        ~WorstFit();
        bool allocate(MemoryOperation* memOp, bool debug);
        void deallocate(MemoryOperation* memOp, bool debug);
        void printMemory();
        void runWorstFit(bool debug);
};
#endif