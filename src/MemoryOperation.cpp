/***********************************************************************
 * CS-450-PA2: Implementation file of the Memory Operation object
 * @file MemoryOperation.cpp
 * @author Alexander Castro
 * @version 1.0 10/4/20
 ***********************************************************************/
#include "../hdr/MemoryOperation.h"

/***********************************************************************
 * Constructor
 * See header file for details
 **********************************************************************/  
MemoryOperation::MemoryOperation(unsigned int referenceNumber, unsigned int operation, unsigned int arguement)
    : m_referenceNumber(referenceNumber), m_operation(operation), m_arguement(arguement)
{}

/***********************************************************************
 * Destructor
 * See header file for details
 ***********************************************************************/ 
MemoryOperation::~MemoryOperation()
{}