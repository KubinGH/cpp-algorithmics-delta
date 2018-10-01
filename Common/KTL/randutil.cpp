#pragma once

#include <random>

// Randomization utility
// random_device{}() - randomizes seed. this is constant on some compilers
//                     for some reason. You can use any valid seed.
// uniform_int_distribution<T>{a, b} - prepares a caller for the generator.
// Works on any range contained in numeric_limits<T>::min(), ~::max()
// Use gen.seed() before usage, with some random integer
//      (time(0) should be enough)
std::mt19937 gen{std::random_device{}()};
template<typename T>
T randint(T a, T b)
    { return std::uniform_int_distribution<T>{a, b}(gen); }
