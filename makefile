INPUT = heap_management.c allocation_deallocation.c my_memory_heap.c
OUTPUT = output_file

all:
	gcc $(INPUT) -o $(OUTPUT) -Wall
	
clean:
	rm $(OUTPUT)
