#include <vector>
#include <iostream>

template<typename T>
void print(const std::vector<T>& elements) {
	std::cout << "{";

	for (auto it = elements.begin(); it != elements.end(); it++) {
		if (it == elements.begin()) {
			std::cout << *it;
		} else {
			std::cout << ", " << *it;
		}
	}
	std::cout << "}" << std::endl;
}

template<typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& elements) {
	o << "{";

	for (auto it = elements.begin(); it != elements.end(); it++) {
		if (it == elements.begin()) {
			o << *it;
		} else {
			o << ", " << *it;
		}
	}
	o << "}";

	return o;
}

int main() {
	auto t1 = std::vector<int>{ 1, 2, 3, 4 };
	auto t2 = std::vector<std::string>{ "haha", "hahaha", "hahahha" };
	print(t1);
	print(t2);
	std::cout << t1 << std::endl;
	std::cout << t2 << std::endl;
	std::cout << std::vector<int>{ 1,2,3 } << std::endl; // should still print "{1,2,3}"
	std::cout << std::vector<double>{ 2.7,3.14 } << std::endl; // should print "{2.7,3.14}"
	std::cout << std::vector<std::vector<std::string>>{ std::vector<std::string>{"hello", "template"}, std::vector<std::string>{"world"} } << std::endl;

}