#include "digits.hpp"
#include <doctest/doctest.h>
#include <limits>
#include <cinttypes>

TEST_CASE("digits10_div")
{
    CHECK(digits10_div(0) == 1);
    CHECK(digits10_div(1) == 1);
    CHECK(digits10_div(9) == 1);
    CHECK(digits10_div(10) == 2);
    CHECK(digits10_div(99) == 2);
    CHECK(digits10_div(100) == 3);
    CHECK(digits10_div(101) == 3);
    CHECK(digits10_div(548548) == 6);
    CHECK(digits10_div(std::numeric_limits<int32_t>::max()) == std::numeric_limits<int32_t>::digits10 + 1);
    CHECK(digits10_div(std::numeric_limits<uint32_t>::max()) == std::numeric_limits<uint32_t>::digits10 + 1);
    CHECK(digits10_div(std::numeric_limits<uint64_t>::max()) == std::numeric_limits<uint64_t>::digits10 + 1);
    CHECK(digits10_div(-1) == 1);
    CHECK(digits10_div(-9) == 1);
    CHECK(digits10_div(-10) == 2);
    CHECK(digits10_div(-99) == 2);
    CHECK(digits10_div(-100) == 3);
    CHECK(digits10_div(-101) == 3);
    CHECK(digits10_div(-548548) == 6);
    CHECK(digits10_div(std::numeric_limits<int32_t>::min()) == std::numeric_limits<int32_t>::digits10 + 1);
    CHECK(digits10_div(std::numeric_limits<int64_t>::min()) == std::numeric_limits<int64_t>::digits10 + 1);
}

TEST_CASE("digits10_log")
{
    CHECK(digits10_log(0) == 1);
    CHECK(digits10_log(1) == 1);
    CHECK(digits10_log(9) == 1);
    CHECK(digits10_log(10) == 2);
    CHECK(digits10_log(99) == 2);
    CHECK(digits10_log(100) == 3);
    CHECK(digits10_log(101) == 3);
    CHECK(digits10_log(548548) == 6);
    CHECK(digits10_log(std::numeric_limits<int32_t>::max()) == std::numeric_limits<int32_t>::digits10 + 1);
    CHECK(digits10_log(std::numeric_limits<uint32_t>::max()) == std::numeric_limits<uint32_t>::digits10 + 1);
    CHECK(digits10_log(std::numeric_limits<uint64_t>::max()) == std::numeric_limits<uint64_t>::digits10 + 1);
    CHECK(digits10_log(-1) == 1);
    CHECK(digits10_log(-9) == 1);
    CHECK(digits10_log(-10) == 2);
    CHECK(digits10_log(-99) == 2);
    CHECK(digits10_log(-100) == 3);
    CHECK(digits10_log(-101) == 3);
    CHECK(digits10_log(-548548) == 6);
    CHECK(digits10_log(std::numeric_limits<int32_t>::min()) == std::numeric_limits<int32_t>::digits10 + 1);
    CHECK(digits10_log(std::numeric_limits<int64_t>::min()) == std::numeric_limits<int64_t>::digits10 + 1);
}

TEST_CASE("digits10_mul")
{
    CHECK(digits10_mul(0) == 1);
    CHECK(digits10_mul(1) == 1);
    CHECK(digits10_mul(9) == 1);
    CHECK(digits10_mul(10) == 2);
    CHECK(digits10_mul(99) == 2);
    CHECK(digits10_mul(100) == 3);
    CHECK(digits10_mul(101) == 3);
    CHECK(digits10_mul(548548) == 6);
    CHECK(digits10_mul(std::numeric_limits<int32_t>::max()) == std::numeric_limits<int32_t>::digits10 + 1);
    CHECK(digits10_mul(std::numeric_limits<uint32_t>::max()) == std::numeric_limits<uint32_t>::digits10 + 1);
    CHECK(digits10_mul(std::numeric_limits<uint64_t>::max()) == std::numeric_limits<uint64_t>::digits10 + 1);
    CHECK(digits10_mul(-1) == 1);
    CHECK(digits10_mul(-9) == 1);
    CHECK(digits10_mul(-10) == 2);
    CHECK(digits10_mul(-99) == 2);
    CHECK(digits10_mul(-100) == 3);
    CHECK(digits10_mul(-101) == 3);
    CHECK(digits10_mul(-548548) == 6);
    CHECK(digits10_mul(std::numeric_limits<int32_t>::min()) == std::numeric_limits<int32_t>::digits10 + 1);
    CHECK(digits10_mul(std::numeric_limits<int64_t>::min()) == std::numeric_limits<int64_t>::digits10 + 1);
}

