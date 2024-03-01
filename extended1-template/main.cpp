/// Created by Marius Mikucionis <marius@cs.aau.dk>
/**
 * Purpose: compare the performance of number_series and number_series_wrap.
 */
#include "number_series.hpp"

#include <chrono>

constexpr auto ns_number = 100'000;
constexpr auto ns_length = 100;

int main()
{
    using namespace data_series;
    using clk = std::chrono::high_resolution_clock;
    using std::chrono::duration;
    using std::milli;
    using std::cout;
    using std::endl;

    // Part 2
    std::vector<number_series> vv;
    vv.reserve(ns_number);  // preallocate memory

    // TODO: Populate the vv with data here

    auto t0 = clk::now();
    // TODO: std::sort(vv.begin(), vv.end());
    auto t1 = clk::now();
    cout << "Sorting values: " << duration<double, milli>(t1 - t0).count() << " ms\n";

    // Part 3
    // Note that this is the exact same code as for Part 1 except using number_series_wrap
    auto vw = std::vector<number_series_wrap>{};
    vw.reserve(ns_number);  // preallocate memory

    // TODO: Populate the vw with data here

    t0 = clk::now();
    // TODO: std::sort(vw.begin(), vw.end());
    t1 = clk::now();
    cout << "Sorting wrapped pointers: " << duration<double, milli>(t1 - t0).count() << " ms\n";

    cout << "sizeof(number_series): " << sizeof(number_series) << '\n';
}

/**
Important: measure the optimized ("Release") build!

Sample result:

Sorting values: XXX ms
Sorting wrapped pointers: YYY ms
sizeof(number_series): ZZZ

Interpretation:

Part 3 is about XX% ****er than Part 2.
PUT YOUR CONCLUSION HERE

Sample result, if number_series is padded with array:

Sorting values: XXX ms
Sorting wrapped pointers: YYY ms
sizeof(number_series): ZZZ

Part 3 is about XX% ****er than Part 2.
PUT YOUR CONCLUSION HERE

*/
