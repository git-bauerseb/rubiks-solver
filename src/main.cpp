#include "cube.hpp"
#include "solver.hpp"

#include <iostream>
#include <bitset>
#include <vector>
#include <map>
#include <fstream>
#include <cstdlib>
#include <filesystem>


// Moves allowed in group G0
const std::vector<Move> g0Moves  = {
    Move::U, Move::U_PRIME, Move::U2,
    Move::D, Move::D_PRIME, Move::D2,
    Move::F, Move::F_PRIME, Move::F2,
    Move::B, Move::B_PRIME, Move::B2,
    Move::L, Move::L_PRIME, Move::L2,
    Move::R, Move::R_PRIME, Move::R2,
};

// "U", "U'", "U2", "D", "D'", "D2", "L", "L'", "L2", "R", "R'", "R2", "F2", "B2"


// Moves allowed in group G1
const std::vector<Move> g1Moves = {
    Move::U, Move::U_PRIME, Move::U2, 
    Move::D, Move::D_PRIME, Move::D2,
    Move::L, Move::L_PRIME, Move::L2,
    Move::R, Move::R_PRIME, Move::R2,
    Move::F2, Move::B2
};

// Moves allowed in group G2
const std::vector<Move> g2Moves = {
    Move::U, Move::U_PRIME, Move::U2,
    Move::D, Move::D_PRIME, Move::D2,
    Move::F2, Move::B2, Move::L2, Move::R2
};

// Moves allowed in group G3
const std::vector<Move> g3Moves
    = {Move::U2, Move::D2, Move::L2, Move::R2, Move::F2, Move::B2};


std::map<__uint128_t, int> g3PSet;


const std::vector<Move> g3PruningMoves 
    = {Move::U2, Move::D2, Move::R2, Move::L2, Move::F2, Move::B2};

bool dfsG0(Cube& current, std::vector<Move>& solveMoves, int dRemaining) {
    if (current.getEdgeParity() == ((1 << 12) - 1)) {
        return true;
    } else if (dRemaining <= 0) {return false;
    } else {
        for (auto& m : g0Moves) {
            Cube nCube = current;
            nCube.applyMove(m);
            solveMoves.push_back(m);
            if (dfsG0(nCube, solveMoves, dRemaining-1)) {
                return true;
            }
            solveMoves.pop_back();
        }

        return false;
    }
}

bool dfsG1(Cube& current, std::vector<Move>& solveMoves, int dRemaining) {
    // Check if current cube is solved according to state
    if (current.getCornerParity() == ((1 << 8) - 1) && current.eSliceEdges() == 4) {
        return true;
    } else if (dRemaining <= 0) {return false;
    } else {
        for (auto& m : g1Moves) {
            Cube nCube = current;
            nCube.applyMove(m);
            solveMoves.push_back(m);
            if (dfsG1(nCube, solveMoves, dRemaining-1)) {
                return true;
            }
            solveMoves.pop_back();
        }

        return false;
    }
}

bool dfsG2(Cube& current, std::vector<Move>& solveMoves, int dRemaining) {
    // Check if current cube is solved according to state
    // Cube is solved if:
    //  1) Corners are correctly oriented (configuration contained in pruning table)
    //  2) All colors are on opposite sides
    __uint128_t mDepth = g3PSet[current.getCornerEncoding()];

    if (g3PSet.find(current.getCornerEncoding()) != g3PSet.end() && current.allOpposite()) {
        return true;
    } else if (dRemaining <= mDepth) {return false;
    } else {
        for (auto& m : g2Moves) {
            Cube nCube = current;
            nCube.applyMove(m);
            solveMoves.push_back(m);
            if (dfsG2(nCube, solveMoves, dRemaining-1)) {
                return true;
            }
            solveMoves.pop_back();
        }

        return false;
    }
}

