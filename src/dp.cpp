#include <cstdlib>
#include <vector>
#include <iostream>
#include <cstdint>
#include <numeric>
#include <unistd.h>
#ifdef PARA
#include <omp.h>
#endif
#include "benchmark.hpp"

using namespace std;

#define MAX 1000000

/*
Different methods of computing an inner product in C++
*/

uint64_t dp_naive(vector<uint64_t> d1, vector<uint64_t> d2)
{
    uint64_t dim = d1.size();
    uint64_t accum = 0;

    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 0;

    #ifdef PARA
    omp_set_num_threads(8);

    #pragma omp parallel for reduction (+:accum)
    #endif
    for(uint64_t i = 0; i < dim; i++)
    {
        accum += d1[i]*d2[i];
        //nanosleep(&tim , &tim2); //we really just need a function call overhead
    }

    return accum;
}

uint64_t dp_modern(vector<uint64_t> d1, vector<uint64_t> d2)
{
    return std::inner_product(std::begin(d1), std::end(d1), std::begin(d2), (uint64_t)0);

}

int main(int argc, char* argv[])
{

    if(argc < 2)
    {
        cout << "Pass vector dimension" << endl;
        return 0;
    }
    uint64_t dim = stoll(argv[1]);

    vector<uint64_t> d1(dim);
    vector<uint64_t> d2(dim);

    for(uint64_t i = 0; i < dim; i++)
    {
        d1[i] = rand() % MAX;
        d2[i] = rand() % MAX;
    }

    //dummy run to warmup cache
    volatile auto dummy = dp_modern(d1,d2);
    cout << "start" << endl;
    benchmark("dp_naive",dp_naive,d1,d2);
    benchmark("dp_modern",dp_modern,d1,d2);
    return 0;

}
