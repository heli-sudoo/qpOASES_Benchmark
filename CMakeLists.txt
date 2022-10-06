Project (TimeBenchmark)

set(CXX_FLAG)
include_directories("../../qpOASES/include")

find_library(QPOASES_LIB 
             NAMES  libqpOASES.a 
             PATHS $ENV{QPOASES_LIB_PATH})

add_executable(time_benchmark time_benchmark.cpp)
target_link_libraries(time_benchmark ${QPOASES_LIB})