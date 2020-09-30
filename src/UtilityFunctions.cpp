#include "../hdr/UtilityFunctions.h"

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


void clearAndFreeVectorMO(std::vector<MemoryOperation*>* vector)
{
    for (unsigned int i = 0; i < vector->size(); i++) {
        delete vector->at(i);;
    }

    vector->clear();
    vector->resize(0);
    vector->shrink_to_fit();
    delete vector;
}

void clearAndFreeVectorHole(std::vector<Hole*>* vector)
{
    for (unsigned int i = 0; i < vector->size(); i++) {
        delete vector->at(i);;
    }

    vector->clear();
    vector->resize(0);
    vector->shrink_to_fit();
    delete vector;
}