/***********************************************************************
 * CS-450-PA2: Driver for the application. Will start up each simulation.
 * @file Driver.cpp
 * @author Alexander Castro
 * @version 1.0 10/4/20
 ***********************************************************************/
#include "../hdr/Driver.h"
#include "../hdr/UtilityFunctions.h"
#include "../hdr/FirstFit.h"
#include "../hdr/BestFit.h"
#include "../hdr/WorstFit.h"

/*************************************************************************
 * Function that prints the usage of the program when the user improperly
 * executes the program.
 *************************************************************************/
void printUsage()
{
    using namespace std;

    cout << "Usage:" << endl;
    cout << "STANDARD MODE: ./pa2 [Request Input File]" << endl;
    cout << "DEBUG MODE: ./pa2 -d [Request Input File]" << endl; 
}

/*************************************************************************
 * Helper to print out all of the memory requests in the input file.
 *************************************************************************/ 
void printInputFile(std::vector<MemoryOperation*>* memOps)
{
    using namespace std;

    cout << "Here is the input I read:" << endl;

    for (unsigned int i = 0; i < memOps->size(); i++)
    {
        MemoryOperation* curMemOp = memOps->at(i);

        cout << curMemOp->getRefNum() << " " << curMemOp->getOperation() << " " << curMemOp->getArguement() << endl;
    }
}

/****************************************************************
 * Driver for the entire application. This will read the data 
 * from the input file and pass a seperate copy to each of the 
 * three memory allocation algorithms.
 ****************************************************************/ 
void startProgram(const char* filename, bool debug)
{
    auto memOps1 = getMemoryOperationsFromFile(filename);

    if (memOps1 == nullptr)
    {
        std::cout << "Invalid Input File" << std::endl;
        return;
    }

    auto memOps2 = copyVector(memOps1);
    auto memOps3 = copyVector(memOps1);

    if (debug) printInputFile(memOps1);

    FirstFit firstFit(memOps1);
    firstFit.runFirstFit(debug);

    BestFit bestFit(memOps2);
    bestFit.runBestFit(debug);

    WorstFit worstFit(memOps3);
    worstFit.runWorstFit(debug);

    clearAndFreeVector<std::vector<MemoryOperation*>*>(memOps1);
    clearAndFreeVector<std::vector<MemoryOperation*>*>(memOps2);
    clearAndFreeVector<std::vector<MemoryOperation*>*>(memOps3);
}

/**********************************************************************
 * Entry point of the application
 **********************************************************************/ 
int main(int argc, char* argv[])
{
    if (argc == 2)
        startProgram(argv[1], false);
    else if (argc == 3 && strcmp("-d", argv[1]) == 0)
        startProgram(argv[2], true);
    else
        printUsage();
    return 0;
}