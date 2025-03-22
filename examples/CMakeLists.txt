# example: exp.cpp
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/examples)
add_executable(final_project_test ${ITAP_EXAMPLE_DIR}/final_project_test.cpp)

list(APPEND ITAP_EXAMPLES
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


