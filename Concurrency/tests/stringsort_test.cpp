#include "stringsort.hpp"

#include <doctest/doctest.h>

#include <algorithm>  // std::sort
#include <sstream>
#include <iostream>
#include <cstring>

TEST_CASE("C++ STL sort of IDs")
{
    auto ids = gen_ids(6);
    std::sort(std::begin(ids), std::end(ids));
    auto ss = std::stringstream{};
    for (auto&& s : ids)
        ss << s << ' ';
    CHECK(ss.str() == "ID0 ID1 ID2 id0 id1 id2 ");
}

TEST_CASE("standard C sort of IDs")
{
    const auto size = 6u;
    auto ids = gen_cids(size);
    std::qsort(ids, size, sizeof(char*), [](const void* a, const void* b) -> int {
        auto x = static_cast<char* const*>(a);
        auto y = static_cast<char* const*>(b);
        return strcmp(*x, *y);
    });
    auto ss = std::stringstream{};
    for (auto i = 0u; i < size; ++i) {
        ss << ids[i] << ' ';
        free(ids[i]);
    }
    free(ids);
    CHECK(ss.str() == "ID0 ID1 ID2 id0 id1 id2 ");
}
