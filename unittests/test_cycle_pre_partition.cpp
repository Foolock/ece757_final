#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest.h>
#include "itap.hpp"


// --------------------------------------------------------
// Testcase: check cycle by manually adding nodes and edges 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.manual" * doctest::timeout(300)) {

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
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition();
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
}

// --------------------------------------------------------
// Testcase: check cycle simple 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.simple" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/simple.txt");

  partitioner.set_partition_size(4);
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 17);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
}

// --------------------------------------------------------
// Testcase: check cycle c17 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.c17" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c17.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 25);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle c432 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.c432" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c432.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 483);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle c499 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.c499" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c499.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 604);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle c880 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.c880" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c880.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 791);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle c1355 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.c1355" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c1355.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 617);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle c1908 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.c1908" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c1908.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 757);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle c2670 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.c2670" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c2670.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 1365);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle c3540 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.c3540" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c3540.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 2314);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle c5315 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.c5315" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c5315.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 3245);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle c6288 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.c6288" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c6288.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 4837);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle c7522 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.c7522" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/c7522.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 3802);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle s27 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.s27" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/s27.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 81);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle s344 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.s344" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/s344.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 526);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle s349 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.s349" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/s349.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 550);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle s400 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.s400" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/s400.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 626);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle s510 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.s510" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/s510.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 849);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle s1196 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.s1196" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/s1196.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 1854);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle s1494 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.s1494" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/s1494.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 2292);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle tv80 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.tv80" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/tv80.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 17038);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle wb_dma 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.wb_dma" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/wb_dma.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 13125);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle usb_phy_ispd 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.usb_phy_ispd" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/usb_phy_ispd.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 2447);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle des_perf 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.des_perf" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/des_perf.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 303690);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}

// --------------------------------------------------------
// Testcase: check cycle vga_lcd 
// --------------------------------------------------------
TEST_CASE("check_cycle_pre_partition.vga_lcd" * doctest::timeout(300)) {

  itap::iTAP partitioner("../../benchmark/vga_lcd.txt");

  partitioner.set_partition_size(partitioner.num_nodes());
  partitioner.partition();

  REQUIRE(partitioner.num_nodes() == 397809);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

  // test incremental ops
  partitioner.random_incre_ops(partitioner.num_nodes()/3);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);
  partitioner.partition(true);
  REQUIRE(partitioner.has_cycle_pre_partition() == false);

}



































































