#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest.h>
#include "itap.hpp"

// --------------------------------------------------------
// Testcase: insert_node 
// --------------------------------------------------------
TEST_CASE("insert_node" * doctest::timeout(300)) {

  itap::iTAP partitioner;

  partitioner.set_partition_size(4);

  itap::Node* A = partitioner.insert_node();
  
  REQUIRE(partitioner.num_nodes() == 1);

}

// --------------------------------------------------------
// Testcase: insert_edge 
// --------------------------------------------------------
TEST_CASE("insert_edge" * doctest::timeout(300)) {

  itap::iTAP partitioner;

  partitioner.set_partition_size(4);

  itap::Node* A = partitioner.insert_node();
  itap::Node* B = partitioner.insert_node();

  itap::Edge* AB = partitioner.insert_edge(A, B);

  REQUIRE(partitioner.num_nodes() == 2);
  REQUIRE(A->num_fanouts() == 1);
  REQUIRE(A->num_fanins() == 0);
  REQUIRE(B->num_fanouts() == 0);
  REQUIRE(B->num_fanins() == 1);
  REQUIRE(A->has_fanout(AB) == true);
  REQUIRE(B->has_fanin(AB) == true);

}

// --------------------------------------------------------
// Testcase: remove_edge 
// --------------------------------------------------------
TEST_CASE("remove_edge" * doctest::timeout(300)) {

  itap::iTAP partitioner;

  partitioner.set_partition_size(4);

  itap::Node* A = partitioner.insert_node();
  itap::Node* B = partitioner.insert_node();

  itap::Edge* AB = partitioner.insert_edge(A, B);

  REQUIRE(partitioner.num_nodes() == 2);
  REQUIRE(A->num_fanouts() == 1);
  REQUIRE(A->num_fanins() == 0);
  REQUIRE(B->num_fanouts() == 0);
  REQUIRE(B->num_fanins() == 1);
  REQUIRE(A->has_fanout(AB) == true);
  REQUIRE(B->has_fanin(AB) == true);

  partitioner.remove_edge(AB);

  REQUIRE(A->num_fanouts() == 0);
  REQUIRE(A->num_fanins() == 0);
  REQUIRE(B->num_fanouts() == 0);
  REQUIRE(B->num_fanins() == 0);
  REQUIRE(A->has_fanout(AB) == false);
  REQUIRE(B->has_fanin(AB) == false);

}

// --------------------------------------------------------
// Testcase: remove_node 
// --------------------------------------------------------
TEST_CASE("remove_node" * doctest::timeout(300)) {

  itap::iTAP partitioner;

  partitioner.set_partition_size(4);

  itap::Node* A = partitioner.insert_node();
  itap::Node* B = partitioner.insert_node();
  itap::Node* C = partitioner.insert_node();
  itap::Node* D = partitioner.insert_node();
  itap::Node* E = partitioner.insert_node();

  itap::Edge* AB = partitioner.insert_edge(A, B);
  itap::Edge* CB = partitioner.insert_edge(C, B);
  itap::Edge* BD = partitioner.insert_edge(B, D);
  itap::Edge* BE = partitioner.insert_edge(B, E);

  REQUIRE(partitioner.num_nodes() == 5);
  REQUIRE(A->num_fanouts() == 1);
  REQUIRE(C->num_fanouts() == 1);
  REQUIRE(B->num_fanins() == 2);
  REQUIRE(B->num_fanouts() == 2);
  REQUIRE(D->num_fanins() == 1);
  REQUIRE(E->num_fanins() == 1);

  partitioner.remove_node(B);

  REQUIRE(partitioner.num_nodes() == 4);
  REQUIRE(A->num_fanouts() == 0);
  REQUIRE(C->num_fanouts() == 0);
  REQUIRE(D->num_fanins() == 0);
  REQUIRE(E->num_fanins() == 0);

}





































