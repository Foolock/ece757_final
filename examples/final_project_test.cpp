#include "itap.hpp"

int main(int argc, char *argv[]) {

  if(argc != 2) {
    std::cerr << "usage: ./example/final_project_test circuit_file\n";
    std::exit(EXIT_FAILURE);
  }

  std::string filename = argv[1]; 

  itap::iTAP partitioner(filename);

  partitioner.set_partition_size(partitioner.num_nodes());

  std::cout << "runnning gpu partitioning...\n";
  partitioner.partition();

  if(partitioner.is_partition_valid() == false) {
    std::cerr << "cycle introduced...\n";
    std::exit(EXIT_FAILURE);
  }

  // dump the partitioned graph
  // std::cout << "dumped graph, node_name[partition], check it on GraphvizOnline.\n";
  // partitioner.dump_graph();
}
