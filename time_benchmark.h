#ifndef TIME_BENCHMARK_H
#define TIME_BENCHMARK_H

#include "qpOASES.hpp"
#include <vector>
#include <string>
#include <fstream>

USING_NAMESPACE_QPOASES

struct QPData
{
    bool hotstart;
    int n_var;
    int n_con;
    int nWSR;
    real_t cpu_time;
    std::vector<real_t> H;
    std::vector<real_t> A;
    std::vector<real_t> g;
    std::vector<real_t> lb;
    std::vector<real_t> ub;
    std::vector<real_t> lbA;
    std::vector<real_t> ubA;
};


void read_one_data_from_file(std::fstream&, QPData&);
void benchmark_qp_seq();
#endif