#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest.h>
#include "itap.hpp"

// --------------------------------------------------------
// Testcase: check cycle by manually adding nodes and edges 
// --------------------------------------------------------
TEST_CASE("seg_test" * doctest::timeout(300)) {

  itap::iTAP partitioner;

  partitioner.set_partition_size(4);

  itap::Node* n0 = partitioner.insert_node("0");
  itap::Node* n1 = partitioner.insert_node("1");
  itap::Node* n2 = partitioner.insert_node("2");
  itap::Node* n3 = partitioner.insert_node("3");
  itap::Node* n4 = partitioner.insert_node("4");
  itap::Node* n5 = partitioner.insert_node("5");
  itap::Node* n6 = partitioner.insert_node("6");
  itap::Node* n7 = partitioner.insert_node("7");
  itap::Node* n8 = partitioner.insert_node("8");
  itap::Node* n9 = partitioner.insert_node("9");
  itap::Node* n10 = partitioner.insert_node("10");
  itap::Node* n11 = partitioner.insert_node("11");
  itap::Node* n12 = partitioner.insert_node("12");
  itap::Node* n13 = partitioner.insert_node("13");
  itap::Node* n14 = partitioner.insert_node("14");
  itap::Node* n15 = partitioner.insert_node("15");
  itap::Node* n16 = partitioner.insert_node("16");

  itap::Edge* e1_10 = partitioner.insert_edge(n1, n10);
  itap::Edge* e10_11 = partitioner.insert_edge(n10, n11);
  itap::Edge* e11_12 = partitioner.insert_edge(n11, n12);
  itap::Edge* e12_13 = partitioner.insert_edge(n12, n13);
  itap::Edge* e13_14 = partitioner.insert_edge(n13, n14);
  itap::Edge* e0_2 = partitioner.insert_edge(n0, n2);
  itap::Edge* e2_3 = partitioner.insert_edge(n2, n3);
  itap::Edge* e3_14 = partitioner.insert_edge(n3, n14);
  itap::Edge* e14_15 = partitioner.insert_edge(n14, n15);
  itap::Edge* e0_15 = partitioner.insert_edge(n0, n15);
  itap::Edge* e15_16 = partitioner.insert_edge(n15, n16);
  itap::Edge* e2_4 = partitioner.insert_edge(n2, n4);
  itap::Edge* e4_5 = partitioner.insert_edge(n4, n5);
  itap::Edge* e5_8 = partitioner.insert_edge(n5, n8);
  itap::Edge* e8_9 = partitioner.insert_edge(n8, n9);
  itap::Edge* e5_6 = partitioner.insert_edge(n5, n6);
  itap::Edge* e6_7 = partitioner.insert_edge(n6, n7);

  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 17);
  REQUIRE(partitioner.has_cycle_post_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_post_partition() == false);
}


