#ifndef STATIC_VISITOR_JSON_INPUT_HPP
#define STATIC_VISITOR_JSON_INPUT_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "meta.hpp"

/** TODO: implement json_istream adapter with json input operations
 * The goal is to exercise meta-programming and not have complete JSON (Unicode support is beyond the scope).
 * Parsing should follow the type structure rather than the content of the input stream.
 * Visitor parsing may depend on the order of fields, which is OK for this exercise.
 */

struct json_istream
{
    std::istream& is;
};

/** Visitor pattern support for reading JSON */
class json_reader_t
{
    json_istream& _j;
    bool _first = true;
public:
    json_reader_t(json_istream& j)
        : _j(j) { }
    
    template <typename Data>
    void visit(const std::string& name, Data& value)
    {
        if (!_first) {
            if (_j.is.get() != ',') {
                throw std::exception("Malformed json, expected ,");
            }
        }
        _first = false;
        std::string s;
        _j.is >> std::quoted(s);
        if (s != name) {
            throw std::exception("Unexpected field ordering");
        }
        if (_j.is.get() != ':') {
            throw std::exception("Malformed json, expected :");
        }
        _j >> value;
    }
};

template<typename T>
struct SomeReader {
    static json_istream& read(json_istream& j, T& out);
};

template <BoolC B>
struct SomeReader<B>
{
    static json_istream& read(json_istream& j, B& out)
    {
        char buf[5];
        j.is.get(buf, 5);
        if (strcmp(buf, "true") == 0) {
            out = true;
            return j;
        } else if (strcmp(buf, "fals") == 0) {
            if (j.is.get() == 'e') {
                out = false;
                return j;
            }
        }
        throw std::exception("Expected false or true");
    }
};

template<NumberC N>
struct SomeReader<N>
{
    static json_istream& read(json_istream& j, N& out) {
        j.is >> out;
        return j;
    }
};

template <StringC S>
struct SomeReader<S>
{
    static json_istream& read(json_istream& j, S& out) {
        j.is >> std::quoted(out);
        return j;
    }
};

template <WriteableContainer W>
struct SomeReader<W>
{
    static json_istream& read(json_istream& j, W& out) {
        if (j.is.get() != '[') {
            throw std::exception("Malformed json, expected [");
        }
        while (j.is.peek() != ']') {
            j >> out.emplace_back();
            if (j.is.peek() == ',') {
                j.is.get();
            } else if ( j.is.peek() != ']') {
                throw std::exception("Malformed json, expected ] or ,");
            }
        }
        j.is.get();
        return j;
    }
};

template<DataC<json_reader_t> D>
struct SomeReader<D>
{
    static json_istream& read(json_istream& j, D& out)
    {
        if (j.is.get() != '{') {
            throw std::exception("Malformed json, expected {");
        }
        json_reader_t reader(j);
        out.accept(reader);
        if (j.is.get() != '}') {
            throw std::exception("Malformed json, expected }");
        }
        return j;
    }
};

template <typename T>
json_istream& operator>>(json_istream& j, T& out)
{
    return SomeReader<T>::read(j, out);
}

/** Helper for rvalue reference */
template <typename T>
json_istream& operator>>(json_istream&& j, T& value)
{
    return j >> value;
}


#endif  // STATIC_VISITOR_JSON_INPUT_HPP
