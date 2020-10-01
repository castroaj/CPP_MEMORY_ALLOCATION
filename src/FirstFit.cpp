#include "../hdr/FirstFit.h"

#define ALLOCATE 1
#define DEALLOCATE 2

FirstFit::FirstFit(std::vector<MemoryOperation*>* memOpsVector)
    : m_memOpsVector(memOpsVector)
{
    m_holeVector = new std::vector<Hole*>();
    m_holeVector->push_back(new Hole(0U, m_totalMemory, false, -1));
}

FirstFit::~FirstFit()
{
    clearAndFreeVectorHole(m_holeVector);
}

void FirstFit::allocate(MemoryOperation* memOp)
{
    using namespace std;

    for (unsigned int i = 0; i < m_holeVector->size(); i++)
    {   
        // Pointer to current hole in loop
        Hole* curHole = m_holeVector->at(i);

        // Calculate hole size to compare to resource request
        unsigned int holeSize = curHole->getEnd() - curHole->getStart();

        if (memOp->getArguement() < holeSize && !curHole->getIsAllocated())
        {
            Hole* newHole = new Hole(curHole->getStart(), curHole->getStart() + memOp->getArguement(), true, memOp->getRefNum());

            // Insert new hole before old hole
            auto itPos = m_holeVector->begin() + i;
            auto newIt = m_holeVector->insert(itPos, newHole);

            curHole->setStart(newHole->getEnd() + 1);

            cout << "Number of bytes to be allocated: " << memOp->getArguement() << endl;

            for (unsigned int j = 0; j < m_holeVector->size(); j++)
            {
                m_holeVector->at(j)->toString();
            }
            
            cout << "\n";
            break;
        }
    }
}

void FirstFit::deallocate(MemoryOperation* memOp)
{
    using namespace std;

    unsigned int refId = memOp->getArguement();

    for (unsigned int i = 0; i < m_holeVector->size(); i++)
    {
        Hole* curHole = m_holeVector->at(i);


        if (curHole->getRefId() == refId)
        {
            cout << "Ref to be Deallocated: " << curHole->getRefId() << endl;
            curHole->setIsAllocated(false);
            curHole->setRefId(-1);
            break;
        }
    }

    cout << "\n";

}


void FirstFit::runFirstFit()
{
    using namespace std;

    for (unsigned int i = 0; i < m_memOpsVector->size(); i++)
    {
        MemoryOperation* curMemOp = m_memOpsVector->at(i);

        switch (curMemOp->getOperation())
        {
            case ALLOCATE:
                allocate(curMemOp);
                break;
            case DEALLOCATE:
                deallocate(curMemOp);
                break;
            default:
                break;
        }
    }
}
