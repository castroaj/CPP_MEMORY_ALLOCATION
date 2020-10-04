#include "../hdr/WorstFit.h"

#define ALLOCATE 1
#define DEALLOCATE 2

WorstFit::WorstFit(std::vector<MemoryOperation*>* memOpsVector)
    : m_memOpsVector(memOpsVector)
{
    m_holeVector = new std::vector<Hole*>();
    m_holeVector->push_back(new Hole(0U, m_totalMemory - 1, false, -1));
}

WorstFit::~WorstFit()
{
    clearAndFreeVector<std::vector<Hole*>*>(m_holeVector);
}

bool WorstFit::allocate(MemoryOperation* memOp, bool debug)
{
        using namespace std;

    Hole* worstHole = nullptr;
    unsigned int worstHoleSize = 0;
    unsigned int worstHoleIndex;

    for (unsigned int i = 0; i < m_holeVector->size(); i++)
    {
        Hole* curHole = m_holeVector->at(i);
        unsigned int holeSize = (curHole->getEnd() - curHole->getStart()) + 1;

        if (memOp->getArguement() <= holeSize && !curHole->getIsAllocated() && holeSize > worstHoleSize)
        {
            worstHoleSize = holeSize;
            worstHoleIndex = i;
            worstHole = curHole;
        }
    }

    if (worstHole == nullptr)
    {
        return false;
    }

    Hole* newHole = new Hole(worstHole->getStart(), (worstHole->getStart() + memOp->getArguement()) - 1, true, memOp->getRefNum());

     if (debug) 
     {
         cout << "Found hole of size " << worstHoleSize << " at " << worstHole->getStart() << "-" << worstHole->getEnd() << endl;
         cout << "Allocating hole of size " << memOp->getArguement() << " at location " << newHole->getStart() << " for request " << memOp->getRefNum() << endl;
     }
    // Insert new hole before old hole
    auto itPos = m_holeVector->begin() + worstHoleIndex;
    auto newIt = m_holeVector->insert(itPos, newHole);

    if (memOp->getArguement() == worstHoleSize)
    { 
        Hole* emptyHole = m_holeVector->at(worstHoleIndex + 1);
        m_holeVector->erase(m_holeVector->begin() + (worstHoleIndex + 1)); 
        delete emptyHole;
    }
    else
    { 
        worstHole->setStart(newHole->getEnd() + 1); 
    }

    return true;
}

void WorstFit::deallocate(MemoryOperation* memOp, bool debug)
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

void WorstFit::runWorstFit(bool debug)
{
        using namespace std;
    bool isSuccess = true;

    cout << "Worst Fit Simulation:" << endl;

    for (unsigned int i = 0; i < m_memOpsVector->size(); i++)
    {
        MemoryOperation* curMemOp = m_memOpsVector->at(i);

        if (debug) printMemory<vector<Hole*>*>(m_holeVector);

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