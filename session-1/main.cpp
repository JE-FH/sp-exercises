// session-1.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <chrono>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std::chrono;

void swap_ends(int arr[], int size) { // #1
	for (int i = size / 2 - 1, j = size - 1; i >= 0; --i, --j)
		std::swap(arr[i], arr[j]); // (1)
}

void swap_ends(std::vector<int>&arr) { // #2
	for (int i = arr.size() / 2 - 1, j = arr.size() - 1; i >= 0; --i, --j)
		std::swap(arr[i], arr[j]); // same syntax and behavior as (1)
}

constexpr int arr_size = 10'000'000;
std::vector<int> vec;
int arr[arr_size];

double bench(std::function<void()> const& f) {
	f();
	auto t0 = high_resolution_clock::now();
	f();
	auto t1 = high_resolution_clock::now();
	return duration<double, std::milli>(t1 - t0).count();

}

int* sort(const int arr[], size_t arr_size) {
	int* copy = new int[arr_size];
	memcpy(copy, arr, arr_size * sizeof(int));
	std::sort(copy, copy + arr_size);
	return copy;
}

std::vector<int> sort(std::vector<int> vec) {
	std::vector<int> copy;
	copy.resize(vec.size());
	std::copy(vec.begin(), vec.end(), copy.begin());
	std::sort(copy.begin(), copy.end());
	return copy;
}

int main() {
	for (size_t i = 0; i < arr_size; i++) {
		arr[i] = i;
		vec.push_back(i);
	}
	double total = 0;
	std::cout << "arr: " << bench([]() {
		swap_ends(arr, arr_size);
	}) << "ms\n";
	
	std::cout << "vec: " << bench([]() {
		swap_ends(vec);
	}) << "ms\n";

	int* bob = nullptr;
	std::cout << "sort c: " << bench([&]() {
		bob  = sort(arr, arr_size);
	}) << "ms\n";
	
	std::vector<int> sorted;
	std::cout << "sort c++: " << bench([&]() {
		sorted = sort(vec);
	}) << "ms\n";

	if (std::is_sorted(bob, bob + arr_size))
		std::cout << "Arr is sorted" << std::endl;
	if (std::is_sorted(sorted.begin(), sorted.end()))
		std::cout << "Vec is sorted" << std::endl;

	delete bob;
}
