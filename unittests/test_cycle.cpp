
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest.h>
#include "itap.hpp"

// --------------------------------------------------------
// Testcase: check cycle by manually adding nodes and edges 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.manual_simple" * doctest::timeout(300)) {

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

  REQUIRE(partitioner.num_nodes() == 17);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle simple 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.simple" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/simple.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  REQUIRE(partitioner.num_nodes() == 17);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle c17 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.c17" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c17.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  REQUIRE(partitioner.num_nodes() == 25);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle c432 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.c432" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c432.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 483);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);  
}

// --------------------------------------------------------
// Testcase: check cycle c499 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.c499" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c499.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 604);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle c880 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.c880" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c880.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 791);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle c1355 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.c1355" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c1355.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 617);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle c1908 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.c1908" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c1908.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 757);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle c2670 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.c2670" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c2670.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 1365);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle c3540 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.c3540" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c3540.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 2314);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle c5315 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.c5315" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c5315.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 3245);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle c6288 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.c6288" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c6288.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 4837);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle c7522 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.c7522" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c7522.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 3802);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle s27 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.s27" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/s27.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 81);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle s344 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.s344" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/s344.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 526);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle s349 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.s349" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/s349.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 550);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle s400 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.s400" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/s400.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 626);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle s510 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.s510" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/s510.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 849);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle s1196 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.s1196" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/s1196.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 1854);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle s1494 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.s1494" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/s1494.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 2292);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle tv80 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.tv80" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/tv80.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 17038);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle wb_dma 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.wb_dma" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/wb_dma.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 13125);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle usb_phy_ispd 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.usb_phy_ispd" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/usb_phy_ispd.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 2447);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 100;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle des_perf 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.des_perf" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/des_perf.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 303690);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);

  // incremental partition
  size_t itr = 10;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle vga_lcd 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.vga_lcd" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/vga_lcd.txt");

  // partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.set_partition_size(10);
  REQUIRE(partitioner.num_nodes() == 397809);

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.num_nodes() == partitioner.num_nodes());
  REQUIRE(partitioner.has_cycle_post_partition() == false);

  // incremental partition
  size_t itr = 10;
  while(itr--) {
    partitioner.random_incre_ops(partitioner.num_nodes()/3);
    REQUIRE(partitioner.has_cycle_pre_partition() == false);
    partitioner.partition(true);
    REQUIRE(partitioner.is_partition_valid() == true);
    REQUIRE(partitioner.is_cluster_cnt_valid() == true);
  }

  // full partition
  partitioner.partition();
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle manual case 1 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.manual_case1" * doctest::timeout(300)) {

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

  REQUIRE(partitioner.num_nodes() == 4);
  REQUIRE(partitioner.is_partition_valid() == true);

  // apply one incremental operation, this should cause cycle
  partitioner.insert_edge(B, C);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle manual case 2 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.manual_case2" * doctest::timeout(300)) {

  itap::iTAP partitioner;

  // ---------------------------------------------------
  itap::Node* A = partitioner.insert_node("A");
  itap::Node* B = partitioner.insert_node("B");

  itap::Edge* AB = partitioner.insert_edge(A, B);
  // ---------------------------------------------------

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 2);
  REQUIRE(partitioner.is_partition_valid() == true);

  // ---------------------------------------------------
  itap::Node* C = partitioner.insert_node("C");  
  itap::Node* D = partitioner.insert_node("D");  
  itap::Node* E = partitioner.insert_node("E");  
  itap::Node* F = partitioner.insert_node("F");  
  itap::Node* G = partitioner.insert_node("G");  

  itap::Edge* CD = partitioner.insert_edge(C, D);
  itap::Edge* DE = partitioner.insert_edge(D, E);
  itap::Edge* DF = partitioner.insert_edge(D, F);
  itap::Edge* EG = partitioner.insert_edge(E, G);
  itap::Edge* FG = partitioner.insert_edge(F, G);

  // ---------------------------------------------------
  REQUIRE(partitioner.num_nodes() == 7);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  partitioner.partition(true);
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle manual case 3 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.manual_case3" * doctest::timeout(300)) {

  itap::iTAP partitioner;

  // ---------------------------------------------------
  itap::Node* A = partitioner.insert_node("A");
  itap::Node* B = partitioner.insert_node("B");

  // ---------------------------------------------------

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 2);
  REQUIRE(partitioner.is_partition_valid() == true);

  // ---------------------------------------------------
  itap::Node* C = partitioner.insert_node("C");  
  itap::Node* D = partitioner.insert_node("D");  

  itap::Edge* AD = partitioner.insert_edge(A, D);
  itap::Edge* CD = partitioner.insert_edge(C, D);
  itap::Edge* BD = partitioner.insert_edge(B, D);

  // ---------------------------------------------------
  REQUIRE(partitioner.num_nodes() == 4);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  partitioner.partition(true);
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle manual case 4 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.manual_case4" * doctest::timeout(300)) {

  itap::iTAP partitioner;

  // ---------------------------------------------------
  itap::Node* A = partitioner.insert_node("A");
  itap::Node* B = partitioner.insert_node("B");

  // ---------------------------------------------------

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 2);
  REQUIRE(partitioner.is_partition_valid() == true);

  // ---------------------------------------------------
  itap::Node* C = partitioner.insert_node("C");  
  itap::Node* D = partitioner.insert_node("D");  
  itap::Node* E = partitioner.insert_node("E");  
  itap::Node* F = partitioner.insert_node("F");  

  itap::Edge* AD = partitioner.insert_edge(A, D);
  itap::Edge* DB = partitioner.insert_edge(D, B);
  itap::Edge* DE = partitioner.insert_edge(D, E);
  itap::Edge* DF = partitioner.insert_edge(D, F);
  itap::Edge* CF = partitioner.insert_edge(C, F);

  // ---------------------------------------------------
  REQUIRE(partitioner.num_nodes() == 6);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  partitioner.partition(true);
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle manual case 5 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.manual_case5" * doctest::timeout(300)) {

  itap::iTAP partitioner;

  // ---------------------------------------------------
  itap::Node* A = partitioner.insert_node("A");
  itap::Node* B = partitioner.insert_node("B");
  itap::Node* C = partitioner.insert_node("C");

  itap::Edge* AB = partitioner.insert_edge(A, B);
  itap::Edge* BC = partitioner.insert_edge(B, C);

  // ---------------------------------------------------

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 3);
  REQUIRE(partitioner.is_partition_valid() == true);

  // ---------------------------------------------------
  itap::Node* D = partitioner.insert_node("D");  
  itap::Node* E = partitioner.insert_node("E");  

  itap::Edge* AD = partitioner.insert_edge(A, D);
  itap::Edge* DC = partitioner.insert_edge(D, C);
  itap::Edge* DE = partitioner.insert_edge(D, E);

  // ---------------------------------------------------
  REQUIRE(partitioner.num_nodes() == 5);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  partitioner.partition(true);
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle manual case 6 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.manual_case6" * doctest::timeout(300)) {

  itap::iTAP partitioner;

  // ---------------------------------------------------
  itap::Node* A = partitioner.insert_node("A");
  itap::Node* B = partitioner.insert_node("B");
  itap::Node* C = partitioner.insert_node("C");
  itap::Node* G = partitioner.insert_node("G");

  itap::Edge* AB = partitioner.insert_edge(A, B);
  itap::Edge* BC = partitioner.insert_edge(B, C);

  // ---------------------------------------------------

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 4);
  REQUIRE(partitioner.is_partition_valid() == true);

  // ---------------------------------------------------
  itap::Node* D = partitioner.insert_node("D");  
  itap::Node* E = partitioner.insert_node("E");  
  itap::Node* F = partitioner.insert_node("F");  
  itap::Node* H = partitioner.insert_node("H");  

  itap::Edge* AD = partitioner.insert_edge(A, D);
  itap::Edge* AE = partitioner.insert_edge(A, E);
  itap::Edge* DB = partitioner.insert_edge(D, B);
  itap::Edge* EB = partitioner.insert_edge(E, B);
  itap::Edge* DF = partitioner.insert_edge(D, F);
  itap::Edge* DG = partitioner.insert_edge(D, G);
  itap::Edge* BH = partitioner.insert_edge(B, H);
  itap::Edge* FH = partitioner.insert_edge(F, H);

  // ---------------------------------------------------
  REQUIRE(partitioner.num_nodes() == 8);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  partitioner.partition(true);
  REQUIRE(partitioner.is_partition_valid() == true);
}

// --------------------------------------------------------
// Testcase: check cycle manual case 7 
// --------------------------------------------------------
TEST_CASE("check_cycle_post_partition.manual_case7" * doctest::timeout(300)) {

  itap::iTAP partitioner;

  // ---------------------------------------------------
  itap::Node* A = partitioner.insert_node("A");
  itap::Node* B = partitioner.insert_node("B");
  itap::Node* C = partitioner.insert_node("C");

  itap::Edge* AB = partitioner.insert_edge(A, B);

  // ---------------------------------------------------

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 3);
  REQUIRE(partitioner.is_partition_valid() == true);

  // ---------------------------------------------------
  itap::Node* D = partitioner.insert_node("D");  

  itap::Edge* CD = partitioner.insert_edge(C, D);
  itap::Edge* DA = partitioner.insert_edge(D, A);

  // ---------------------------------------------------
  REQUIRE(partitioner.num_nodes() == 4);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  partitioner.partition(true);
  REQUIRE(partitioner.is_partition_valid() == true);
}












