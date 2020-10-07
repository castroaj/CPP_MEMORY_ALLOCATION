/***********************************************************************
 * CS-450-PA2: Implementation file of a couple utility functions that are
 *             used throughout the application.
 * @file UtilityFunctions.cpp
 * @author Alexander Castro
 * @version 1.0 10/4/20
 ***********************************************************************/
#include "../hdr/UtilityFunctions.h"

/***********************************************************************
 * Helper function for reading input data
 * See header file for details
 **********************************************************************/ 
std::vector<MemoryOperation*>* getMemoryOperationsFromFile(const char* filename)
{
    using namespace std;

    uint32_t refNum, opNum, arguementNum;
   
    ifstream infile(filename);
    if (infile.is_open())
    {
        vector<MemoryOperation*>* listOfMemOps = new vector<MemoryOperation*>();

        while (infile >> refNum >> opNum >> arguementNum)
        {
            MemoryOperation* curMemOp = new MemoryOperation(refNum, opNum, arguementNum); 
            listOfMemOps->push_back(curMemOp);
        }

        return listOfMemOps;
    }
    else
    {
        return nullptr;
    }
}

/***********************************************************************
 * Helper function used to copyVector into another completely different
 * vector.
 * See header file for details
 **********************************************************************/ 
std::vector<MemoryOperation*>* copyVector(std::vector<MemoryOperation*>* vector)
{
    auto newVector = new std::vector<MemoryOperation*>();

    for (unsigned int i = 0; i < vector->size(); i++)
    {
        auto curMemOp = vector->at(i);
        newVector->push_back(new MemoryOperation(curMemOp->getRefNum(), curMemOp->getOperation(), curMemOp->getArguement()));
    }

    return newVector;
}

int getExternalFragmentation(std::vector<Hole*>* holeVector)
{
    int totalFragmentation = 0;

    for (unsigned int i = 0; i < holeVector->size(); i++)
    {
        Hole* curHole = holeVector->at(i);

        if (!curHole->getIsAllocated())
        { 
            totalFragmentation += curHole->getEnd() - curHole->getStart();
        }
    }

    return totalFragmentation;
}

