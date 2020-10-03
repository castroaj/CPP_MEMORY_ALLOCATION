#include "../hdr/BestFit.h"

#define ALLOCATE 1
#define DEALLOCATE 2

BestFit::BestFit(std::vector<MemoryOperation*>* memOpsVector)
    : m_memOpsVector(memOpsVector)
{
    m_holeVector = new std::vector<Hole*>();
    m_holeVector->push_back(new Hole(0U, m_totalMemory, false, -1));
}

BestFit::~BestFit()
{
    clearAndFreeVectorHole(m_holeVector);
}

void BestFit::printMemory()
{
    using namespace std;

    cout << "Here is what memory looks like:" << endl;
    for (unsigned int j = 0; j < m_holeVector->size(); j++)
    {
        m_holeVector->at(j)->toString();
    }
}

bool BestFit::allocate(MemoryOperation* memOp, bool debug)
{
    return true;
}

void BestFit::deallocate(MemoryOperation* memOp, bool debug)
{

}

void BestFit::runBestFit(bool debug)
{
    using namespace std;
    bool isSuccess = true;

    cout << "Best Fit Simulation:" << endl;

    for (unsigned int i = 0; i < m_memOpsVector->size(); i++)
    {
        MemoryOperation* curMemOp = m_memOpsVector->at(i);

        if (debug) printMemory();

        switch (curMemOp->getOperation())
        {
            case ALLOCATE:
                if (debug) cout << "Request " << curMemOp->getRefNum() << " is to allocate " << curMemOp->getArguement() << " bytes." << endl;
                isSuccess = allocate(curMemOp, debug);
                break;
            case DEALLOCATE:
                if (debug) cout << "Request " << curMemOp->getRefNum() << " is to deallocate request " << curMemOp->getArguement() << "." << endl;
                deallocate(curMemOp, debug);
                break;
            default:
                break;
        }
        if (!isSuccess) 
        {
            cout << "Failed at Request " << curMemOp->getRefNum() << " for " << curMemOp->getArguement() << " bytes." << endl;

            break;
        }
    }

    if (isSuccess)
    {
        cout << "Success" << endl;
    }   
}