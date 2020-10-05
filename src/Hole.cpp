/***********************************************************************
 * CS-450-PA2: Implementation file of the Hole object
 * @file Hole.cpp
 * @author Alexander Castro
 * @version 1.0 10/4/20
 ***********************************************************************/
#include "../hdr/Hole.h"

/***********************************************************************
 * Constructor
 * See header file for details
 **********************************************************************/  
Hole::Hole(unsigned int start, unsigned int end, bool allocated, int refId) 
    : m_start(start), m_end(end), m_isAllocated(allocated), m_refId(refId)
{}

/***********************************************************************
 * Destructor
 * See header file for details
 ***********************************************************************/ 
Hole::~Hole()
{}

/************************************************************************
 * Prints the contents of this object
 * See header file for details
 ************************************************************************/ 
void Hole::toString()
{
    using namespace std;

    cout << m_start << "-" << m_end << ": ";

    if (m_isAllocated)
        cout << "Allocated to " << m_refId << endl;
    else
        cout << "free" << endl;
}


