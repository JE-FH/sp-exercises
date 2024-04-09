#include <iostream>

template<typename T>
class TD;

template <typename T>
void univ_ref(T&& d) {
	TD<T> a;
}


struct SomeClass {
	int x, y;
	SomeClass(const SomeClass&) {
		std::cout << "SomeClass(const SomeClass&) called" << std::endl;
	}
	SomeClass(SomeClass&&) {
		std::cout << "SomeClass(SomeClass&&) called" << std::endl;
	};
	SomeClass() = default;
};

int bitchFunction(SomeClass&& yes) {
	std::cout << "function called" << std::endl;
	return 0;
}

int main() {
	SomeClass d;
	univ_ref(d);
	return 1;
}