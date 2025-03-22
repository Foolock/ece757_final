#include "itap.hpp"

int main() {

  itap::iTAP partitioner;

  itap::Node* A = partitioner.insert_node("A");
  itap::Node* B = partitioner.insert_node("B");
  itap::Node* C = partitioner.insert_node("C");
  itap::Node* D = partitioner.insert_node("D");

  itap::Edge* AC = partitioner.insert_edge(A, C);
  itap::Edge* AD = partitioner.insert_edge(A, D);
  itap::Edge* BD = partitioner.insert_edge(B, D);

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  if(partitioner.has_cycle_post_partition()) {
    std::cerr << "cycle introduced...\n";
    std::exit(EXIT_FAILURE);
  }

  partitioner.dump_graph();

  // apply one incremental operation, this should cause cycle
  partitioner.insert_edge(B, C);
  partitioner.partition(true);
  partitioner.dump_graph();
  if(partitioner.has_cycle_post_partition()) {
    std::cerr << "cycle introduced...\n";
    std::exit(EXIT_FAILURE);
  }

}
