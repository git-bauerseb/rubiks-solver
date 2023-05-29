#ifndef RC_SOLVER_UTIL_HPP
#define RC_SOLVER_UTIL_HPP

#include <iostream>
#include <fstream>
#include <ostream>

template<typename T>
void write(std::ofstream& oFile, T value) {
    oFile.write(reinterpret_cast<char*>(&value), sizeof(T));
}

template<typename T>
T read(std::ifstream& iFile) {
    T value;
    iFile.read(reinterpret_cast<char*>(&value), sizeof(value));
    return value;
}

#endif