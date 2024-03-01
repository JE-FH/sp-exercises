/// Created by Marius Mikucionis <marius@cs.aau.dk>

/** Unit tests for number_series */

#include "number_series.hpp"

#include <doctest/doctest.h>

using namespace data_series;

/// number_series class
TEST_CASE("Maintain minimum and maximum values")
{
    auto ns = number_series{};
    // TODO: uncomment one test at a time, implement it and check it
    ns.add_value(10);
    CHECK(ns.get_min() == 10);
    CHECK(ns.get_max() == 10);
    SUBCASE("Add greater")
    {
        ns.add_value(15);
        CHECK(ns.get_min() == 10);
        CHECK(ns.get_max() == 15);
        ns.add_value(17);
        CHECK(ns.get_min() == 10);
        CHECK(ns.get_max() == 17);
        ns.add_value(13);
        CHECK(ns.get_min() == 10);
        CHECK(ns.get_max() == 17);
    }
    SUBCASE("Add lesser")
    {
        ns.add_value(5);
        CHECK(ns.get_min() == 5);
        CHECK(ns.get_max() == 10);
        ns.add_value(3);
        CHECK(ns.get_min() == 3);
        CHECK(ns.get_max() == 10);
        ns.add_value(7);
        CHECK(ns.get_min() == 3);
        CHECK(ns.get_max() == 10);
    }
     
}

// TODO: uncomment one test at a time, then implement it
TEST_CASE("Special members: ctors, dtor, assignment")
{
    const auto ns1 = number_series{11, 3, 7};
    CHECK(ns1.size() == 3);
    CHECK(ns1.get_min() == 3);
    CHECK(ns1.get_max() == 11);
    auto ns2 = number_series{27, 20, 33, 23};
    CHECK(ns2.size() == 4);
    CHECK(ns2.get_min() == 20);
    CHECK(ns2.get_max() == 33);
    auto ns3 = ns1;
    CHECK(ns3.size() == 3);
    CHECK(ns3.get_min() == 3);
    CHECK(ns3.get_max() == 11);
    ns2 = std::move(ns3);
    CHECK(ns2.size() == 3);
    CHECK(ns2.get_min() == 3);
    CHECK(ns2.get_max() == 11);
    CHECK(ns3.size() == 0); // your implementation may differ
}

// TODO: uncomment one test at a time, then implement it
TEST_CASE("Static factory method")
{
    auto ns = number_series::make_random(4);
    CHECK(ns.size() == 4);
}


// TODO: uncomment one test at a time, then implement it
TEST_CASE("operator+ and operator+= over number series")
{
    auto ns1 = number_series::make_random(2);
    CHECK(ns1.size() == 2);
    auto ns2 = number_series::make_random(3);
    CHECK(ns2.size() == 3);
    auto ns3 = ns1 + ns2;
    CHECK(ns1.size() == 2);
    CHECK(ns2.size() == 3);
    CHECK(ns3.size() == 3);
    ns2.add_value(10);
    CHECK(ns2.size() == 4);
    (ns3 += ns1) += ns2;
    CHECK(ns1.size() == 2);
    CHECK(ns2.size() == 4);
    CHECK(ns3.size() == 4);
}


// TODO: uncomment one test at a time, then implement it
TEST_CASE("operator< using amplitudes")
{
    auto ns1 = number_series{6, 3, 9};
    CHECK(ns1.amplitude() == 6);
    auto ns2 = number_series{24, 21, 22};
    CHECK(ns2.amplitude() == 3);
    CHECK(ns2 < ns1);
}


/// number_series_wrap class
// TODO: uncomment one test at a time, then implement it
TEST_CASE("Maintain minimum and maximum values")
{
    auto ns = number_series_wrap{};
    ns.add_value(10);
    CHECK(ns.get_min() == 10);
    CHECK(ns.get_max() == 10);
    SUBCASE("Add greater")
    {
        ns.add_value(15);
        CHECK(ns.get_min() == 10);
        CHECK(ns.get_max() == 15);
        ns.add_value(17);
        CHECK(ns.get_min() == 10);
        CHECK(ns.get_max() == 17);
        ns.add_value(13);
        CHECK(ns.get_min() == 10);
        CHECK(ns.get_max() == 17);
    }
    SUBCASE("Add lesser")
    {
        ns.add_value(5);
        CHECK(ns.get_min() == 5);
        CHECK(ns.get_max() == 10);
        ns.add_value(3);
        CHECK(ns.get_min() == 3);
        CHECK(ns.get_max() == 10);
        ns.add_value(7);
        CHECK(ns.get_min() == 3);
        CHECK(ns.get_max() == 10);
    }
}

// TODO: uncomment one test at a time, then implement it
TEST_CASE("Special members: ctors, dtor, assignment")
{
    const auto ns1 = number_series_wrap{11, 3, 7};
    CHECK(ns1.size() == 3);
    CHECK(ns1.get_min() == 3);
    CHECK(ns1.get_max() == 11);
    auto ns2 = number_series_wrap{27, 20, 33, 23};
    CHECK(ns2.size() == 4);
    CHECK(ns2.get_min() == 20);
    CHECK(ns2.get_max() == 33);
    auto ns3 = ns1;
    CHECK(ns3.size() == 3);
    CHECK(ns3.get_min() == 3);
    CHECK(ns3.get_max() == 11);
    ns2 = std::move(ns3);
    CHECK(ns2.size() == 3);
    CHECK(ns2.get_min() == 3);
    CHECK(ns2.get_max() == 11);
    CHECK(ns3.size() == 0); // your implementation may differ
}

// TODO: uncomment one test at a time, then implement it
TEST_CASE("Class should have a static factory method")
{
    auto ns = number_series::make_random(4);
    CHECK(ns.size() == 4);
}

// TODO: uncomment one test at a time, then implement it
TEST_CASE("operator+ and operator+= over number series")
{
    auto ns1 = number_series_wrap::make_random(2);
    CHECK(ns1.size() == 2);
    auto ns2 = number_series_wrap::make_random(3);
    CHECK(ns2.size() == 3);
    auto ns3 = ns1 + ns2;
    CHECK(ns1.size() == 2);
    CHECK(ns2.size() == 3);
    CHECK(ns3.size() == 3);
    ns2.add_value(10);
    CHECK(ns2.size() == 4);
    (ns3 += ns1) += ns2;
    CHECK(ns1.size() == 2);
    CHECK(ns2.size() == 4);
    CHECK(ns3.size() == 4);
}


// TODO: uncomment one test at a time, then implement it
TEST_CASE("operator< using amplitudes")
{
    auto ns1 = number_series_wrap{6, 3, 9};
    CHECK(ns1.amplitude() == 6);
    auto ns2 = number_series_wrap{24, 21, 22};
    CHECK(ns2.amplitude() == 3);
    CHECK(ns2 < ns1);
}
