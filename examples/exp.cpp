
#include "itap.hpp"


std::vector<int> generate_random_nums(int N, int count) {

    if(N <= count) {
      std::cerr << "too many random incremental ops...\n";
      std::exit(EXIT_FAILURE);
    }

    std::vector<int> numbers(N);
    std::iota(numbers.begin(), numbers.end(), 0); // Fill with 0, 1, ..., N-1

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(numbers.begin(), numbers.end(), gen);

    numbers.resize(count); // Keep only the first 'count' numbers
    return numbers;
}

const void check_identical(const itap::iTAP& partitioner_incre, const itap::iTAP& partitioner_full) {

  auto itr1 = partitioner_incre._nodes.begin();
  auto itr2 = partitioner_full._nodes.begin();
  for(size_t i=0; i<partitioner_incre._nodes.size(); i++) {
    if((*itr1)._name != (*itr2)._name) {
      std::cerr << "name: graph not the same...\n";
      std::exit(EXIT_FAILURE);
    }
    if((*itr1)._fanins.size() != (*itr2)._fanins.size()) {
      std::cerr << "fanins.size(): graph not the same...\n";
      std::exit(EXIT_FAILURE);
    }
    if((*itr1)._fanouts.size() != (*itr2)._fanouts.size()) {
      std::cerr << "fanouts.size(): graph not the same...\n";
      std::exit(EXIT_FAILURE);
    }
    ++itr1;
    ++itr2;
  }

}

