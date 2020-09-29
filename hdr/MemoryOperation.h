#ifndef MEMOP_H
#define MEMOP_H

class MemoryOperation 
{
    private:
        int m_referenceNumber;
        int m_operation;
        int m_arguement;

    public:
        MemoryOperation(int, int, int);

        int getRefNum() {return m_referenceNumber; }
        int getOperation() {return m_operation; }
        int getArguement() {return m_arguement; }
};

#endif