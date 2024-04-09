#include "json_output.hpp"
#include "meta.hpp"
#include "data.hpp"

#include <doctest/doctest.h>

#include <sstream>
#include <vector>

using namespace std::string_literals;

/** Output operator just for friendly output in tests: */
std::ostream& operator<<(std::ostream& os, const aggregate_t& agg)
{
    json_ostream { os } << agg;
    return os;
}

/** Output operator just for friendly output in tests: */
std::ostream& operator<<(std::ostream& os, const nested_t& nested)
{
    json_ostream { os } << nested;
    return os;
}

TEST_CASE("JSON output")
{
    auto os = std::ostringstream{};
    auto jos = json_ostream{os};
    SUBCASE("boolean: lvalue true")
    {
        auto v = true;
        jos << v;
        CHECK(os.str() == "true");
    }
    SUBCASE("boolean: lvalue false")
    {
        auto v = false;
        jos << v;
        CHECK(os.str() == "false");
    }
    SUBCASE("boolean: rvalue")
    {
        jos << true;
        CHECK(os.str() == "true");
    }
    SUBCASE("integer")
    {
        jos << 7;
        CHECK(os.str() == "7");
    }
    SUBCASE("double")
    {
        jos << 3.14;
        CHECK(os.str() == "3.14");
    }
    SUBCASE("c-string")
    {
        jos << "hello";
        CHECK(os.str() == "\"hello\"");
    }
    SUBCASE("cpp-string")
    {
        jos << "hello"s;
        CHECK(os.str() == "\"hello\"");
    }
    SUBCASE("container")
    {
        auto v = std::vector{3, 7, 11};
        jos << v;
        CHECK(os.str() == "[3,7,11]");
    }
    static_assert(accepts_v<const aggregate_t&, json_writer_t>, "const aggregate should accept writer");
    static_assert(accepts_v<const nested_t&, json_writer_t>, "const nested should accept writer");
    // TODO: uncomment the following extra tests for meta library and fix accepts_v implementation
    static_assert(!accepts_v<json_writer_t, aggregate_t>, "writer should not accept aggregate");
    static_assert(!accepts_v<int, double>, "int should not accept double");
    SUBCASE("aggregate")
    {
        auto v = aggregate_t{true, 3, 3.14, "hello", {7, 11}};
        jos << v;
        CHECK(os.str() == R"({"b":true,"x":3,"y":3.14,"z":"hello","w":[7,11]})");
    }
    SUBCASE("nested")
    {
        const auto v = nested_t{"complicated", {true, 3, 3.14, "hello", {7, 11}}};
        jos << v;
        CHECK(os.str() == R"({"text":"complicated","agg":{"b":true,"x":3,"y":3.14,"z":"hello","w":[7,11]}})");
    }
}
