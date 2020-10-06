#include "../hdr/WorstFit.h"

#define ALLOCATE 1
#define DEALLOCATE 2

/***********************************************************************
 * Constructor
 * See header file for details
 **********************************************************************/ 
WorstFit::WorstFit(std::vector<MemoryOperation*>* memOpsVector) : m_memOpsVector(memOpsVector)
{
    m_holeVector = new std::vector<Hole*>();
    m_holeVector->push_back(new Hole(0U, m_totalMemory - 1, false, -1));
}

/***********************************************************************
 * Destructor
 * See header file for details
 ***********************************************************************/ 
WorstFit::~WorstFit()
{
    clearAndFreeVector<std::vector<Hole*>*>(m_holeVector);
}

/***********************************************************************
 * Function that allocates memory for a given memory request
 * See header file for details
 ***********************************************************************/ 
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

/***********************************************************************
 * Function that deallocates memory for a previous memory request
 * See header file for details
 ***********************************************************************/ 
void WorstFit::deallocate(MemoryOperation* memOp, bool debug)
{
    using namespace std;
    unsigned int refId = memOp->getArguement();

    // Loop to find the hole with the ref id that needs to be deallocated
    for (unsigned int i = 0; i < m_holeVector->size(); i++)
    {
        // Pointer to current hole 
        Hole* curHole = m_holeVector->at(i);

        if (curHole->getRefId() == refId)
        {
            if (debug) cout << "Deallocated hole for request " << curHole->getRefId() << " (" << (curHole->getEnd() - curHole->getStart()) + 1 << " bytes)." << endl;
            
            // Deallocate the current hole of memory
            curHole->setIsAllocated(false);
            curHole->setRefId(-1);

            /**
             * The following code will check for adjacent free memory before the 
             * newly deallocated memory. If the memory is free, it will merge the 
             * two holes.
             */ 
            if (i != 0)
            {
                Hole* previousHole = m_holeVector->at(i-1);

                if (!previousHole->getIsAllocated())
                {
                    Hole* newHole = new Hole(previousHole->getStart(), curHole->getEnd(), false, -1);

                    // Insert newHole before the previous hole
                    auto itPos = m_holeVector->begin() + (i -1);
                    auto newIt = m_holeVector->insert(itPos, newHole);

                    // Erase the two old free memory holes
                    m_holeVector->erase(m_holeVector->begin() + i);
                    m_holeVector->erase(m_holeVector->begin() + i);

                    // Get a pointer to the old hole for freeing
                    Hole* oldCurHole = curHole;
                    
                    // Update the curHole pointer in order to continue
                    // using it within the function
                    curHole = newHole;

                    // Decrement looping variable in order to account for
                    // removed element
                    i--;

                    // Free up unused memory
                    delete previousHole;
                    delete oldCurHole;
                }
            }

            /**
             * The following code will check for adjacent free memory after the 
             * newly deallocated memory. If the memory is free, it will merge the 
             * two holes.
             */ 
            if (i != m_holeVector->size() - 1)
            {
                Hole* nextHole = m_holeVector->at(i+1);

                if (!nextHole->getIsAllocated())
                {
                    Hole* newHole = new Hole(curHole->getStart(), nextHole->getEnd(), false, -1);

                    // Insert newHole before the current hole
                    auto itPos = m_holeVector->begin() + i;
                    auto newIt = m_holeVector->insert(itPos, newHole);

                    // Erase the two old free memory holes
                    m_holeVector->erase(m_holeVector->begin() + (i + 1));
                    m_holeVector->erase(m_holeVector->begin() + (i + 1));

                    // Free up unused memory
                    delete nextHole;
                    delete curHole;
                }
            }
            // Exit the loop once the deallocation is finished
            break;
        }
    }
}

/************************************************************************
 * Driver for the Worst Fit Memory Allocation simulation
 * See header file for details
 ************************************************************************/ 
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