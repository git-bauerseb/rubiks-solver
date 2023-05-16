#include "cube.hpp"

#include <iostream>
#include <bitset>
#include <vector>

// Moves allowed in group G0
const std::vector<Move> g0Moves 
    = {Move::U, Move::D, Move::F, Move::B, Move::L, Move::R};

// Moves allowed in group G1
const std::vector<Move> g1Moves
    = {Move::U, Move::D, Move::F2, Move::B2, Move::L, Move::R};



bool isSolved(Cube& cube) {
    // Check front
    return cube.haveColor(Color::GREEN,21,24)
        && cube.haveColor(Color::ORANGE,39,40,41,42)
        && cube.haveColor(Color::ORANGE,43,44)
        && cube.haveColor(Color::BLUE,50,53);
}

bool isCrossSolved(Cube& cube) {
    return cube.haveColor(Color::WHITE, 1,3,4,5)
        && cube.haveColor(Color::WHITE, 5,7)
        && cube.haveColor(Color::RED, 10,13)
        && cube.haveColor(Color::ORANGE, 37, 40)
        && cube.haveColor(Color::GREEN, 19, 22)
        && cube.haveColor(Color::BLUE, 46, 49);
}

bool dfs(Cube current, std::vector<Move>& solveMoves, int dRemaining) {
    if (isCrossSolved(current)) {
        return true;
    } else if (dRemaining <= 0) {return false;
    } else {
        for (int m = Move::U; m <= Move::M_PRIME; ++m) {
            Cube nCube = current;
            nCube.applyMove(static_cast<Move>(m));
            solveMoves.push_back(static_cast<Move>(m));
            if (dfs(nCube, solveMoves, dRemaining-1)) {
                return true;
            }
            solveMoves.pop_back();
        }

        return false;
    }
}

// Use iterative-deepening DFS
bool solveIDDfs(Cube current, std::vector<Move>& moves, int dLimit) {
    for (int i = 0; i <= dLimit; ++i) {
        if (dfs(current, moves, i)) {
            return true;
        }
        moves.clear();
    }
    return false;
}

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

bool g0(Cube& cube, std::vector<Move>& moves, int dLimit) {
    for (int i = 0; i <= dLimit; ++i) {
        if (dfsG0(cube, moves, i)) {return true;}
        moves.clear();
    }
    return false;
}

void thistlethwaite(Cube& cube) {
    // Going from G0 to G1
    printf("G0 --> G1\n");
    std::vector<Move> moves;
    g0(cube, moves, 7);
    printf("%s\n", movesToString(moves).c_str());
}

int main() {

    Cube cube;

    // First, scramble cube
    std::vector<Move> scramble{
        Move::F, Move::D, Move::L2, Move::D_PRIME,
        Move::U, Move::R_PRIME};

    cube.applyMoves(scramble);
    thistlethwaite(cube);

    return 0;
}