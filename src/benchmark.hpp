#include <chrono>
#include <functional>
#include <string>
//generated with GPT
template<typename Func, typename... Args>
void benchmark(std::string func_name, Func func, Args&&... args) {

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