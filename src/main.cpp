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
    // Test performance first phase
    // F D2 F L' F' U B' U' R2 F' U2 L2 D2 B' F2 D2 U2 R L2 U' B D L F D' F2 L' F' U2 R
    /*
    std::vector<Move> scramble {
        Move::F, Move::D2, Move::F,
        Move::L_PRIME, Move::F_PRIME, Move::U,
        Move::B_PRIME, Move::U_PRIME, Move::R2, Move::F_PRIME,
        Move::U2, Move::L2, Move::D2, Move::B_PRIME,
        Move::F2, Move::D2, Move::U2, Move::R, Move::L2, Move::U_PRIME, Move::B,
        Move::D, Move::L, Move::F, Move::D_PRIME, Move::F2, Move::L_PRIME, Move::F_PRIME,
        Move::U2, Move::R
    };
    */


    // L U' L R F2 L2 R' D2 R L' D U' L' R U R L2 D' L' F2 U' D' R2 B2 R F2 U' L2 D2 R
    // Test performance second phase
    /*
    std::vector<Move> scramble{
        Move::L, Move::U_PRIME, Move::L, Move::R, Move::F2, Move::L2, Move::R_PRIME,
        Move::D2, Move::R, Move::L_PRIME, Move::D, Move::U_PRIME, Move::L_PRIME, Move::R,
        Move::U, Move::R, Move::L2, Move::D_PRIME, Move::L_PRIME, Move::F2, Move::U_PRIME,
        Move::D_PRIME, Move::R2, Move::B2, Move::R, Move::F2, Move::U_PRIME, Move::L2, Move::D2, Move::R
    };
    */
    
    // Test performance third phase
    // D' L2 D B2 D' U B2 U F2 D' U' F2 R2 D' R2 U2 L2 U2 D' F2 D U B2 U' F2 D' R2 L2 D' U2
    /*
    std::vector<Move> scramble {
        Move::D_PRIME, Move::L2, Move::D, Move::B2,
        Move::D_PRIME, Move::U, Move::B2, Move::U,
        Move::F2, Move::D_PRIME, Move::F2, Move::R2,
        Move::D_PRIME, Move::R2, Move::U2, Move::L2,
        Move::U2, Move::D_PRIME, Move::F2, Move::D, Move::U,
        Move::B2, Move::U_PRIME, Move::F2, Move::D_PRIME,
        Move::R2, Move::L2, Move::D_PRIME, Move::U2
    };

    // Performance for third phase
    // R2 L2 U2 F2 B2 L2 U2 D F2 D' U R2 D' F2 U' B2 D' R2 D R2 U' F2 U' L2 B2 U2 B2 F2 L2 B2
    std::vector<Move> scramble2 {
        Move::R2, Move::L2, Move::U2, Move::F2,
        Move::B2, Move::L2, Move::U2, Move::D,
        Move::F2, Move::D_PRIME, Move::U,
        Move::R2, Move::D_PRIME, Move::F2,
        Move::U_PRIME, Move::B2, Move::D_PRIME, Move::R2,
        Move::D, Move::R2, Move::U_PRIME, Move::F2, Move::U_PRIME,
        Move::L2, Move::B2, Move::U2, Move::B2, Move::F2, Move::L2, Move::B2
    };

    // Performance test for fourth phase
    // L2 F2 R2 B2 L2 D2 F2 D2 F2 B2 L2 U2 L2 U2 D2 B2 L2 U2 F2 U2 D2 L2 R2 B2 D2 F2 U2 R2 U2 D2
    std::vector<Move> scramble3 {
        Move::L2, Move::F2, Move::R2,
        Move::B2, Move::L2, Move::D2, Move::F2, Move::R2
    };
    */


   
    
    Cube cube;
    cube.applyMoves("B F R' D2 R' B' R U2 D F R2 U L U R2 F' U' R B2 L U' B' R' B' R2 F' B2 D B2 R");

    Solver solver;
    solver.init();
    solver.solve(cube);
    
    return 0;
}