TEST_CASE("digits10_div2")
{
    CHECK(digits10_div2(0) == 1);
    CHECK(digits10_div2(1) == 1);
    CHECK(digits10_div2(9) == 1);
    CHECK(digits10_div2(10) == 2);
    CHECK(digits10_div2(99) == 2);
    CHECK(digits10_div2(100) == 3);
    CHECK(digits10_div2(101) == 3);
    CHECK(digits10_div2(548548) == 6);
    CHECK(digits10_div2(std::numeric_limits<int32_t>::max()) == std::numeric_limits<int32_t>::digits10 + 1);
    CHECK(digits10_div2(std::numeric_limits<uint32_t>::max()) == std::numeric_limits<uint32_t>::digits10 + 1);
    CHECK(digits10_div2(std::numeric_limits<uint64_t>::max()) == std::numeric_limits<uint64_t>::digits10 + 1);
    CHECK(digits10_div2(-1) == 1);
    CHECK(digits10_div2(-9) == 1);
    CHECK(digits10_div2(-10) == 2);
    CHECK(digits10_div2(-99) == 2);
    CHECK(digits10_div2(-100) == 3);
    CHECK(digits10_div2(-101) == 3);
    CHECK(digits10_div2(-548548) == 6);
    CHECK(digits10_div2(std::numeric_limits<int32_t>::min()) == std::numeric_limits<int32_t>::digits10 + 1);
    CHECK(digits10_div2(std::numeric_limits<int64_t>::min()) == std::numeric_limits<int64_t>::digits10 + 1);
}

TEST_CASE("digits10_div3")
{
    CHECK(digits10_div3(0) == 1);
    CHECK(digits10_div3(1) == 1);
    CHECK(digits10_div3(9) == 1);
    CHECK(digits10_div3(10) == 2);
    CHECK(digits10_div3(99) == 2);
    CHECK(digits10_div3(100) == 3);
    CHECK(digits10_div3(101) == 3);
    CHECK(digits10_div3(548548) == 6);
    CHECK(digits10_div3(std::numeric_limits<int32_t>::max()) == std::numeric_limits<int32_t>::digits10 + 1);
    CHECK(digits10_div3(std::numeric_limits<uint32_t>::max()) == std::numeric_limits<uint32_t>::digits10 + 1);
    CHECK(digits10_div3(std::numeric_limits<uint64_t>::max()) == std::numeric_limits<uint64_t>::digits10 + 1);
    CHECK(digits10_div3(-1) == 1);
    CHECK(digits10_div3(-9) == 1);
    CHECK(digits10_div3(-10) == 2);
    CHECK(digits10_div3(-99) == 2);
    CHECK(digits10_div3(-100) == 3);
    CHECK(digits10_div3(-101) == 3);
    CHECK(digits10_div3(-548548) == 6);
    CHECK(digits10_div3(std::numeric_limits<int32_t>::min()) == std::numeric_limits<int32_t>::digits10 + 1);
    CHECK(digits10_div3(std::numeric_limits<int64_t>::min()) == std::numeric_limits<int64_t>::digits10 + 1);
}

TEST_CASE("digits10_div4")
{
    CHECK(digits10_div4(0) == 1);
    CHECK(digits10_div4(1) == 1);
    CHECK(digits10_div4(9) == 1);
    CHECK(digits10_div4(10) == 2);
    CHECK(digits10_div4(99) == 2);
    CHECK(digits10_div4(100) == 3);
    CHECK(digits10_div4(101) == 3);
    CHECK(digits10_div4(548548) == 6);
    CHECK(digits10_div4(std::numeric_limits<int32_t>::max()) == std::numeric_limits<int32_t>::digits10 + 1);
    CHECK(digits10_div4(std::numeric_limits<uint32_t>::max()) == std::numeric_limits<uint32_t>::digits10 + 1);
    CHECK(digits10_div4(std::numeric_limits<uint64_t>::max()) == std::numeric_limits<uint64_t>::digits10 + 1);
    CHECK(digits10_div4(-1) == 1);
    CHECK(digits10_div4(-9) == 1);
    CHECK(digits10_div4(-10) == 2);
    CHECK(digits10_div4(-99) == 2);
    CHECK(digits10_div4(-100) == 3);
    CHECK(digits10_div4(-101) == 3);
    CHECK(digits10_div4(-548548) == 6);
    CHECK(digits10_div4(std::numeric_limits<int32_t>::min()) == std::numeric_limits<int32_t>::digits10 + 1);
    CHECK(digits10_div4(std::numeric_limits<int64_t>::min()) == std::numeric_limits<int64_t>::digits10 + 1);
}

