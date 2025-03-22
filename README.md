# How to compile?

```bash

~$ mkdir build
~$ cd build
~$ make
~$ ./examples/simple

```


1/18

1. Bugs in void iTAP::partition();
2. How to better design remove functions; 

1/28

1. Bugs removed in iTAP::partition()
2. Duplicate edges(cedges) appear in rebuilt graph 
3. Add remove\_node() and remove\_edge(). (needs to rebuild cnode and cedge)

1/29

1. Add unittests for remove\_node() and remove\_edge()

2/1

1. Add circuits testcases from OpenTimer
2. Design an incremental partitioning method so that the partitioning results should be exactly the same with full partitioning method.
3. Assume 12 operations each time (with 4 of each basic operations).

2/6

1. Fix BUGs in remove\_node
2. Implemented random incremental test

2/9

1. Adding frontiers nodes for incremental update.
   First assume insert\_edge and remove\_edge does not produce any frontiers
   i.e., won't have an impact on partitioning results.

2/19

1. The concept of propogating partition IDs from frontiers does not seem to make sense. 
   Imaging for each partitioning iteration, we are inserting a new node as the fanin of the inserted node from the last iteration, i.e., inserting a linear chain of nodes through multiple iterations, propagating partition IDs in this case will cause multiple meaningless update on partition IDs for the nodes in the linear chains.
2. Instead, can we consider just to merge the frontiers node into the current partitions (or start a new one)?
3. In the current stages, let's just consider the newly inserted nodes as frontiers, leaving the nodes whose fanins/fanouts are changed during remove\_node, insert\_edge/remove\_edge.
4. For random\_incre\_test, for remove\_node we only remove the nodes that are in the graph already instead of the newly inserted nodes (since if we would need to remove it why inserting it at the first place).
5. Updated ctest, add random\_incre\_ops. But it takes O(n^2) time to n random ops. In larger designs (e.g., des\_perf or vga\_lcd), ctest could take ~30s. This needs to be improved.
6. Start to implement the idea of just merge the frontiers node into the current partitions. 
7. Fixed random\_incre\_ops takes too long bug, now the complexity is O(NlogN). Now all ctest cases takes num\_nodes/3 random ops

2/20

1. Updated random\_incre\_ops such that new nodes can connect to each other and there may be new nodes that connect to no one. 
2. Add vga\_lcd example for testing.
3. Implemeting the idea of starting partitioning from \_frontiers. And only partition the nodes in \_candidates
4. But there is an issue for this idea, the largest partition ID order is not guaranteed. Will there be a problem?

2/21

1. Finished implementing a naive version of incremental partitioning.

2/23

1. Need to insert\_edge between existing nodes. To avoid cycles, I need to make sure from node and to node in insert\_edge follow topological order.

2/26

1. Fixed BUGs in ctest
2. Add run\_graph for experiments.

2/27

1. Added netcard\_iccad testcase.
2. Propose a naive solution for insert\_edge between existing nodes.
3. Need to measure partitioning runtime for both incremental partition and full partition 

2/29

1. Removed a hell lot of BUGs.
2. The naive solution for insert\_edge bewteen existing nodes won't work.
   My guess is that here we assign ++max\_partition\_ID for type3 frontiers.   Which break the loop invarient internally.

3/4

1. Finished implementation of my new ideas. This includes breaking down the types of situations and solve it accordingly.
2. Need to add ctest cases to verify it.
3. No, the current idea cannot maintain the loop invarient.
4. There is BUG in dep\_cnt, I tried remove dep\_cnt in remove\_edge. And add a global flag to say I finished the partition. Still not work
   Guess I need to solve this one first.

3/7

1. Solved a BUG in \_dep\_cnt by handling it in insert\_edge and remove\_edge
2. Need to increase the iteration of incremental partitioning in ctest to verify. (currently only one iteration)

3/11

1. Modified ctest

3/13

1. Solved a BUG in cluster\_cnt. (Still need to be verified) 
2. Added partition valid check function and replaced it in ctest. 
3. Tested why ctest take so long, random\_ops takes up a lot of time.
4. Create exp.cpp so we can test runtime for incremental partition and full partition

3/28

1. Added all heuristics
2. Modified ctest test\_cycle.cpp, set partition\_size to 10 for most test cases.
2. Need to add unbalanced\_rate = largest\_partition\_size / average\_partition\_size  

3/30

1. Solved BUGs in \_cluster\_cnt.
2. Added \_cluster\_cnt checker. Need to use after run\_graph
3. In exp, partition\_size = 10 usually give a very good results.
4. In exp, imbalance\_factor of incremental partitioning will blow up sometimes.
5. Need to add G-PASTA.

4/1

1. Adding G-PASTA.
2. Added CUDA compile CMakeLists.txt.
3. Added \_cluster\_cnt check in ctest.
4. Modified CMakeLists.txt.
5. Added export\_csr().

4/2

1. Implemented G-PASTA.

















# ece757_final
