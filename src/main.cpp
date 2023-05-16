#include "cube.hpp"

#include <iostream>
#include <bitset>
#include <vector>
#include <set>


// Moves allowed in group G0
const std::vector<Move> g0Moves 
    = {Move::U, Move::D, Move::F, Move::B, Move::L, Move::R};

// Moves allowed in group G1
const std::vector<Move> g1Moves
    = {Move::U, Move::D, Move::F2, Move::B2, Move::L, Move::R};

// Moves allowed in group G2
const std::vector<Move> g2Moves
    = {Move::U, Move::U_PRIME, Move::U2, Move::D, Move::D_PRIME, Move::D2, Move::F2, Move::B2, Move::L2, Move::R2};

// Moves allowed in group G3
const std::vector<Move> g3Moves
    = {Move::U2, Move::D2, Move::R2, Move::L2, Move::F2, Move::B2};


std::set<__uint128_t> g3PSet;
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
    if (g3PSet.find(current.getCornerEncoding()) != g3PSet.end() && current.allOpposite()) {
        return true;
    } else if (dRemaining <= 0) {return false;
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
        moves.clear();
    }
    return false;
}

bool g1(Cube& cube, std::vector<Move>& moves, int dLimit) {
    for (int i = 0; i <= dLimit; ++i) {
        if (dfsG1(cube, moves, i)) {return true;}
        moves.clear();
    }
    return false;
}

bool g2(Cube& cube, std::vector<Move>& moves, int dLimit) {
    for (int i = 0; i <= dLimit; ++i) {
        if (dfsG2(cube, moves, i)) {return true;}
        moves.clear();
    }
    return false;
}

bool g3(Cube& cube, std::vector<Move>& moves, int dLimit) {
    for (int i = 0; i <= dLimit; ++i) {
        if (dfsG3(cube, moves, i)) {return true;}
        moves.clear();
    }
    return false;
}

void thistlethwaite(Cube& cube) {
    std::vector<Move> moves;

    // Going from G0 to G1
    printf("G0 --> G1\n");
    g0(cube, moves, 7);
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

void g3Pruning(Cube& cube, int dLimit) {
    if (dLimit <= 0) {
        auto encoded = cube.getCornerEncoding();
        if (g3PSet.find(encoded) == g3PSet.end())
            g3PSet.insert(encoded);
    } else {
        for (auto& m: g3PruningMoves) {
            Cube nCube = cube;
            nCube.applyMove(m);
            g3Pruning(nCube, dLimit-1);
        }
    }
}

void generateG3PruningTable() {
    Cube cube;
    for (int i = 0; i <= 5; ++i) {
        g3Pruning(cube, i);
    }
}

int main() {

    generateG3PruningTable();
    // printf("Size of G3 Pruning table: %ld\n", g3PSet.size());    // Should print '96'

    
    Cube cube;
    // First, scramble cube
    std::vector<Move> scramble{
        Move::R2, Move::F_PRIME, Move::U2, Move::L, Move::D,
        Move::U, Move::R2, Move::L_PRIME, Move::D, Move::L_PRIME, Move::B2, Move::U2};

    // R2 F' U2 L D U R2 L' D L' B2 U2

    cube.applyMoves(scramble);
    cube.printCube();
    thistlethwaite(cube);
    cube.printCube();
    
    return 0;
}