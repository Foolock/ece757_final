
#include "itap.hpp"

int main() {

  itap::iTAP partitioner("../benchmark/c17.txt");

  partitioner.set_partition_size(1);

  partitioner.partition();

  if(partitioner.has_cycle_post_partition()) {
    std::cerr << "cycle introduced...\n";
    std::exit(EXIT_FAILURE);
  }

  partitioner.check_cluster();
  partitioner.dump_graph();

  partitioner.random_incre_ops(10);

  partitioner.partition(true);

  if(partitioner.has_cycle_post_partition()) {
    std::cerr << "cycle introduced...\n";
    std::exit(EXIT_FAILURE);
  }
  partitioner.check_cluster();
  partitioner.dump_graph();

}
