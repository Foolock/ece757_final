enable_testing()

include(${ITAP_3RD_PARTY_DIR}/doctest/doctest.cmake)

list(APPEND ITAP_UNITTESTS 
  test_ops 
  seg_test
  test_cycle
)

string(FIND '${CMAKE_CXX_FLAGS}' "-fsanitize" sanitize)
#message("sanitize='${sanitize}'")

# if(${sanitize} EQUAL -1)
#   message(STATUS "Add test_exception to unit tests")
#   list(APPEND ITAP_UNITTESTS test_exceptions)
# endif()


find_package(Threads REQUIRED)
foreach(unittest IN LISTS ITAP_UNITTESTS)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/unittests)
  add_executable(${unittest} ${unittest}.cpp)
  target_link_libraries(${unittest} 
    PRIVATE Threads::Threads
    PUBLIC itap)
  target_include_directories(${unittest} 
    PRIVATE 
    ${ITAP_3RD_PARTY_DIR}/doctest
    PUBLIC
    ${ITAP_3RD_PARTY_DIR}/taskflow
    ${PROJECT_SOURCE_DIR}/itap
  )
  doctest_discover_tests(${unittest})
endforeach()



