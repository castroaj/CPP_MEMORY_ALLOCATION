/***********************************************************************
 * CS-450-PA2: Implementation file of the BestFit memory allocation 
 *             simulation.
 * @file BestFit.cpp
 * @author Alexander Castro
 * @version 1.0 10/4/20
 ***********************************************************************/
#include "../hdr/BestFit.h"

#define ALLOCATE 1
#define DEALLOCATE 2

/***********************************************************************
 * Constructor
 * See header file for details
 **********************************************************************/ 
BestFit::BestFit(std::vector<MemoryOperation*>* memOpsVector) : m_memOpsVector(memOpsVector)
{
    // Instantiate the hole vector member
    m_holeVector = new std::vector<Hole*>();

    // Add the first hole of unalloacted memory from 0 to m_totalMemory
    m_holeVector->push_back(new Hole(0U, m_totalMemory - 1, false, -1));
}

/***********************************************************************
 * Destructor
 * See header file for details
 ***********************************************************************/ 
BestFit::~BestFit()
{
    clearAndFreeVector<std::vector<Hole*>*>(m_holeVector);
}

bool BestFit::allocate(MemoryOperation* memOp, bool debug)
{
    using namespace std;

    Hole* bestHole = nullptr;
    unsigned int bestHoleSize = INT_MAX;
    unsigned int bestHoleIndex;

    for (unsigned int i = 0; i < m_holeVector->size(); i++)
    {
        Hole* curHole = m_holeVector->at(i);
        unsigned int holeSize = (curHole->getEnd() - curHole->getStart()) + 1;

        if (memOp->getArguement() <= holeSize && !curHole->getIsAllocated() && holeSize < bestHoleSize)
        {
            bestHoleSize = holeSize;
            bestHoleIndex = i;
            bestHole = curHole;
        }
    }

    if (bestHole == nullptr)
    {
        return false;
    }

    Hole* newHole = new Hole(bestHole->getStart(), (bestHole->getStart() + memOp->getArguement()) - 1, true, memOp->getRefNum());

     if (debug) 
     {
         cout << "Found hole of size " << bestHoleSize << " at " << bestHole->getStart() << "-" << bestHole->getEnd() << endl;
         cout << "Allocating hole of size " << memOp->getArguement() << " at location " << newHole->getStart() << " for request " << memOp->getRefNum() << endl;
     }
    // Insert new hole before old hole
    auto itPos = m_holeVector->begin() + bestHoleIndex;
    auto newIt = m_holeVector->insert(itPos, newHole);

    if (memOp->getArguement() == bestHoleSize)
    { 
        Hole* emptyHole = m_holeVector->at(bestHoleIndex + 1);
        m_holeVector->erase(m_holeVector->begin() + (bestHoleIndex + 1)); 
        delete emptyHole;
    }
    else
    { 
        bestHole->setStart(newHole->getEnd() + 1); 
    }

    return true;
}

void BestFit::deallocate(MemoryOperation* memOp, bool debug)
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

void BestFit::runBestFit(bool debug)
{
    using namespace std;
    bool isSuccess = true;

    cout << "Best Fit Simulation:" << endl;

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