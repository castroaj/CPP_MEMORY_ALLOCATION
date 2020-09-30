#include "../hdr/Hole.h"

Hole::Hole(unsigned int start, unsigned int end, bool allocated, int refId)
    : m_start(start), m_end(end), m_isAllocated(allocated), m_refId(refId)
{}

Hole::~Hole()
{
}

void Hole::toString()
{
    using namespace std;

    cout << "Start: " << m_start << "  End: " << m_end << " Is Allocated: " << m_isAllocated << " Process: " << m_refId << endl;
}


