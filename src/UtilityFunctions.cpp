#include "../hdr/UtilityFunctions.h"

std::vector<MemoryOperation*>* getMemoryOperationsFromFile(const char* filename)
{
    int refNum, opNum, arguementNum;
   
    std::ifstream infile(filename);
    std::vector<MemoryOperation*>* listOfMemOps = new std::vector<MemoryOperation*>();

    while (infile >> refNum >> opNum >> arguementNum)
    {
        MemoryOperation* curMemOp = new MemoryOperation(refNum, opNum, arguementNum); 
        listOfMemOps->push_back(curMemOp);
    }

    return listOfMemOps;
}
