/****************************************************************************
 * TASKS:
// 1. In C++11 write a function summing all vector elements:
// std::vector xs = { 1, 2, 3, 4 };
// vectorSum(xs); // 10

// 2. Let's separate iteration and an operation to be done.
// Write a function aggregating a vector with any given function:
// aggregate(xs, add); // 10
// aggregate(xs, mul); // 24

// 3. Add an optional parameter to start aggregating with
// aggregate(xs, mul, 10); // 240
// aggregate(xs, concat, std::string("0")); // "01234"

// 4. Implement `aggregate` recursively
// Let's also make it work with plain arrays (and maybe other collections?)
// And with both function pointers and lambdas (and maybe something else?)
*****************************************************************************/

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <numeric>

#include "aggregate.h"

class Add {
    public:
        int operator()(int a, int b) {
            counter++;
            return a + b;
        }

        int counter = 0;
};

int add(int a, int b) {
    return a + b;
}

int mul(int a, int b) {
    return a * b;
}

std::string concat(const std::string& a, const int b) {
    return a + std::to_string(b);
}


int main() {
    std::vector<int> xs = { 1, 2, 3, 4 };

    Add addObj;

    auto sum = algo::vectorSum(xs);

    std::cout << "Sum: " << sum << std::endl;

    auto agrAdd = algo::aggregate(xs, addObj);
    std::cout << "Aggregate with add: " << agrAdd << std::endl;
    std::cout << "Add object counter: " << addObj.counter << std::endl;

    auto agrLambda = algo::aggregate(xs, [](int a, int b) { return a + b; });
    std::cout << "Aggregate with lambda: " << agrLambda << std::endl;

    //auto agrAddFunc = std::accumulate(xs.begin(), xs.end(), 0, addObj);

    auto agrMul = algo::aggregate(xs, mul);
    std::cout << "Aggregate with mul: " << agrMul << std::endl;

    auto agrMulInit = algo::aggregate(xs, mul, 10);
    std::cout << "Aggregate with mul and initial value 10: " << agrMulInit << std::endl;

    auto agrConcat = algo::aggregate(xs, concat, std::string("0"));
    std::cout << "Aggregate with concat and initial value '0': " << agrConcat << std::endl;
    
    auto agrRecursive = algo::aggregate_recursive(xs, add, 0);
    std::cout << "Recursive aggregate with add and initial value 0: " << agrRecursive << std::endl;

    int arr[] = { 1, 2, 3, 4 };
    auto agrArray = algo::aggregate(arr, add, 0);
    std::cout << "Aggregate with array and add: " << agrArray << std::endl;

    auto agrArrayNoInit = algo::aggregate_recursive(arr, add);
    std::cout << "Aggregate with array and add without initial value: " << agrArrayNoInit << std::endl;

    auto recAgrArray = algo::aggregate_recursive(arr, add, 0);
    std::cout << "Recursive aggregate with array and add: " << recAgrArray << std::endl;

    std::map<int, int> myMap = {{1, 10}, {2, 20}, {3, 30}};

    auto sumSeconds = [](int acc, const std::pair<const int, int>& p) {
        return acc + p.second;
    };

    auto result = algo::aggregate(myMap, sumSeconds, 0);

    std::cout << "Aggregate with map and sum of seconds: " << result << std::endl;

    return 0;
}