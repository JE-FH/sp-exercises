/// Created by Marius Mikucionis <marius@cs.aau.dk>
/**
 * Definitions/implementation of some number_series methods
 */

#include "number_series.hpp"
#include <random>
#include <memory>

namespace data_series
{
    number_series_wrap::number_series_wrap() {
        _ns = std::make_unique<number_series>();
    }

    number_series_wrap::number_series_wrap(std::initializer_list<int> s) {
        _ns = std::make_unique<number_series>(std::move(s));
    }

    number_series_wrap::number_series_wrap(const number_series_wrap& other) {
        _ns = std::make_unique<number_series>(*other._ns);
    }

    number_series_wrap::number_series_wrap(number_series_wrap&& other) noexcept {
        _ns = std::move(other._ns);
        other._ns = std::make_unique<number_series>();
    }

    number_series_wrap& number_series_wrap::operator=(const number_series_wrap& other)
    {
        _ns = std::make_unique<number_series>(*other._ns);
        return *this;
    }

    number_series_wrap& number_series_wrap::operator=(number_series_wrap&& other) noexcept
    {
        _ns = std::move(other._ns);
        other._ns = std::make_unique<number_series>();
        return *this;
    }

    size_t number_series_wrap::size() const noexcept {
        return _ns->size();
    }

    int number_series_wrap::get_min() const noexcept {
        return _ns->get_min();
    }

    int number_series_wrap::get_max() const noexcept {
        return _ns->get_max();
    }

    void number_series_wrap::add_value(int value) {
        _ns->add_value(value);
    }

    int number_series_wrap::amplitude() const noexcept {
        return _ns->amplitude();
    }

    number_series_wrap& number_series_wrap::operator+=(const number_series_wrap& other)
    {
        *_ns += *other._ns;
        return *this;
    }

    number_series_wrap number_series_wrap::make_random(size_t length){
        return number_series_wrap(number_series::make_random(length));
    }

    number_series_wrap::number_series_wrap(number_series ns) {
        _ns = std::make_unique<number_series>(std::move(ns));
    }

    number_series::number_series() {
        _min = INT_MAX;
        _max = INT_MIN;
    }

    number_series::number_series(std::initializer_list<int> s) {
        _min = INT_MAX;
        _max = INT_MIN;
        _data.reserve(s.size());
        for (auto n : s) {
            add_value(n);
        }
    }

    size_t number_series::size() const noexcept { 
        return _data.size();
    }

    int number_series::get_min() const noexcept { 
        return _min;
    }

    int number_series::get_max() const noexcept {
        return _max;
    }

    void number_series::add_value(int value)
    {
        _data.push_back(value);
        _min = std::min(value, _min);
        _max = std::max(value, _max);
    }

    number_series number_series::make_random(size_t length) { 
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(INT_MIN, INT_MAX);
        number_series series;

        series._data.reserve(length);

        for (size_t i = 0; i < length; i++) {
            series.add_value(distrib(gen));
        }

        return series;
    }
    
    number_series& number_series::operator+=(const number_series& other)
    {
        auto tit = _data.begin(); 
        auto oit = other._data.begin();
        for (; tit != _data.end() && oit != other._data.end(); tit++, oit++) {
            *tit += *oit;
        }
        for (; oit != other._data.end(); oit++) {
            add_value(*oit);
        }
        return *this;
    }

    int number_series::amplitude() const noexcept {
        return (_max - _min);
    }

    number_series operator+(const number_series& lhs, const number_series& rhs) { 
        number_series rv = lhs;
        rv += rhs;
        return rv;
    }

    bool operator<(const number_series& lhs, const number_series& rhs) {
        return lhs.amplitude() < rhs.amplitude();
    }

    number_series_wrap operator+(const number_series_wrap& lhs, const number_series_wrap& rhs)
    {
        return number_series_wrap(*lhs._ns + *rhs._ns);
    }

    bool operator<(const number_series_wrap& lhs, const number_series_wrap& rhs) {
        return *lhs._ns < *rhs._ns;
    }

}  // namespace data_series
