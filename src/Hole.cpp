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

    cout << m_start << "-" << m_end << ": ";

    if (m_isAllocated)
    {
        cout << "Allocated to " << m_refId << endl;
    }
    else
    {
        cout << "free" << endl;
    }
}


