/// Created by Marius Mikucionis <marius@cs.aau.dk>
/**
 * Definitions of number_series and number_series_wrap classes.
 */

#ifndef INCLUDE_NUMBER_SERIES_H
#define INCLUDE_NUMBER_SERIES_H

#include <vector>
#include <limits>
#include <memory>
#include <iostream>

namespace data_series
{
    class number_series
    {
        std::vector<int> _data;
        int _min;
        int _max;

    public:
        number_series();
        number_series(std::initializer_list<int> s);

        size_t size() const noexcept;

        int get_min() const noexcept;

        int get_max() const noexcept;

        void add_value(int value);

        static number_series make_random(size_t length);

        number_series& operator+=(const number_series& other);

        int amplitude() const noexcept;

        friend number_series operator+(const number_series& lhs, const number_series& rhs);

        friend bool operator<(const number_series& lhs, const number_series& rhs);
    };

    class number_series_wrap
    {
        std::unique_ptr<number_series> _ns;
        number_series_wrap(number_series ns);
    public:
        number_series_wrap();
        number_series_wrap(std::initializer_list<int> s);
        number_series_wrap(const number_series_wrap& other);
        number_series_wrap(number_series_wrap&& other) noexcept;
        number_series_wrap& operator=(const number_series_wrap& other);
        number_series_wrap& operator=(number_series_wrap&& other) noexcept;

        size_t size() const noexcept;

        int get_min() const noexcept;

        int get_max() const noexcept;

        void add_value(int value);

        int amplitude() const noexcept;

        number_series_wrap& operator+=(const number_series_wrap& other);

        friend number_series_wrap operator+(const number_series_wrap& lhs, const number_series_wrap& rhs);

        friend bool operator<(const number_series_wrap& lhs, const number_series_wrap& rhs);

        static number_series_wrap make_random(size_t length);

        // TODO: add the same interface as in number_series which forwards all the calls
    };

}  // namespace data_series

#endif  // INCLUDE_NUMBER_SERIES_H
