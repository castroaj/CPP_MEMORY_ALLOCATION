#include "../hdr/Driver.h"
#include "../hdr/UtilityFunctions.h"


int main()
{
    std::vector<MemoryOperation*>* memOpsVector = getMemoryOperationsFromFile("inputFile.txt");

    for (unsigned int i = 0; i < memOpsVector->size(); i++)
    {
        MemoryOperation* curMemOp = memOpsVector->at(i);

        std::cout << curMemOp->getRefNum() << " " << curMemOp->getOperation() << " " << curMemOp->getArguement() << std::endl;
    }

    // Clear and free items inside memOpsVector
    memOpsVector->clear();
    delete memOpsVector;
}