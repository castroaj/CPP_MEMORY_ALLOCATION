# CS-450-PA2

Name: Alexander Castro

Implementaion of three memory allocation algorithms:

Description:

	Reads input from an input file that lists all of the memory requests.
	The input file should be formated with each request being on its
	own individual line. For each request, there are 3 fields:
		- Reference Number
		- An Operation (either 1 for allocate or 2 for deallocate)
		- An Arguement (size in bytes for allocation; a reference number for a deallocation)

	The program will run a memory allocation simulation using the following algorithms:
		- First-fit
		- Best-fit
		- Worst-fit

Compiling:

	The provided makefile should build the project for you. Run the following 
	command to use the makefile (You will need the g++ compiler for this step):

		make
	
	After you build the project, an executable named pa2 should be placed in the directory.

Cleaning:

	If you wish to clean the project, then 
	you can run the following command to do so:
		
		make clean

Running:

	The application has two modes:
		- Standard Mode
		- Debug Mode
	
	Standard Mode:
		This mode will run the simulation using the given input file and the 
		output the final statistics of the simulation.
	
		HOW TO RUN:
			Make sure the pa2 executable file is in your current directory and then
			run the following command.

			./pa2 [Processes Input File]

	Debug Mode:
		This mode will run the simulation using the given input file and also
		log all steps made by the simulation.
	
		HOW TO RUN:
			Make sure the pa2 executable file is in your current directory and then 
			run the following command.

			./pa2 -d [Processes Input File]

Known Bugs:

	The are no known bugs for any of the scheduling algorithms
