
#include "itap.hpp"

int main(int argc, char *argv[]) {

  if(argc != 2) {
    std::cerr << "usage: ./example/simple num_iteration\n";
    std::exit(EXIT_FAILURE);
  }

  int num_itr = std::atoi(argv[1]);

  itap::iTAP partitioner("../benchmark/simple.txt");

  partitioner.set_partition_size(partitioner.num_nodes());

  std::cout << "runnning full partitioning...\n";
  partitioner.partition();

  if(partitioner.is_partition_valid() == false) {
    std::cerr << "cycle introduced...\n";
    std::exit(EXIT_FAILURE);
  }

  int count = 0;
  while(count < num_itr) {
    std::cout << "running " << count+1 << " th incremental partitioning iteration...\n";
    // test incremental ops
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    if(partitioner.has_cycle_pre_partition() == true) {
      std::cerr << "cycle introduced by incremental operations...\n";
      std::exit(EXIT_FAILURE);
    }
    partitioner.partition();
    if(partitioner.is_partition_valid() == false) {
      std::cerr << "cycle introduced by incremental partition...\n";
      std::exit(EXIT_FAILURE);
    }
    partitioner.dump_graph();
    count++;
  }

  // partitioner._partition_cuda();

}

