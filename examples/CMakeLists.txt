# example: exp.cpp
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/examples)
add_executable(simple ${ITAP_EXAMPLE_DIR}/simple.cpp)
add_executable(c17 ${ITAP_EXAMPLE_DIR}/c17.cpp)
add_executable(large_circuit ${ITAP_EXAMPLE_DIR}/large_circuit.cpp)
add_executable(manual1 ${ITAP_EXAMPLE_DIR}/manual1.cpp)
add_executable(exp ${ITAP_EXAMPLE_DIR}/exp.cpp)
add_executable(exp_objectpool ${ITAP_EXAMPLE_DIR}/exp_objectpool.cpp)
add_executable(cuda_test ${ITAP_EXAMPLE_DIR}/cuda_test.cpp)
add_executable(final_project_test ${ITAP_EXAMPLE_DIR}/final_project_test.cpp)

list(APPEND ITAP_EXAMPLES
  simple
  c17
  large_circuit 
  manual1
  exp
  exp_objectpool
  cuda_test
  final_project_test
)

find_package(Threads REQUIRED)
foreach(example IN LISTS ITAP_EXAMPLES) 
  # include OpenTimer
  target_include_directories(${example}
    PUBLIC 
    ${ITAP_3RD_PARTY_DIR}/taskflow
    ${PROJECT_SOURCE_DIR}/itap)

  # link external libaries
  target_link_libraries(${example}
    PRIVATE Threads::Threads
    PUBLIC itap
  )
endforeach()