TEST_CASE("digits10_div5")
{
    CHECK(digits10_div5(0) == 1);
    CHECK(digits10_div5(1) == 1);
    CHECK(digits10_div5(9) == 1);
    CHECK(digits10_div5(10) == 2);
    CHECK(digits10_div5(99) == 2);
    CHECK(digits10_div5(100) == 3);
    CHECK(digits10_div5(101) == 3);
    CHECK(digits10_div5(548548) == 6);
    CHECK(digits10_div5(std::numeric_limits<int32_t>::max()) == std::numeric_limits<int32_t>::digits10 + 1);
    CHECK(digits10_div5(std::numeric_limits<uint32_t>::max()) == std::numeric_limits<uint32_t>::digits10 + 1);
    CHECK(digits10_div5(std::numeric_limits<uint64_t>::max()) == std::numeric_limits<uint64_t>::digits10 + 1);
    CHECK(digits10_div5(-1) == 1);
    CHECK(digits10_div5(-9) == 1);
    CHECK(digits10_div5(-10) == 2);
    CHECK(digits10_div5(-99) == 2);
    CHECK(digits10_div5(-100) == 3);
    CHECK(digits10_div5(-101) == 3);
    CHECK(digits10_div5(-548548) == 6);
    CHECK(digits10_div5(std::numeric_limits<int32_t>::min()) == std::numeric_limits<int32_t>::digits10 + 1);
    CHECK(digits10_div5(std::numeric_limits<int64_t>::min()) == std::numeric_limits<int64_t>::digits10 + 1);
}

TEST_CASE("digits10_divn")
{
    CHECK(digits10_divn(0) == 1);
    CHECK(digits10_divn(1) == 1);
    CHECK(digits10_divn(9) == 1);
    CHECK(digits10_divn(10) == 2);
    CHECK(digits10_divn(99) == 2);
    CHECK(digits10_divn(100) == 3);
    CHECK(digits10_divn(101) == 3);
    CHECK(digits10_divn(548548) == 6);
    CHECK(digits10_divn(std::numeric_limits<int32_t>::max()) == std::numeric_limits<int32_t>::digits10 + 1);
    CHECK(digits10_divn(std::numeric_limits<uint32_t>::max()) == std::numeric_limits<uint32_t>::digits10 + 1);
    CHECK(digits10_divn(std::numeric_limits<uint64_t>::max()) == std::numeric_limits<uint64_t>::digits10 + 1);
    CHECK(digits10_divn(-1) == 1);
    CHECK(digits10_divn(-9) == 1);
    CHECK(digits10_divn(-10) == 2);
    CHECK(digits10_divn(-99) == 2);
    CHECK(digits10_divn(-100) == 3);
    CHECK(digits10_divn(-101) == 3);
    CHECK(digits10_divn(-548548) == 6);
    CHECK(digits10_divn(std::numeric_limits<int32_t>::min()) == std::numeric_limits<int32_t>::digits10 + 1);
    CHECK(digits10_divn(std::numeric_limits<int64_t>::min()) == std::numeric_limits<int64_t>::digits10 + 1);
}

TEST_CASE("digits10_loop")
{
    CHECK(digits10_loop(0) == 1);
    CHECK(digits10_loop(1) == 1);
    CHECK(digits10_loop(9) == 1);
    CHECK(digits10_loop(10) == 2);
    CHECK(digits10_loop(99) == 2);
    CHECK(digits10_loop(100) == 3);
    CHECK(digits10_loop(101) == 3);
    CHECK(digits10_loop(548548) == 6);
    CHECK(digits10_loop(std::numeric_limits<int32_t>::max()) == std::numeric_limits<int32_t>::digits10 + 1);
    CHECK(digits10_loop(std::numeric_limits<uint32_t>::max()) == std::numeric_limits<uint32_t>::digits10 + 1);
    CHECK(digits10_loop(std::numeric_limits<uint64_t>::max()) == std::numeric_limits<uint64_t>::digits10 + 1);
    CHECK(digits10_loop(-1) == 1);
    CHECK(digits10_loop(-9) == 1);
    CHECK(digits10_loop(-10) == 2);
    CHECK(digits10_loop(-99) == 2);
    CHECK(digits10_loop(-100) == 3);
    CHECK(digits10_loop(-101) == 3);
    CHECK(digits10_loop(-548548) == 6);
    CHECK(digits10_loop(std::numeric_limits<int32_t>::min()) == std::numeric_limits<int32_t>::digits10 + 1);
    CHECK(digits10_loop(std::numeric_limits<int64_t>::min()) == std::numeric_limits<int64_t>::digits10 + 1);
}
