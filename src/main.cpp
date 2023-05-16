#include "cube.hpp"
#include <iostream>
#include <bitset>

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

void thistlethwaite() {

}

int main() {

    Cube cube;

    // First, scramble cube
    std::vector<Move> scramble{Move::F, Move::F};
    cube.applyMoves(scramble);

    std::bitset<16> edges(cube.getEdgeParity());

    std::cout << edges << "\n";

    /*
    std::vector<Move> moves;
    bool solved = solveIDDfs(cube, moves, 8);

    if (solved) {
        printf("Solved CUBE\n%s\n", movesToString(moves).c_str());
    }
    */

    return 0;
}