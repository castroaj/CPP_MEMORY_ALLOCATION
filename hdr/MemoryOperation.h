#include "Driver.h"

#ifndef MEMOP_H
#define MEMOP_H

class MemoryOperation 
{
    private:
        unsigned int m_referenceNumber;
        unsigned int m_operation;
        unsigned int m_arguement;

    public:
        MemoryOperation(unsigned int, unsigned int, unsigned int);
        ~MemoryOperation();

        unsigned int getRefNum() { return m_referenceNumber; }
        unsigned int getOperation() { return m_operation; }
        unsigned int getArguement() { return m_arguement; }
};

#endif