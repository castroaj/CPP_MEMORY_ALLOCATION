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


void FirstFit::printMemory()
{
    using namespace std;

    cout << "Here is what memory looks like:" << endl;
    for (unsigned int j = 0; j < m_holeVector->size(); j++)
    {
        m_holeVector->at(j)->toString();
    }
}

bool FirstFit::allocate(MemoryOperation* memOp, bool debug)
{
    using namespace std;

    for (unsigned int i = 0; i < m_holeVector->size(); i++)
    {   
        // Pointer to current hole in loop
        Hole* curHole = m_holeVector->at(i);

        // Calculate hole size to compare to resource request
        unsigned int holeSize = (curHole->getEnd() - curHole->getStart()) + 1;

        if (memOp->getArguement() <= holeSize && !curHole->getIsAllocated())
        {
            Hole* newHole = new Hole(curHole->getStart(), (curHole->getStart() + memOp->getArguement()) - 1, true, memOp->getRefNum());

            if (debug) 
            {
                cout << "Found hole of size " << holeSize << " at " << curHole->getStart() << "-" << curHole->getEnd() << endl;
                cout << "Allocating hole of size " << memOp->getArguement() << " at location " << newHole->getStart() << " for request " << memOp->getRefNum() << endl;
            }
            // Insert new hole before old hole
            auto itPos = m_holeVector->begin() + i;
            auto newIt = m_holeVector->insert(itPos, newHole);

            if (memOp->getArguement() == holeSize)
            { m_holeVector->erase(m_holeVector->begin() + (i + 1)); }
            else
            { curHole->setStart(newHole->getEnd() + 1); }

            return true;
        }
    }
    return false;
}


void FirstFit::deallocate(MemoryOperation* memOp, bool debug)
{
    using namespace std;

    unsigned int refId = memOp->getArguement();

    for (unsigned int i = 0; i < m_holeVector->size(); i++)
    {
        Hole* curHole = m_holeVector->at(i);

        if (curHole->getRefId() == refId)
        {
            if (debug) cout << "Deallocated hole for request " << curHole->getRefId() << " (" << (curHole->getEnd() - curHole->getStart()) + 1 << " bytes)." << endl;
            
            curHole->setIsAllocated(false);
            curHole->setRefId(-1);

            if (i != 0)
            {
                Hole* previousHole = m_holeVector->at(i-1);

                if (!previousHole->getIsAllocated())
                {
                    Hole* newHole = new Hole(previousHole->getStart(), curHole->getEnd(), false, -1);

                    // Insert new hole before old hole
                    auto itPos = m_holeVector->begin() + (i -1);
                    auto newIt = m_holeVector->insert(itPos, newHole);

                    m_holeVector->erase(m_holeVector->begin() + i);
                    m_holeVector->erase(m_holeVector->begin() + i);

                    Hole* oldCurHole = curHole;
                    curHole = newHole;

                    i--;

                    delete previousHole;
                    delete oldCurHole;
                }

            }

            if (i != m_holeVector->size() - 1)
            {
                Hole* nextHole = m_holeVector->at(i+1);

                if (!nextHole->getIsAllocated())
                {
                    Hole* newHole = new Hole(curHole->getStart(), nextHole->getEnd(), false, -1);

                    auto itPos = m_holeVector->begin() + i;
                    auto newIt = m_holeVector->insert(itPos, newHole);

                    m_holeVector->erase(m_holeVector->begin() + (i + 1));
                    m_holeVector->erase(m_holeVector->begin() + (i + 1));

                    delete nextHole;
                    delete curHole;
                }
            }

            break;
        }
    }
}


void FirstFit::runFirstFit(bool debug)
{
    using namespace std;

    bool isSuccess = true;

    cout << "First Fit Simulation:" << endl;

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
