/**
 * Lambda inheritance with std::variant and std::visit: https://youtu.be/3wm5QzdddYc
 * In compiler explorer: https://godbolt.org/z/dLHTWZ
 */
#include <variant>
#include <array>
#include <iostream>

template <typename...Fns>
struct Visitor: Fns...
{
	using Fns::operator()...; // import all the call operators
	template <typename... Args> // ctor with perfect forwarding
	Visitor(Args&&... args): Fns{std::forward<Args>(args)}... {}
};

template <typename...Args>
Visitor(Args&&...) -> Visitor<std::remove_cvref_t<Args>...>;

template <typename...Args> // CTAD guide workaround for GCC
auto overload(Args&&... args) {
	return Visitor<std::decay_t<Args>...>(std::forward<Args>(args)...);
}

int main()
{
    using std::cout;
    using namespace std::string_literals;

    using Data = std::variant<int, double, std::string>;  // multiple types
    auto data = std::array<Data, 3>{3, 3.14, "hello"s};   // heterogeneous array

    auto visitor = [](const auto& d) { cout << d << '\n'; };  // generic
    for (auto& item : data)
        std::visit(visitor, item);

    auto visitor2 = Visitor(  // rvalue-references, move
        [](int i) { cout << "int: " << i << '\n'; }, [](double d) { cout << "double: " << d << '\n'; },
        [](const std::string& s) { cout << "string: " << s << '\n'; });
    for (auto& item : data)
        std::visit(visitor2, item);

    auto fi = [](int i) { cout << "int: " << i << '\n'; };
    auto fd = [](double d) { cout << "double: " << d << '\n'; };
    auto fs = [](const std::string& s) { cout << "string: " << s << '\n'; };

    auto visitor3 = Visitor(fi, fd, fs);  // lvalue-references
    for (auto& item : data)
        std::visit(visitor3, item);
}