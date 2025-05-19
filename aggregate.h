#pragma once

#include <vector>

namespace algo {
    template <typename T>
    T vectorSum(const std::vector<T>& vec) {
        T sum = 0;
        for (const auto& val : vec) {
            sum += val;
        }
        return sum;
    }

    template <typename T, typename Func>
    T aggregate(const std::vector<T>& vec, Func func) {
        T result = vec.empty() ? T() : vec[0];
        for (size_t i = 1; i < vec.size(); ++i) {
            result = func(result, vec[i]);
        }
        return result;
    }

    template <typename Container, typename Func, typename ResultT>
    ResultT aggregate(const Container& container, Func func, ResultT initial) {
        ResultT result = initial;
        
        for (const auto& val : container) {
            result = func(result, val);
        }
        return result;
    }

    template <typename T, std::size_t N, typename Func, typename ResultT>
    ResultT aggregate(const T (&arr)[N], Func func, ResultT init) {
        for (std::size_t i = 0; i < N; ++i) {
            init = func(init, arr[i]);
        }
        return init;
    }

    template <typename Iterator, typename Func, typename ResultT>
    ResultT aggregate_recursive_impl(Iterator begin, Iterator end, Func func, ResultT result) {
      if (begin == end)
           return result;
       return aggregate_recursive_impl(std::next(begin), end, func, func(result, *begin));
    }

    template <typename Container, typename Func, typename ResultT>
    ResultT aggregate_recursive(const Container& container, Func func, ResultT init) {
        return aggregate_recursive_impl(std::begin(container), std::end(container), func, init);
    }

    template <typename T, std::size_t N, typename Func, typename ResultT>
    ResultT aggregate_recursive(const T (&arr)[N], Func func, ResultT init) {
        return aggregate_recursive_impl(arr, arr + N, func, init);
    }

} // namespace algo