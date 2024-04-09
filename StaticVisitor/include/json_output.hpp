#ifndef STATIC_VISITOR_JSON_OUTPUT_HPP
#define STATIC_VISITOR_JSON_OUTPUT_HPP

#include "meta.hpp"
#include <iostream>
#include <iomanip>

/** TODO: implement json_ostream adapter with json output operations
 * The goal is to exercise meta-programming and not have complete JSON (Unicode support is beyond the scope).
 */
struct json_ostream
{
    std::ostream& os;
};

template<typename T>
struct SomeWriter {
    static void write(json_ostream& j, const T& v);
};

template<BoolC B>
struct SomeWriter<B> {
    static void write(json_ostream& j, const B& v) {
        j.os << (v ? "true" : "false");
    }
};

template <NumberC N>
struct SomeWriter<N> {
    static void write(json_ostream& j, const N& v) { 
        j.os << v;
    }
};

template <StringC S>
struct SomeWriter<S> {
    static void write(json_ostream& j, const S& v) { 
        j.os << std::quoted(v);
    }
};

template <ContainerC C>
struct SomeWriter<C>
{
    static void write(json_ostream& j, const C& v) {
        auto it = std::cbegin(v);
        j.os << "[";
        if (it != std::cend(v)) {
            j.os << *it;
        }
        for (it++; it != std::cend(v); it++) {
            j.os << "," << *it;
        }
        j.os << "]";
    }
};

/** Visitor pattern support for writing JSON */
class json_writer_t
{
    json_ostream& _jos;
    bool _first = true;
public:
    json_writer_t(json_ostream& jos)
        : _jos(jos) {}

    template <typename Data>
    void visit(const std::string& name, const Data& value)
    {
        if (!_first) {
            _jos.os << ",";
        }
        _first = false;
        _jos.os << std::quoted(name) << ":";
        _jos << value;
    }
};

template <TupleC T>
struct SomeWriter<T>
{
    static void write(json_ostream& j, const T& v) {
        json_writer_t visitor(j);
        for (size_t i = 0; i < std::tuple_size_v<T>; i++) {
            visitor.visit(std::to_string(i + 1), v);
        }
    }
};

template <DataC<json_writer_t> D>
struct SomeWriter<D>
{
    static json_ostream& write(json_ostream& j, const D& data)
    {
        j.os << "{";
        json_writer_t writer(j);
        data.accept(writer);
        j.os << "}";
        return j;
    }
};

template <typename T>
json_ostream& operator<<(json_ostream& j, const T& v) {
    SomeWriter<T>::write(j, v);
    return j;
}

template <typename T>
json_ostream& operator<<(json_ostream&& j, T& value)
{
    return j << value;
}

#endif  // STATIC_VISITOR_JSON_OUTPUT_HPP