bool dfsG3(Cube& current, std::vector<Move>& solveMoves, int dRemaining) {
    // Check if current cube is solved according to state
    // Cube is solved if:
    //  1) Finally solved
    if (current.isSolved()) {
        return true;
    } else if (dRemaining <= 0) {return false;
    } else {
        for (auto& m : g3Moves) {
            Cube nCube = current;
            nCube.applyMove(m);
            solveMoves.push_back(m);
            if (dfsG3(nCube, solveMoves, dRemaining-1)) {
                return true;
            }
            solveMoves.pop_back();
        }

        return false;
    }
}

bool g0(Cube& cube, std::vector<Move>& moves, int dLimit) {
    for (int i = 0; i <= dLimit; ++i) {
        if (dfsG0(cube, moves, i)) {return true;}
        printf("Searching depth: %d\n", i);
        moves.clear();
    }
    return false;
}

bool g1(Cube& cube, std::vector<Move>& moves, int dLimit) {
    for (int i = 0; i <= dLimit; ++i) {
        if (dfsG1(cube, moves, i)) {return true;}
        printf("Searching depth: %d\n", i);
        moves.clear();
    }
    return false;
}

bool g2(Cube& cube, std::vector<Move>& moves, int dLimit) {
    for (int i = 0; i <= dLimit; ++i) {
        if (dfsG2(cube, moves, i)) {return true;}
        printf("Searching depth: %d\n", i);
        moves.clear();
    }
    return false;
}

bool g3(Cube& cube, std::vector<Move>& moves, int dLimit) {
    for (int i = 0; i <= dLimit; ++i) {
        if (dfsG3(cube, moves, i)) {return true;}
        printf("Searching depth: %d\n", i);
        moves.clear();
    }
    return false;
}

void thistlethwaite(Cube& cube) {
    std::vector<Move> moves;

    // Going from G0 to G1
    printf("G0 --> G1\n");
    g0(cube, moves, 10);
    printf("Found moves: %s\n", movesToString(moves).c_str());
    cube.applyMoves(moves);
    moves.clear();

    // Going from G1 to G2
    printf("G1 --> G2\n");
    g1(cube, moves, 10);
    printf("Found moves: %s\n", movesToString(moves).c_str());
    cube.applyMoves(moves);
    moves.clear();

    // Going from G2 to G3
    printf("G2 --> G3\n");
    g2(cube, moves, 13);
    printf("Found moves: %s\n", movesToString(moves).c_str());
    cube.applyMoves(moves);
    moves.clear();


    printf("G3 --> Solved\n");
    g3(cube, moves, 14);
    printf("Found moves: %s\n", movesToString(moves).c_str());
    cube.applyMoves(moves);
    moves.clear();
}

void g3Pruning(Cube& cube, int cDepth, int dLimit) {
    if (dLimit <= 0) {
        auto encoded = cube.getCornerEncoding();
        if (g3PSet.find(encoded) == g3PSet.end())
            g3PSet.insert(std::pair<__uint128_t, int>{encoded, cDepth});
    } else {
        for (auto& m: g3PruningMoves) {
            Cube nCube = cube;
            nCube.applyMove(m);
            g3Pruning(nCube, cDepth+1, dLimit-1);
        }
    }
}

void generateG3PruningTable() {
    Cube cube;
    for (int i = 0; i <= 5; ++i) {
        g3Pruning(cube, 0, i);
    }
}

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


    std::vector<Move> randomScramble = {
        Move::U, Move::F_PRIME, Move::B2,
        Move::R, Move::D_PRIME, Move::B,
        Move::L2, Move::R, Move::B, Move::F,
        Move::L2, Move::D2, Move::U_PRIME, Move::R2,
        Move::L, Move::U2, Move::L2, Move::R, Move::F,
        Move::R_PRIME, Move::D_PRIME, Move::L_PRIME, Move::B_PRIME,
        Move::U2, Move::B_PRIME, Move::F, Move::L, Move::R, Move::F, Move::R2
    };

    Cube cube;
    cube.applyMoves(randomScramble);

    
    Solver solver;
    solver.init();
    solver.solve(cube);

    return 0;
}