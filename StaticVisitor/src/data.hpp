#ifndef STATIC_VISITOR_DATA_HPP
#define STATIC_VISITOR_DATA_HPP

#include <string>
#include <vector>

/** custom class to test JSON input/output */
struct aggregate_t
{ /** public access is just for easy structured initialization in tests */
    bool b;
    int x;
    double y;
    std::string z;
    std::vector<int> w;
    /** visitor support with read-only access, e.g. for writing-out */
    template <typename Visitor>
    void accept(Visitor&& v) const
    {
        v.visit("b", b);
        v.visit("x", x);
        v.visit("y", y);
        v.visit("z", z);
        v.visit("w", w);
    }
    /** visitor support with full access, e.g. for reading-in */
    template <typename Visitor>
    void accept(Visitor&& v)
    {
        v.visit("b", b);
        v.visit("x", x);
        v.visit("y", y);
        v.visit("z", z);
        v.visit("w", w);
    }
    /** equality operator to support testing */
    friend bool operator==(const aggregate_t& a1, const aggregate_t& a2)
    {
        return (a1.b == a2.b) && (a1.x == a2.x) && (a1.y == a2.y) && (a1.z == a2.z) && (a1.w == a2.w);
    }
};

/** custom class to test JSON input/output with nesting */
struct nested_t
{
    std::string text;
    aggregate_t agg;
    /** visitor support with read-only access, e.g. for writing-out */
    template <typename Visitor>
    void accept(Visitor&& v) const
    {
        v.visit("text", text);
        v.visit("agg", agg);
    }
    /** visitor support with full access, e.g. for reading-in */
    template <typename Visitor>
    void accept(Visitor&& v)
    {
        v.visit("text", text);
        v.visit("agg", agg);
    }
    /** equality operator to support testing */
    friend bool operator==(const nested_t& n1, const nested_t& n2)
    {
        return (n1.text == n2.text) && (n1.agg == n2.agg);
    }
};

#endif  // STATIC_VISITOR_DATA_HPP
