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
2. `circuit_file` (describing the structure of a circuit in the form of a dependency acyclic graph) are stored in /benchmark. 
3. `matrix_size` is used to define how much workload each task in the task graph has. Each task in the graph is doing matrix multiplication with a problemn size of matrix_size^3.
4. For static timing analysis, a typical matrix size is 8. We can use this number for most of our experiments.
5. To run the partitioned graph, use `run_graph()` function (make sure the graph is partitioned **before** we run `run_graph()`).

# An example run

```bash

~$ # after you make the project and goes into the /build directory
~$ ./examples/final_project_test ../benchmark/des_perf.txt 8

```

# To modify partition size 

```bash

~$ # line 16 of /examples/final_project_test.cpp
~$ partitioner.set_partition_size(partition_size);
~$ # partition_size is set as the total number of tasks in the graph by default (partitioner.num_nodes()). 

```

`partition_size` refers to the upper limit of number of tasks within one partition. E.g., if we have a partition size of 100, that means each partition will have **at most** 100 tasks.

# To visual the task graph

```bash

~$ # simply use dump_graph() (line 29 of /examples/final_project_test.cpp)
~$ partitioner.dump_graph();

```

The graph structure information will look something like this:
```bash

digraph Taskflow {
subgraph cluster_p0x7ffc19682ba0 {
label="Taskflow: p0x7ffc19682b50";
p0x556d7b241bc0[label="0[0]" ];
p0x556d7b241bc0 -> p0x556d7b241cb0;
p0x556d7b241bc0 -> p0x556d7b2429d0;
p0x556d7b241cb0[label="1[0]" ];
p0x556d7b241cb0 -> p0x556d7b241da0;
p0x556d7b241cb0 -> p0x556d7b2427f0;
p0x556d7b241da0[label="2[0]" ];
p0x556d7b241da0 -> p0x556d7b241e90;
p0x556d7b241e90[label="3[0]" ];
p0x556d7b241e90 -> p0x556d7b241f80;
p0x556d7b241e90 -> p0x556d7b242160;
p0x556d7b241f80[label="4[0]" ];
p0x556d7b241f80 -> p0x556d7b242070;
p0x556d7b242070[label="5[0]" ];
p0x556d7b242160[label="6[0]" ];
p0x556d7b242160 -> p0x556d7b242250;
p0x556d7b242250[label="7[0]" ];
p0x556d7b242340[label="8[1]" ];
p0x556d7b242340 -> p0x556d7b242430;
p0x556d7b242430[label="9[1]" ];
p0x556d7b242430 -> p0x556d7b242520;
p0x556d7b242520[label="10[1]" ];
p0x556d7b242520 -> p0x556d7b242610;
p0x556d7b242610[label="11[1]" ];
p0x556d7b242610 -> p0x556d7b242700;
p0x556d7b242700[label="12[1]" ];
p0x556d7b242700 -> p0x556d7b2428e0;
p0x556d7b2427f0[label="13[0]" ];
p0x556d7b2427f0 -> p0x556d7b2428e0;
p0x556d7b2428e0[label="14[1]" ];
p0x556d7b2428e0 -> p0x556d7b2429d0;
p0x556d7b2429d0[label="15[1]" ];
p0x556d7b2429d0 -> p0x556d7b242ac0;
p0x556d7b242ac0[label="16[1]" ];
}
}

```

Copy and paste it to [graphviz online](https://dreampuf.github.io/GraphvizOnline/) for visualization.









