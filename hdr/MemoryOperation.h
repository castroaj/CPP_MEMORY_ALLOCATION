/***********************************************************************
 * CS-450-PA2: Header file for MemoryOperation object
 * @file MemoryOperation.h
 * @author Alexander Castro
 * @version 1.0 10/4/20
 ***********************************************************************/
#include "Driver.h"

#ifndef MEMOP_H
#define MEMOP_H

/***********************************************************************
 * Encapsulation of a Memory Request.
 ***********************************************************************/ 
class MemoryOperation 
{
    private:
        unsigned int m_referenceNumber;  /** Reference number for this
                                             memory request */
        unsigned int m_operation;        /** Binary value indicating 
                                             either a allocation or 
                                             deallocation of memory */
        unsigned int m_arguement;        /** Argurement that is dependent
                                             on the operation. Is the number
                                             of bytes to be allocated for 
                                             allocation, or the ref number for
                                             deallocation */

    public:
        /**********************************************************************
         * An explicit value constructor.
         * Constructs a MemoryOperation object with all of the members explicitly
         * defined.
         * 
         * @param m_referenceNumber is the reference number for the Memory Request
         * @param m_operation       value indicating whether the request is for allocation
         *                          or deallocation
         * @param m_arguement       Arguement that is dependent on the type of operation
         **********************************************************************/
        MemoryOperation(unsigned int, unsigned int, unsigned int);

        /***********************************************************************
         * A destructor.
         * Destructs a MemoryOperation object when the delete keyword is called
         * on an instance. 
         **********************************************************************/
        ~MemoryOperation();

        /**********************************************************************
         * Getter for the m_referenceNumber member of the class
         **********************************************************************/
        unsigned int getRefNum() { return m_referenceNumber; }

        /**********************************************************************
         * Getter for the m_operation member of the class
         **********************************************************************/
        unsigned int getOperation() { return m_operation; }

        /**********************************************************************
         * Getter for the m_arguement member of the class
         **********************************************************************/
        unsigned int getArguement() { return m_arguement; }
};

#endif