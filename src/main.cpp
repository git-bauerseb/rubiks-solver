#include "cube.hpp"
#include "solver.hpp"

#include <iostream>
#include <bitset>
#include <vector>
#include <map>
#include <fstream>
#include <cstdlib>
#include <filesystem>

int main() {
    Cube cube;
    cube.applyMoves("L U' R2 B' U2 B2 D B2 F D' R L2 F2 U B D L2 U' F' R' B2 U' D F2 B D' L R B2 L");
    
    
    Solver solver;
    solver.init();
    solver.solve(cube);
    

    return 0;
}