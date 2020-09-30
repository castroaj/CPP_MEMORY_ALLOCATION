#include "../hdr/MemoryOperation.h"

// Constructor
MemoryOperation::MemoryOperation(unsigned int referenceNumber, unsigned int operation, unsigned int arguement)
    : m_referenceNumber(referenceNumber), m_operation(operation), m_arguement(arguement)
{
}

// Destructor
MemoryOperation::~MemoryOperation()
{}