int main(int argc, char *argv[]) {

  if(argc != 4) {
    std::cerr << "usage: ./example/exp num_iteration num_incre_ops circuit.txt\n";
    std::exit(EXIT_FAILURE);
  }

  size_t num_itr = std::atoi(argv[1]);
  size_t num_incre_ops = std::atoi(argv[2]);
  std::string circuit_file = argv[3];

  itap::iTAP partitioner_incre(circuit_file);
  // itap::iTAP partitioner_incre_only_handle_edge(circuit_file);
  itap::iTAP partitioner_full(circuit_file);

  // ------------------------------------------------------------------------------

  // baseline
  std::cout << "---------------------------------------------------------------------\n";
  std::cout << "*baseline(incre)*\n";
  partitioner_incre.set_partition_size(1);
  partitioner_incre.partition();
  if(!partitioner_incre.is_partition_valid()) {
    std::cerr << "partition invalid...\n";
    std::exit(EXIT_FAILURE);
  }
  partitioner_incre.run_graph();
 
  // reset partition
  std::cout << "---------------------------------------------------------------------\n";
  std::cout << "*reset(incre)*\n";
  partitioner_incre.reset_partition();

  // // baseline
  // std::cout << "---------------------------------------------------------------------\n";
  // std::cout << "*baseline(incre_only_handle_edge)*\n";
  // partitioner_incre_only_handle_edge.set_partition_size(1);
  // partitioner_incre_only_handle_edge.partition();
  // if(!partitioner_incre_only_handle_edge.is_partition_valid()) {
  //   std::cerr << "partition invalid...\n";
  //   std::exit(EXIT_FAILURE);
  // }
  // partitioner_incre_only_handle_edge.run_graph();
 
  // // reset partition
  // std::cout << "---------------------------------------------------------------------\n";
  // std::cout << "*reset(incre)*\n";
  // partitioner_incre_only_handle_edge.reset_partition();

  // baseline
  std::cout << "---------------------------------------------------------------------\n";
  std::cout << "*baseline(full)*\n";
  partitioner_full.set_partition_size(1);
  partitioner_full.partition();
  if(!partitioner_full.is_partition_valid()) {
    std::cerr << "partition invalid...\n";
    std::exit(EXIT_FAILURE);
  }
  partitioner_full.run_graph();

  // reset partition
  std::cout << "---------------------------------------------------------------------\n";
  std::cout << "*reset(full)*\n";
  partitioner_full.reset_partition();

  // ------------------------------------------------------------------------------

  // 1st iteration: full partition
  std::cout << "---------------------------------------------------------------------\n";
  std::cout << "*1st full partitioning iteration(incre)*\n";
  // partitioner_incre.set_partition_size(partitioner_incre.num_nodes());
  partitioner_incre.set_partition_size(10);
  partitioner_incre.partition();
  if(!partitioner_incre.is_partition_valid()) {
    std::cerr << "partition invalid...\n";
    std::exit(EXIT_FAILURE);
  }
  partitioner_incre.run_graph();

  // // 1st iteration: full partition
  // std::cout << "---------------------------------------------------------------------\n";
  // std::cout << "*1st full partitioning iteration(incre_only_handle_edge)*\n";
  // // partitioner_incre_only_handle_edge.set_partition_size(partitioner_incre_only_handle_edge.num_nodes());
  // partitioner_incre_only_handle_edge.set_partition_size(10);
  // partitioner_incre_only_handle_edge.partition();
  // if(!partitioner_incre_only_handle_edge.is_partition_valid()) {
  //   std::cerr << "partition invalid...\n";
  //   std::exit(EXIT_FAILURE);
  // }
  // partitioner_incre_only_handle_edge.run_graph();

  // 1st iteration: full partition
  std::cout << "---------------------------------------------------------------------\n";
  std::cout << "*1st full partitioning iteration(full)*\n";
  // partitioner_full.set_partition_size(partitioner_full.num_nodes());
  partitioner_full.set_partition_size(10);
  partitioner_full.partition();
  if(!partitioner_full.is_partition_valid()) {
    std::cerr << "partition invalid...\n";
    std::exit(EXIT_FAILURE);
  }
  partitioner_full.run_graph();

  // ------------------------------------------------------------------------------

  // set the partition_size of incre partitioner as the partition_size of full partitioner
  // partitioner_incre.set_partition_size(partitioner_full.get_max_cluster_size());
  int count = 0;
  size_t random_ops_time = 0;
  size_t incre_partition_time = 0;
  size_t run_graph_time = 0;
  while(count < num_itr) {

    std::cout << "---------------------------------------------------------------------\n";

    std::cout << "running " << count+1 << " th incremental partitioning iteration...\n";

    size_t N = num_incre_ops;

    if(2*N >= partitioner_incre._nodes.size()) {
      std::cerr << "2*N exceeds the total number of nodes.\n";
      std::exit(EXIT_FAILURE);
    }
    // if(2*N >= partitioner_incre_only_handle_edge._nodes.size()) {
    //   std::cerr << "2*N exceeds the total number of nodes.\n";
    //   std::exit(EXIT_FAILURE);
    // }
    if(2*N >= partitioner_full._nodes.size()) {
      std::cerr << "2*N exceeds the total number of nodes.\n";
      std::exit(EXIT_FAILURE);
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());

    // get N random numbers
    std::vector<int> random_nodes = generate_random_nums(partitioner_incre._nodes.size(), N);
    std::vector<int> random_edges = generate_random_nums(partitioner_incre._edges.size(), N);
    std::sort(random_nodes.begin(), random_nodes.end());
    std::sort(random_edges.begin(), random_edges.end());

    // ------------------------------------------------------------------------------

    // remove N nodes randomly
    auto node_it = partitioner_incre._nodes.begin();
    size_t currentIndex = 0;
    auto index_it = random_nodes.begin();
    while (node_it != partitioner_incre._nodes.end() && index_it != random_nodes.end()) {
        if (currentIndex == *index_it) {
            // When the current index matches, erase the element
            partitioner_incre.remove_node(&(*(node_it++))); // first remove the element, then increment node_it
            ++index_it; // Move to the next index
        } else {
            ++node_it; // Move to the next element in the list
        }
        ++currentIndex; // Increment the current index in the list
    }
    // // remove N nodes randomly
    // node_it = partitioner_incre_only_handle_edge._nodes.begin();
    // currentIndex = 0;
    // index_it = random_nodes.begin();
    // while (node_it != partitioner_incre_only_handle_edge._nodes.end() && index_it != random_nodes.end()) {
    //     if (currentIndex == *index_it) {
    //         // When the current index matches, erase the element
    //         partitioner_incre_only_handle_edge.remove_node(&(*(node_it++))); // first remove the element, then increment node_it
    //         ++index_it; // Move to the next index
    //     } else {
    //         ++node_it; // Move to the next element in the list
    //     }
    //     ++currentIndex; // Increment the current index in the list
    // }
    // remove N nodes randomly
    node_it = partitioner_full._nodes.begin();
    currentIndex = 0;
    index_it = random_nodes.begin();
    while (node_it != partitioner_full._nodes.end() && index_it != random_nodes.end()) {
        if (currentIndex == *index_it) {
            // When the current index matches, erase the element
            partitioner_full.remove_node(&(*(node_it++))); // first remove the element, then increment node_it
            ++index_it; // Move to the next index
        } else {
            ++node_it; // Move to the next element in the list
        }
        ++currentIndex; // Increment the current index in the list
    }

    // ------------------------------------------------------------------------------

    // remove N edges randomly
    auto edge_it = partitioner_incre._edges.begin();
    currentIndex = 0;
    index_it = random_edges.begin();
    while (edge_it != partitioner_incre._edges.end() && index_it != random_edges.end()) {
        if (currentIndex == *index_it) {
            // When the current index matches, erase the element
            partitioner_incre.remove_edge(&(*(edge_it++))); // first remove the element, then increment edge_it
            ++index_it; // Move to the next index
        } else {
            ++edge_it; // Move to the next element in the list
        }
        ++currentIndex; // Increment the current index in the list
    }
    // // remove N edges randomly
    // edge_it = partitioner_incre_only_handle_edge._edges.begin();
    // currentIndex = 0;
    // index_it = random_edges.begin();
    // while (edge_it != partitioner_incre_only_handle_edge._edges.end() && index_it != random_edges.end()) {
    //     if (currentIndex == *index_it) {
    //         // When the current index matches, erase the element
    //         partitioner_incre_only_handle_edge.remove_edge(&(*(edge_it++))); // first remove the element, then increment edge_it
    //         ++index_it; // Move to the next index
    //     } else {
    //         ++edge_it; // Move to the next element in the list
    //     }
    //     ++currentIndex; // Increment the current index in the list
    // }
    // remove N edges randomly
    edge_it = partitioner_full._edges.begin();
    currentIndex = 0;
    index_it = random_edges.begin();
    while (edge_it != partitioner_full._edges.end() && index_it != random_edges.end()) {
        if (currentIndex == *index_it) {
            // When the current index matches, erase the element
            partitioner_full.remove_edge(&(*(edge_it++))); // first remove the element, then increment edge_it
            ++index_it; // Move to the next index
        } else {
            ++edge_it; // Move to the next element in the list
        }
        ++currentIndex; // Increment the current index in the list
    }

    // ------------------------------------------------------------------------------

    // add N random edges within the existing nodes
    // this insertion needs to follow topological order
    std::vector<itap::Node*> topo; 
    std::queue<itap::Node*> to_visit;
    for(auto& node : partitioner_incre._nodes) {
      node._dep_cnt_random = 0;
    }
    for(auto& node : partitioner_incre._nodes) {
      if(node._fanins.size() == 0) {
        to_visit.push(&node);
      }
    }
    while(!to_visit.empty()) {
      itap::Node* cur_node = to_visit.front();
      to_visit.pop();
      topo.push_back(cur_node);
      for(auto& edge : cur_node->_fanouts) {
        itap::Node* successor = edge->_to; 
        if(++successor->_dep_cnt_random == successor->_fanins.size()) {
          to_visit.push(successor);
        }
      }
    }
    if(N >= topo.size()) {
      std::cerr << "N exceeds topo.size()...\n";
      std::exit(EXIT_FAILURE);
    }
    std::vector<itap::Node*> topo_full; 
    std::queue<itap::Node*> to_visit_full;
    for(auto& node : partitioner_full._nodes) {
      node._dep_cnt_random = 0;
    }
    for(auto& node : partitioner_full._nodes) {
      if(node._fanins.size() == 0) {
        to_visit_full.push(&node);
      }
    }
    while(!to_visit_full.empty()) {
      itap::Node* cur_node = to_visit_full.front();
      to_visit_full.pop();
      topo_full.push_back(cur_node);
      for(auto& edge : cur_node->_fanouts) {
        itap::Node* successor = edge->_to; 
        if(++successor->_dep_cnt_random == successor->_fanins.size()) {
          to_visit_full.push(successor);
        }
      }
    }
    if(N >= topo_full.size()) {
      std::cerr << "N exceeds topo_full.size()...\n";
      std::exit(EXIT_FAILURE);
    }
    // std::vector<itap::Node*> topo_incre_only_handle_edge; 
    // std::queue<itap::Node*> to_visit_incre_only_handle_edge;
    // for(auto& node : partitioner_incre_only_handle_edge._nodes) {
    //   node._dep_cnt_random = 0;
    // }
    // for(auto& node : partitioner_incre_only_handle_edge._nodes) {
    //   if(node._fanins.size() == 0) {
    //     to_visit_incre_only_handle_edge.push(&node);
    //   }
    // }
    // while(!to_visit_incre_only_handle_edge.empty()) {
    //   itap::Node* cur_node = to_visit_incre_only_handle_edge.front();
    //   to_visit_incre_only_handle_edge.pop();
    //   topo_incre_only_handle_edge.push_back(cur_node);
    //   for(auto& edge : cur_node->_fanouts) {
    //     itap::Node* successor = edge->_to; 
    //     if(++successor->_dep_cnt_random == successor->_fanins.size()) {
    //       to_visit_incre_only_handle_edge.push(successor);
    //     }
    //   }
    // }
    // if(N >= topo_incre_only_handle_edge.size()) {
    //   std::cerr << "N exceeds topo_incre_only_handle_edge.size()...\n";
    //   std::exit(EXIT_FAILURE);
    // }
    // the topological order should be the same
    for(size_t i=0; i<N; i++) {
      if(topo[i]->_name != topo_full[i]->_name) {
        std::cerr << "different topo order...\n"; 
        std::exit(EXIT_FAILURE);
      }
    }
    // for(size_t i=0; i<N; i++) {
    //   if(topo[i]->_name != topo_incre_only_handle_edge[i]->_name) {
    //     std::cerr << "different topo order...\n"; 
    //     std::exit(EXIT_FAILURE);
    //   }
    // }

    // each time select 2 random indices from topo and connect them
    for(size_t i=0; i<N; i++) {
      std::uniform_int_distribution<> dis(i+1, topo.size() - 1); 
      size_t randomIndex = dis(gen);
      // use name to find if there is already an edge between them
      bool has_edge = false;
      for(auto& edge : topo[i]->_fanouts) {
        if(edge->_to->_name == topo[randomIndex]->_name) {
          has_edge = true;
        } 
      }
      if(!has_edge) {
        partitioner_incre.insert_edge(topo[i], topo[randomIndex]);
        // partitioner_incre_only_handle_edge.insert_edge(topo_incre_only_handle_edge[i], topo_incre_only_handle_edge[randomIndex]);
        partitioner_full.insert_edge(topo_full[i], topo_full[randomIndex]);
      }
    }

    // ------------------------------------------------------------------------------
    
    // add N nodes 
    std::vector<itap::Node*> nodes(N);
    for(size_t i=0; i<N; i++) {
      nodes[i] = partitioner_incre.insert_node("itr"+std::to_string(count)+"new_"+std::to_string(i)); 
    }
    // std::vector<itap::Node*> nodes_incre_only_handle_edge(N);
    // for(size_t i=0; i<N; i++) {
    //   nodes_incre_only_handle_edge[i] = partitioner_incre_only_handle_edge.insert_node("itr"+std::to_string(count)+"new_"+std::to_string(i)); 
    // }
    std::vector<itap::Node*> nodes_full(N);
    for(size_t i=0; i<N; i++) {
      nodes_full[i] = partitioner_full.insert_node("itr"+std::to_string(count)+"new_"+std::to_string(i)); 
    }

    // add N edges randomly by connectint the new nodes 
    // to the existing nodes as dependents/successors  
    std::vector<int> random_nodes1 = generate_random_nums(partitioner_incre._nodes.size(), N);
    std::sort(random_nodes1.begin(), random_nodes1.end());
    auto it = random_nodes1.begin();
    size_t listIndex = 0;
    size_t new_node_index = 0;
    auto list_itr = partitioner_full._nodes.begin();
    // auto list_itr2 = partitioner_incre_only_handle_edge._nodes.begin();
    for (auto& element : partitioner_incre._nodes) {
      if (it != random_nodes1.end() && listIndex == *it) {
        if(*it>=partitioner_incre._nodes.size()-N && *it-(partitioner_incre._nodes.size()-N) == new_node_index) {
          // to prevent the new node connected to itself
          // so some of the new nodes will not connect to anyone
          continue;
        }
        std::uniform_int_distribution<> dis(0, partitioner_incre._nodes.size() - 1 - N); 
        size_t randomIndex = dis(gen);  
        if(randomIndex % 2 == 0) {
          partitioner_incre.insert_edge(&element, nodes[new_node_index]);
          partitioner_full.insert_edge(&(*list_itr), nodes_full[new_node_index]);
          // partitioner_incre_only_handle_edge.insert_edge(&(*list_itr2), nodes_incre_only_handle_edge[new_node_index]);
        }
        else {
          partitioner_incre.insert_edge(nodes[new_node_index], &element);
          partitioner_full.insert_edge(nodes_full[new_node_index], &(*list_itr));
          // partitioner_incre_only_handle_edge.insert_edge(nodes_incre_only_handle_edge[new_node_index], &(*list_itr2));
        }
        ++new_node_index;
        ++it; // Move to the next index
      }
      ++list_itr;
      // ++list_itr2;
      ++listIndex; // Increment the current index in the list
    }

    // ------------------------------------------------------------------------------

    check_identical(partitioner_incre, partitioner_full);
    // check_identical(partitioner_incre, partitioner_incre_only_handle_edge);

    if(partitioner_incre.has_cycle_pre_partition() == true) {
      std::cerr << "cycle introduced by incremental operations...\n";
      std::exit(EXIT_FAILURE);
    }
    // if(partitioner_incre_only_handle_edge.has_cycle_pre_partition() == true) {
    //   std::cerr << "cycle introduced by incremental operations...\n";
    //   std::exit(EXIT_FAILURE);
    // }
    if(partitioner_full.has_cycle_pre_partition() == true) {
      std::cerr << "cycle introduced by incremental operations...\n";
      std::exit(EXIT_FAILURE);
    }

    // ------------------------------------------------------------------------------

    partitioner_incre.partition(true);
    // partitioner_incre_only_handle_edge.partition(true, true);
    partitioner_full.partition();

    // ------------------------------------------------------------------------------

    std::cout << "incremental "; 
    partitioner_incre.run_graph();
    // std::cout << "incremental_only_handle_edge "; 
    // partitioner_incre_only_handle_edge.run_graph();
    std::cout << "full "; 
    partitioner_full.run_graph();

    // ------------------------------------------------------------------------------

    // check cluster_cnt
    if(!partitioner_incre.is_cluster_cnt_valid()) {
      std::cerr << "cluster_cnt not correct...\n";
      std::exit(EXIT_FAILURE);
    } 

    // if(count == num_itr - 1) {
    //   partitioner_incre.dump_graph();
    // }

    count++;
  }
  if(!partitioner_incre.is_partition_valid()) {
    std::cerr << "partition invalid...\n";
    std::exit(EXIT_FAILURE);
  }
  // if(partitioner_incre_only_handle_edge.has_cycle_post_partition()) {
  //   std::cerr << "only_handle_edge: partition invalid...\n";
  //   std::exit(EXIT_FAILURE);
  // }
  if(!partitioner_full.is_partition_valid()) {
    std::cerr << "partition invalid...\n";
    std::exit(EXIT_FAILURE);
  }

}
