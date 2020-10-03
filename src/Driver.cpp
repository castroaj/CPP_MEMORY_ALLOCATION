#include "../hdr/Driver.h"
#include "../hdr/UtilityFunctions.h"
#include "../hdr/FirstFit.h"
#include "../hdr/BestFit.h"


void printUsage()
{
    using namespace std;

    cout << "Usage" << endl;
}


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

    clearAndFreeVectorMO(memOps1);
    clearAndFreeVectorMO(memOps2);
    clearAndFreeVectorMO(memOps3);
}

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        startProgram(argv[1], false);
    }
    else if (argc == 3 && strcmp("-d", argv[1]) == 0)
    {
        startProgram(argv[2], true);
    }
    else
    {
        printUsage();
    }
    return 0;
}