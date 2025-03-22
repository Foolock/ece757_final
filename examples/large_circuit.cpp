
#include "itap.hpp"

int main(int argc, char *argv[]) {

  if(argc != 2) {
    std::cerr << "usage: ./example/large_case num_iteration\n";
    std::exit(EXIT_FAILURE);
  }

  int num_itr = std::atoi(argv[1]);

  itap::iTAP partitioner("../benchmark/vga_lcd.txt");

  // baseline
  std::cout << "baseline-----------------------------\n";
  partitioner.set_partition_size(1);
  partitioner.partition();
  if(!partitioner.is_partition_valid()) {
    std::cerr << "partition invalid...\n";
    std::exit(EXIT_FAILURE);
  }
  partitioner.run_graph();

  // reset partition
  std::cout << "reset-----------------------------\n";
  partitioner.reset_partition();

  // 1st iteration: full partition
  std::cout << "1st full partitioning iteration-----------------------------\n";
  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();
  if(!partitioner.is_partition_valid()) {
    std::cerr << "partition invalid...\n";
    std::exit(EXIT_FAILURE);
  }
  partitioner.run_graph();

  
  
  int count = 0;
  size_t random_ops_time = 0;
  size_t incre_partition_time = 0;
  size_t run_graph_time = 0;
  while(count < num_itr) {

    std::cout << "running " << count+1 << " th incremental partitioning iteration...\n";

    // incremental operations
    auto start = std::chrono::steady_clock::now();
    partitioner.random_incre_ops(10);
    auto end = std::chrono::steady_clock::now();
    random_ops_time += std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

    // incremental partition
    start = std::chrono::steady_clock::now();
    partitioner.partition(true);
    end = std::chrono::steady_clock::now();
    incre_partition_time += std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

    start = std::chrono::steady_clock::now();
    partitioner.run_graph();
    end = std::chrono::steady_clock::now();
    run_graph_time += std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
  
    count++;
  }
  std::cout << "random_ops_time: " << random_ops_time << "\n";
  std::cout << "incre_partition_time: " << incre_partition_time << "\n";
  std::cout << "run_graph_time: " << run_graph_time << "\n";
  if(!partitioner.is_partition_valid()) {
    std::cerr << "partition invalid...\n";
    std::exit(EXIT_FAILURE);
  }

}
