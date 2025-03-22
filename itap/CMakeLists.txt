add_library(itap itap.cpp partition_cuda.cu)
#add_library(partition_cuda partition_cuda.cu)
#target_link_libraries(itap PUBLIC partition_cuda)

# include taskflow
target_include_directories(itap
  PUBLIC ${ITAP_3RD_PARTY_DIR}/taskflow)

# find the pthreads library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(itap PRIVATE Threads::Threads)
