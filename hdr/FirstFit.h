/***********************************************************************
 * CS-450-PA2: Header file for First Fit Memory allocation algorithm
 * @file FirstFit.h
 * @author Alexander Castro
 * @version 1.0 10/4/20
 ***********************************************************************/
#include "Driver.h"
#include "MemoryOperation.h"
#include "Hole.h"
#include "UtilityFunctions.h"

#ifndef FIRSTFIT_H
#define FIRSTFIT_H

/***********************************************************************
 * Storage for data asscocitated with the First Fit memory
 * allocation simulation. 
 ***********************************************************************/
class FirstFit 
{
    private:
        const unsigned int m_totalMemory = 1024;       /** Memory available in the simulation     */
        std::vector<MemoryOperation*>* m_memOpsVector; /** Vector to hold inputed memory requests */
        std::vector<Hole*>* m_holeVector;              /** Vector to hold the holes in memory     */

    public:
        /**********************************************************************
         * A constructor.
         * Constructs a FirstFit object with the given memory operations.
         * Will instantiate the m_holeVector on the heap and then add the
         * first hole containing all of the free memory.
         * 
         * @param memOpsVector is the vector of memoryOperations that is 
         *                     used control the simulation
         **********************************************************************/
        FirstFit(std::vector<MemoryOperation*>*);

        /*****************************************************************
         * A destructor.
         * Destructs a FirstFit object when the delete keyword is called
         * on an instance. This function will also clear and free the 
         * hole vector 
         *****************************************************************/ 
        ~FirstFit();

        /*****************************************************************
         * Allocation function that is called when a memory operation
         * requests to allocate memory. This function will seek through 
         * the existing hole vector to find the first hole that satisfies
         * the memory request. It will then insert a new allocated hole
         * and update other holes if necesary.  
         * 
         * @param memOp current memory operation that will dictate the memory
         *              allocation
         * 
         * @param debug flag that indicates whether or not logging 
         *              should occur
         ******************************************************************/
        bool allocate(MemoryOperation* memOp, bool debug);

        /********************************************************************
         * Deallocation function that is called when a memory operation 
         * requests to deallocate memory. This function will take the given
         * memory operation's arguement and free up the memory at that ref
         * number. It will also merge any two adjacent free memory holes that
         * may be created from the deallocation.
         * 
         * @param memOp current memory operation that will dicate the memory
         *              deallocation
         * 
         * @param debug flag that indicates whether or not logging should occur
         * 
         * @return whether or not allocation was successful
         ********************************************************************/ 
        void deallocate(MemoryOperation* memOp, bool debug);

        /*********************************************************************
         * Driver that will take the given memory operation vector and run the 
         * First Fit memory allocation simulation.
         * 
         * @param debug flag that indicates whether or not logging should occur
         *********************************************************************/ 
        void runFirstFit(bool debug);
};


#endif