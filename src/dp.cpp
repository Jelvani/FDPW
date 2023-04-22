#include <cstdlib>
#include <vector>
#include <iostream>
#include <cstdint>
#include <numeric>
#include <chrono>
#include <functional>
#include <string>
#include <type_traits>
using namespace std;

#define MAX 1000000

/*
Different methods of computing an inner product in C++
*/


//generated with GPT
template<typename Func, typename... Args>
void benchmark(string func_name, Func func, Args&&... args) {

    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();

    // Call the function to be benchmarked
    std::invoke(func, std::forward<Args>(args)...);

    // Stop the timer
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time in microseconds
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Print the function name and elapsed time
    std::cout << func_name << ": " << elapsed.count() << " μs" << std::endl;
}

uint64_t dp_naive(vector<uint64_t> d1, vector<uint64_t> d2)
{
    uint64_t dim = d1.size();
    uint64_t accum = 0;
    for(uint64_t i = 0; i < dim; i++)
    {
        accum += d1[i]*d2[i];
    }

    return accum;
}

uint64_t dp_modern(vector<uint64_t> d1, vector<uint64_t> d2)
{
    return inner_product(std::begin(d1), std::end(d1), std::begin(d2), (uint64_t)0);
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

    benchmark("dp_naive",dp_naive,d1,d2);
    benchmark("dp_modern",dp_modern,d1,d2);
    return 0;

}
