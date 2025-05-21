#pragma once

#include <vector>
#include <stdexcept>

namespace algo {
    template <typename T>
    T vectorSum(const std::vector<T>& vec) {
        T sum = 0;
        for (const auto& val : vec) {
            sum += val;
        }
        return sum;
    }

    // Use function with const reference and non const
    // Solution: Use universal reference to allow both lvalue and rvalue references
    template <typename T, typename Func>
    T aggregate(const std::vector<T>& vec, Func&& func) {
        if (vec.empty())
            throw std::invalid_argument("Vector must not be empty");

        T result = vec.at(0);
 
        for (size_t i = 1; i < vec.size(); ++i) {
            // Use std::forward to preserve the value category of func
            // This allows the function to be called with either lvalue or rvalue
            result = std::forward<Func>(func)(result, vec.at(i));
        }
        return result;
    }

    template <typename Container, typename Func, typename ResultT>
    auto aggregate(const Container& container, Func&& func, ResultT&& initial)
    // Use std::decay to remove references and cv-qualifiers
        -> typename std::decay<ResultT>::type {
        if (std::begin(container) == std::end(container))
            throw std::invalid_argument("Container must not be empty");

        auto result = std::forward<ResultT>(initial);
        
        for (const auto& val : container) {
            result = std::forward<Func>(func)(result, val);
        }
        return result;
    }

/*     template <typename T, std::size_t N, typename Func, typename ResultT>
    ResultT aggregate(const T (&arr)[N], Func func, ResultT init) {
        for (std::size_t i = 0; i < N; ++i) {
            init = func(init, arr[i]);
        }
        return init;
    } */

    template <typename Iterator, typename Func, typename ResultT>
    ResultT aggregate_recursive_impl(Iterator begin, Iterator end, Func func, ResultT result) {
      if (begin == end)
           return result;
       return aggregate_recursive_impl(std::next(begin), end, func, func(result, *begin));
    }

    template <typename Container, typename Func, typename ResultT>
    auto aggregate_recursive(const Container& container, Func&& func, ResultT&& init)
        -> typename std::decay<ResultT>::type {
        if (std::begin(container) == std::end(container))
            throw std::invalid_argument("Container must not be empty");

        return aggregate_recursive_impl(std::begin(container), std::end(container),
            std::forward<Func>(func), std::forward<ResultT>(init));
    }
    
    template <typename Container, typename Func>
    auto aggregate_recursive(const Container& container, Func&& func)
        -> typename std::decay<decltype(*std::begin(container))>::type
    {
       auto it = std::begin(container);
       auto end = std::end(container);

       if (it == end)
           throw std::invalid_argument("Container must not be empty");

       auto init = *it;
       return aggregate_recursive_impl(std::next(it), end, std::forward<Func>(func), init);
    }


/*     template <typename T, std::size_t N, typename Func, typename ResultT>
    ResultT aggregate_recursive(const T (&arr)[N], Func func, ResultT init) {
        return aggregate_recursive_impl(arr, arr + N, func, init);
    } */

} // namespace algo