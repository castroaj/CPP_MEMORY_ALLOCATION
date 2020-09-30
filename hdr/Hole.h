#include "Driver.h"

#ifndef HOLE_H
#define HOLE_H

class Hole 
{
    private:
        unsigned int m_start;
        unsigned int m_end;
        bool m_isAllocated;
        int m_refId;

    public:
        Hole(unsigned int start, unsigned int end, bool isAllocated, int refId);
        ~Hole();

        void toString();

        unsigned int getStart() { return m_start; }
        void setStart(unsigned int s) { m_start = s; }

        unsigned int getEnd() { return m_end; }
        void setEnd(unsigned int e) { m_end = e; }

        bool getIsAllocated() { return m_isAllocated; }
        void setIsAllocated(bool a) { m_isAllocated = a; }

        int getRefId() { return m_refId; }
        void setRefId(int e) { m_refId = e; }
};
#endif