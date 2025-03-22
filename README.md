# ECE757 Final

```bash

~$ mkdir build
~$ cd build
~$ cmake ../
~$ make
~$ ./examples/final_project_test ./example/final_project_test circuit_file matrix_size

```

# Note
1. Our partitioner takes 2 inputs, one is a circuit file, one is the matrix_size.
2. Circuit files (describing the structure of a circuit in the form of a dependency acyclic graph) are stored in /benchmark. 
3. matrix_size is used to define how much workload each task in the task graph has. Each task in the graph is doing matrix multiplication with a problemn size of matrix_size^3.
4. For static timing analysis, a typical matrix size is 8. We can use this number for most of our experiments.

# An example run

```bash

~$ # after you make the project and goes into the /build directory
~$ ./examples/final_project_test ../benchmark/des_perf.txt 8

```

# To modify partition size 


