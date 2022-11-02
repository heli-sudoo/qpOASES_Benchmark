Project (TimeBenchmark)

set(CMAKE_CXX_FLAG "-std=c++11")
include_directories($ENV{QPOASES_INCLUDE})

find_library(QPOASES_LIB 
             NAMES  libqpOASES.a 
             PATHS $ENV{QPOASES_LIB_PATH})

add_executable(time_benchmark time_benchmark.cpp)
target_link_libraries(time_benchmark ${QPOASES_LIB})