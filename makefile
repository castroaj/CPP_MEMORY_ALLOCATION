all: Driver

Driver:
	cd src; g++ -g Driver.cpp MemoryOperation.cpp UtilityFunctions.cpp -o pa2; mv pa2 ..

run:
	./pa2;

clean:
	rm pa2;