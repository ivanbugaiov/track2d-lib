#include "include/statistics.hpp"
#include <cmath>
#include <cfloat>
#include <iostream>

Statistics::Statistics() {
    reset();
} // Statistics

Statistics::~Statistics() {
} // ~Statistics

void Statistics::reset() {
    min = std::numeric_limits<float>::max();
    max = std::numeric_limits<float>::min();
    sum = 0.0;
    squares_sum = 0.0;
    count = 0;
} // init

void Statistics::put(double val) {
    sum += val;
    squares_sum += val * val;
    min = (min < val) ? min : val;
    max = (max > val) ? max : val;
    ++count;
} // put

double Statistics::get_min() const {
    return min;
} // get_min

double Statistics::get_max() const {
    return max;
} // get_max

double Statistics::get_avg() const {
    if (count <= 0) { return 0.0; }
    return sum / double(count);
} // get_avg

double Statistics::get_var() const {
    if (count <= 1) { return 0.0; }
    return (squares_sum - sum*sum / double(count)) / double(count - 1);
} // get_var

double Statistics::get_std() const {
    return sqrt(get_var());
} // get_std

unsigned int Statistics::get_count() const {
    return count;
} // get_count

void Statistics::print() const {
    std::cout << "count: " << std::fixed << get_count() << std::endl;
    std::cout << "min: " << std::fixed << get_min() << std::endl;
    std::cout << "max: " << std::fixed << get_max() << std::endl;
    std::cout << "avg: " << std::fixed << get_avg() << std::endl;
    std::cout << "var: " << std::fixed << get_var() << std::endl;
    std::cout << "std: " << std::fixed << get_std() << std::endl;
} // print
