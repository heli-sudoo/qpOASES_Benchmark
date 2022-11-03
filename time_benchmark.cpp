#include "time_benchmark.h"
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <numeric>
#include <cmath>
#include <algorithm>
int main()

{
    printf("Benchmark qpOASES for solving a sequenc of QP problems \n\n\n");
    benchmark_qp_seq();
}

void benchmark_qp_seq()
{
    std::string mpc_log_fname = "../MC_QP_LOG";
    std::fstream fstrm(mpc_log_fname);
    if (!fstrm.is_open())
    {
        printf("Failed to open test file \n");
        return;
    }

    Options options;
    options.setToMPC();
    options.printLevel = PL_NONE;
    std::vector<real_t> cpu_times;

    /* Read the first QP Data and Set up SQP problem*/
    QPData data;
    printf("\n\n");
    printf("=====================\n");
    printf("read one qp data \n");
    read_one_data_from_file(fstrm, data);
    SQProblem sqp(data.n_var, data.n_con);
    sqp.setOptions(options);

    // solve the first QP
    sqp.init(data.H.data(),
             data.g.data(),
             data.A.data(),
             data.lb.data(),
             data.ub.data(),
             data.lbA.data(),
             data.ubA.data(), data.nWSR, &data.cpu_time);      
    
    printf("n_WSR = %d, cputime = %f seconds\n", data.nWSR, data.cpu_time);
    printf("=====================\n");
    cpu_times.push_back(data.cpu_time);

    while (!fstrm.eof())
    {
        printf("\n\n");
        printf("=====================\n");
        printf("read one qp data \n");
        read_one_data_from_file(fstrm, data);

        printf("solving QP \n");
        if (data.hotstart)
        {
            sqp.hotstart(data.H.data(),
                         data.g.data(),
                         data.A.data(),
                         data.lb.data(),
                         data.ub.data(),
                         data.lbA.data(),
                         data.ubA.data(), data.nWSR, &data.cpu_time);
        }
        else
        {
            sqp.init(data.H.data(),
                     data.g.data(),
                     data.A.data(),
                     data.lb.data(),
                     data.ub.data(),
                     data.lbA.data(),
                     data.ubA.data(), data.nWSR, &data.cpu_time);
        }
        printf("n_WSR = %d, cputime = %f seconds\n", data.nWSR, data.cpu_time);
        printf("=====================\n");
        cpu_times.push_back(data.cpu_time);
    }

    printf("Mean = %f, Std = %f, Min = %f, Max = %f \n", mean(cpu_times), std_variation(cpu_times),
           *std::min_element(cpu_times.begin(), cpu_times.end()), *std::max_element(cpu_times.begin(), cpu_times.end()));
}

void read_one_data_from_file(std::fstream &fstrm, QPData &data)
{
    std::string line, word;

    // Iterate through each line of the file
    while (getline(fstrm, line))
    {
        if (line == "INIT")
        {
            data.hotstart = false;
        }

        if (line == "HOTSTART")
        {
            data.hotstart = true;
        }

        // If read n_var
        if (line == "n_var=")
        {
            getline(fstrm, line); // read n_var
            data.n_var = std::stoi(line);
        }

        // If read n_con
        if (line == "n_con=")
        {
            getline(fstrm, line); // read n_var
            data.n_con = std::stoi(line);
        }

        // If read H
        if (line == "H=")
        {
            data.H.clear();
            while (data.H.size() < data.n_var * data.n_var)
            {
                getline(fstrm, line);          // read n_var
                std::stringstream lstrm(line); // break each line to a stream with delimeter (,)
                while (lstrm >> word)
                {
                    data.H.push_back(std::stof(word));
                }
            }
        }

        // If read g
        if (line == "g=")
        {
            data.g.clear();
            while (data.g.size() < data.n_var)
            {
                getline(fstrm, line);          // read n_var
                std::stringstream lstrm(line); // break each line to a stream with delimeter (,)

                while (lstrm >> word)
                {
                    data.g.push_back(std::stof(word));
                }
            }
        }

        // If read A
        if (line == "A=")
        {
            // printf("reading A \n");
            data.A.clear();
            // fstrm.ignore(256, '\n');
            while (data.A.size() < data.n_var * data.n_con)
            {
                getline(fstrm, line);          // read n_var
                std::stringstream lstrm(line); // break each line to a stream with delimeter (,)

                while (lstrm >> word)
                {
                    data.A.push_back(std::stof(word));
                }
            }
        }

        // If read lb
        if (line == "lb=")
        {
            data.lb.clear();
            // fstrm.ignore(256, '\n');

            while (data.lb.size() < data.n_var)
            {
                getline(fstrm, line);          // read n_var
                std::stringstream lstrm(line); // break each line to a stream with delimeter (,)

                while (lstrm >> word)
                {
                    data.lb.push_back(std::stof(word));
                }
            }
        }

        // If read ub
        if (line == "ub=")
        {
            data.ub.clear();
            while (data.ub.size() < data.n_var)
            {
                getline(fstrm, line);          // read n_var
                std::stringstream lstrm(line); // break each line to a stream with delimeter (,)

                while (lstrm >> word)
                {
                    data.ub.push_back(std::stof(word));
                }
            }
        }
        // If read lbA
        if (line == "lbA=")
        {
            data.lbA.clear();
            // fstrm.ignore(256, '\n');
            while (data.lbA.size() < data.n_con)
            {
                getline(fstrm, line);          // read n_var
                std::stringstream lstrm(line); // break each line to a stream with delimeter (,)

                while (lstrm >> word)
                {
                    data.lbA.push_back(std::stof(word));
                }
            }
        }

        // If read lb
        if (line == "ubA=")
        {
            data.ubA.clear();
            while (data.ubA.size() < data.n_con)
            {
                getline(fstrm, line);          // read n_var
                std::stringstream lstrm(line); // break each line to a stream with delimeter (,)

                while (lstrm >> word)
                {
                    data.ubA.push_back(std::stof(word));
                }
            }
        }

        // If read nWSR
        if (line == "nWSR=")
        {
            getline(fstrm, line); // read n_var
            data.nWSR = std::stoi(line);
        }

        // If read cputime
        if (line == "cputime=")
        {
            // fstrm.ignore(256, '\n');
            getline(fstrm, line); // read cputime
            data.cpu_time = std::stof(line);
            break;
        }
    }
}

real_t sum(const std::vector<real_t> &v)
{
    // return std::accumulate(v.begin(), v.end(), 0);
    real_t s(0);
    for (auto a : v)
    {
        s = s + a;
    }
    return s;
}
real_t mean(const std::vector<real_t> &v)
{
    return sum(v) / v.size();
}
real_t sq_sum(const std::vector<real_t> &v)
{
    real_t s(0);
    for (auto a : v)
    {
        s = s + a * a;
    }
    return s;
}
real_t std_variation(const std::vector<real_t> &v)
{
    real_t m = mean(v);
    real_t s(0);
    for (auto a : v)
    {
        s = s + (a - m) * (a - m);
    }
    return sqrt(s / v.size());
}
