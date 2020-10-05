/***********************************************************************
 * CS-450-PA2: Header file for the Hole Object
 * @file Hole.h
 * @author Alexander Castro
 * @version 1.0 10/4/20
 ***********************************************************************/
#include "Driver.h"

#ifndef HOLE_H
#define HOLE_H

/***********************************************************************
 * Encapsulation of a Hole in memory.
 ***********************************************************************/
class Hole 
{
    private:
        unsigned int m_start;  /** Starting index of the byte range for
                                   this memory hole */
        unsigned int m_end;    /** Ending index of the byte range for 
                                   this memory hole */
        bool m_isAllocated;    /** Flag on whether or not this hole is 
                                   allocated to a request or not */
        int m_refId;           /** Ref Number for the memory request 
                                   that currently occupies this hole */

    public:
        /**********************************************************************
         * An explicit value constructor.
         * Constructs a Hole object with all of the members explicitly defined.
         * 
         * @param start is the starting index of this new hole
         * @param end is the ending index of this new hole
         * @param isAllocated is whether or not this new hole is allocated
         * @param refId is the ref number of the memory request that allocated
         *              this hole. Will be -1 if the hole is not allocated.
         **********************************************************************/
        Hole(unsigned int start, unsigned int end, bool isAllocated, int refId);

        /**********************************************************************
         * A destructor.
         * Destructs a Hole object when the delete keyword is called
         * on an instance. 
         **********************************************************************/
        ~Hole();

        /**********************************************************************
         * Function that prints the contents of the hole to the console.
         **********************************************************************/
        void toString();

        /**********************************************************************
         * Getter and setter for the m_start member of the class
         **********************************************************************/
        unsigned int getStart() { return m_start; }
        void setStart(unsigned int s) { m_start = s; }

        /**********************************************************************
         * Getter and setter for the m_end member of the class
         **********************************************************************/
        unsigned int getEnd() { return m_end; }
        void setEnd(unsigned int e) { m_end = e; }

        /**********************************************************************
         * Getter and setter for the m_isAllocated member of the class
         **********************************************************************/
        bool getIsAllocated() { return m_isAllocated; }
        void setIsAllocated(bool a) { m_isAllocated = a; }

        /**********************************************************************
         * Getter and setter for the m_refId member of the class
         **********************************************************************/
        int getRefId() { return m_refId; }
        void setRefId(int e) { m_refId = e; }
};

#endif