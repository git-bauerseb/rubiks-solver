#include "solver.hpp"

// G1
void Solver::g1TableToFile() {
    // Create table file
    std::ofstream tFile;
    tFile.open("../resources/table1.pru",
        std::ios_base::out 
        | std::ios_base::binary);

    // Write map

    // First, write map size
    write<std::size_t>(tFile, m_G1Table.size());

    // Write key/value pairs
    for (std::map<uint16_t, int>::iterator it = m_G1Table.begin();
            it != m_G1Table.end(); ++it) {
        uint16_t key = it->first;
        int value = it->second;

        write<uint16_t>(tFile, key);
        write<int>(tFile, value);
    }

    tFile.close();
}

void Solver::readG1Table() {
    if (!std::filesystem::exists("../resources/table1.pru")) {
        std::cout << "Error! Pruning table not available\n";
    } else {
        std::ifstream tFile;
        tFile.open("../resources/table1.pru",
        std::ios_base::in 
        | std::ios_base::binary);

        std::size_t size = read<std::size_t>(tFile);
        std::cout << "G1 table has size: " << size << "\n";

        for (int i = 0; i < size; ++i) {
            uint16_t key = read<uint16_t>(tFile);
            int value = read<int>(tFile);
            m_G1Table.insert({key, value});
        }
    }
}


void Solver::idG1(Cube& cube, int cDepth, int rDepth) {
    if (rDepth < 0) {return;}

    uint16_t edgeParity = cube.getEdgeParity();
    if (m_G1Table.count(edgeParity) <= 0) {
        m_G1Table.insert({edgeParity, cDepth});
    }

    for (auto& m : m_G1Moves) {
        Cube newC = cube;
        newC.applyMove(m);

        idG1(newC, cDepth+1, rDepth-1);
    }
}

void Solver::generateG1Table(int depth) {
    std::cout << "Generating pruning tables for G1\n";

    if (!std::filesystem::exists("../resources/table1.pru")) {
        Cube cube;
        for (int i = 0; i <= depth; ++i) {
            idG1(cube,0,i);
        }
        std::cout << "Done! Size: " << m_G1Table.size() << "\n";
        std::cout << "Write table to ../resources/table1.pru\n";
        g1TableToFile();
    } else {
        std::cout << "Pruning table for G1 already exists\n";
    }
}


// G2
void Solver::g2TableToFile() {
    // Create table file
    std::ofstream tFile;
    tFile.open("../resources/table2.pru",
        std::ios_base::out 
        | std::ios_base::binary);

    // Write map

    // First, write map size
    write<std::size_t>(tFile, m_G2Table.size());

    // Write key/value pairs
    for (std::map<uint16_t, int>::iterator it = m_G2Table.begin();
            it != m_G2Table.end(); ++it) {
        uint16_t key = it->first;
        int value = it->second;

        write<uint16_t>(tFile, key);
        write<int>(tFile, value);
    }

    tFile.close();
}

void Solver::idG2(Cube& cube, int cDepth, int rDepth) {
    if (rDepth < 0) {return;}

    uint16_t entry = (static_cast<uint16_t>(cube.getCornerParity()) << 8) | (cube.eSliceEdges());

    if (!m_G2Table.count(entry)) {
        m_G2Table.insert({entry, cDepth});
    }

    for (auto& m : m_G2Moves) {
        Cube newC = cube;
        newC.applyMove(m);

        if (rDepth-1 >= 0)
        idG2(newC, cDepth+1, rDepth-1);
    }
}

void Solver::generateG2Table(int depth) {
    std::cout << "Generating pruning tables for G2\n";

    if (!std::filesystem::exists("../resources/table2.pru")) {
        Cube cube;
        for (int i = 0; i <= depth; ++i) {
            idG2(cube,0,i);
            std::cout << "Depth: " << i << " Map size: " << m_G2Table.size() << "\n";
        }
        std::cout << "Done! Size: " << m_G2Table.size() << "\n";
        std::cout << "Write table to ../resources/table2.pru\n";
        g2TableToFile();
    } else {
        std::cout << "Pruning table for G2 already exists\n";
    }
}

void Solver::readG2Table() {
    if (!std::filesystem::exists("../resources/table2.pru")) {
        std::cout << "Error! Pruning table not available\n";
    } else {
        std::ifstream tFile;
        tFile.open("../resources/table2.pru",
        std::ios_base::in 
        | std::ios_base::binary);

        std::size_t size = read<std::size_t>(tFile);
        std::cout << "G2 table has size: " << size << "\n";

        for (int i = 0; i < size; ++i) {
            uint16_t key = read<uint16_t>(tFile);
            int value = read<int>(tFile);
            m_G2Table.insert({key, value});
        }
    }
}


// G3
void Solver::g3TableToFile() {
    // Create table file
    std::ofstream tFile;
    tFile.open("../resources/table3.pru",
        std::ios_base::out 
        | std::ios_base::binary);

    // Write map

    // First, write map size
    write<std::size_t>(tFile, m_G3Table.size());

    // Write key/value pairs
    for (std::map<__uint128_t, int>::iterator it = m_G3Table.begin();
            it != m_G3Table.end(); ++it) {
        __uint128_t key = it->first;
        int value = it->second;

        write<__uint128_t>(tFile, key);
        write<int>(tFile, value);
    }

    tFile.close();
}

void Solver::readG3Table() {
    if (!std::filesystem::exists("../resources/table3.pru")) {
        std::cout << "Error! Pruning table not available\n";
    } else {
        std::ifstream tFile;
        tFile.open("../resources/table3.pru",
        std::ios_base::in 
        | std::ios_base::binary);

        std::size_t size = read<std::size_t>(tFile);
        std::cout << "G3 table has size: " << size << "\n";

        for (int i = 0; i < size; ++i) {
            __uint128_t key = read<__uint128_t>(tFile);
            int value = read<int>(tFile);
            m_G3Table.insert({key, value});
        }
    }
}

void Solver::idG3(Cube& cube, int cDepth, int rDepth) {
    if (rDepth < 0) {return;}
    __uint128_t encoding = cube.getCornerEncoding();

    if (!m_G3Table.count(encoding)) {
        m_G3Table.insert({encoding, cDepth});
    }

    for (auto& m : m_G3Moves) {
        Cube newC = cube;
        newC.applyMove(m);

        if (rDepth-1 >= 0)
        idG3(newC, cDepth+1, rDepth-1);
    }
}

void Solver::generateG3Table(int depth) {
    std::cout << "Generating pruning tables for G3\n";

    if (!std::filesystem::exists("../resources/table3.pru")) {
        Cube cube;
        for (int i = 0; i <= depth; ++i) {
            idG3(cube,0,i);
            std::cout << "Depth: " << i << " Map size: " << m_G3Table.size() << "\n";
        }
        std::cout << "Done! Size: " << m_G3Table.size() << "\n";
        std::cout << "Write table to ../resources/table3.pru\n";
        g3TableToFile();
    } else {
        std::cout << "Pruning table for G3 already exists\n";
    }
}


// PUBLIC METHODS

void Solver::halfTurnID(Cube& cube, int rDepth) {

    __uint128_t encoding = cube.getCornerEncoding();
    m_HalfPossible.insert(encoding);

    if (rDepth <= 0) return;

    for (const Move& move : m_HalfTurns) {
        Cube newCube = cube;
        newCube.applyMove(move);

        halfTurnID(newCube, rDepth-1);
    }
}

void Solver::generateHalfTurnTable() {
    if (!std::filesystem::exists("../resources/half.tab")) {
        Cube cube;
        for (int i = 0; i <= 6; ++i) {
            halfTurnID(cube, i);
        }

        if (m_HalfPossible.size() != 96) {
            std::cout << "Missing moves\n";
        }

        // Write half turn table to file
        std::ofstream tFile;
        tFile.open("../resources/half.tab",
            std::ios_base::out 
            | std::ios_base::binary);


        // Write values
        for (std::set<__uint128_t>::iterator it = m_HalfPossible.begin();
                it != m_HalfPossible.end(); ++it) {
            __uint128_t key = *it;
            write<__uint128_t>(tFile, key);
        }

        tFile.close();
    } else {
        std::cout << "Half turn table already exists.\n";
    }
}

void Solver::readHalfTurnTable() {
    if (!std::filesystem::exists("../resources/half.tab")) {
        std::cout << "Error! Table not available\n";
    } else {
        std::ifstream tFile;
        tFile.open("../resources/half.tab",
        std::ios_base::in 
        | std::ios_base::binary);

        for (int i = 0; i < 96; ++i) {
            __uint128_t value = read<__uint128_t>(tFile);
            m_HalfPossible.insert(value);
        }
    }
}

void Solver::init() {
    generateG1Table(7);
    readG1Table();

    generateG2Table(7);
    readG2Table();

    // Generate a table that stores corner information about which
    // configurations of a cube can be generated with half turns
    generateHalfTurnTable();
    readHalfTurnTable();

    generateG3Table(7);
    readG3Table();
}

// SOLVE METHODS
bool Solver::dfsG0(Cube& current, std::vector<Move>& solveMoves, int dRemaining) {
    uint16_t parity = current.getEdgeParity();
    
    int lowerBound;

    if (m_G1Table.count(parity)) {
        lowerBound = m_G1Table[parity];
    } else {
        // If not in there, lower bound is G1 pruning depth + 1
        lowerBound = 8;
    }

    if (lowerBound > dRemaining) {return false;}
    else if (parity == ((1 << 12) - 1)) {
        return true;
    } else if (dRemaining <= 0) {
        return false;
    } else {
        for (auto& m : m_G1Moves) {
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


void Solver::g0Phase(Cube& cube, std::vector<Move>& moves, int dLimit) {
    for (int i = 0; i <= dLimit; ++i) {
        if (dfsG0(cube, moves, i)) {break;}
        printf("Searching depth: %d\n", i);
        moves.clear();
    }
}


// G1 -> G2
bool Solver::dfsG1(Cube& current, std::vector<Move>& solveMoves, int dRemaining) {
    uint16_t parity = (current.getCornerParity() << 8) | (current.eSliceEdges());

    int lowerBound;

    if (m_G2Table.count(parity)) {
        lowerBound = m_G2Table[parity];
    } else {
        // If not in there, lower bound is G2 pruning depth + 1
        lowerBound = 8;
    }

    if (lowerBound > dRemaining) {return false;}
    else if (parity == 0xFF04) {
        return true;
    } else if (dRemaining <= 0) {
        return false;
    } else {
        for (auto& m : m_G2Moves) {
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

void Solver::g1Phase(Cube& cube, std::vector<Move>& moves, int dLimit) {
    for (int i = 0; i <= dLimit; ++i) {
        if (dfsG1(cube, moves, i)) {break;}
        printf("Searching depth: %d\n", i);
        moves.clear();
    }
}

// G2 -> G3
bool Solver::dfsG2(Cube& current, std::vector<Move>& solveMoves, int dRemaining) {
    __uint128_t parity = current.getCornerEncoding();
    int lowerBound;

    if (m_G3Table.count(parity)) {
        lowerBound = m_G3Table[parity];
    } else {
        // If not in there, lower bound is G2 pruning depth + 1
        lowerBound = 8;
    }

    bool poss = m_HalfPossible.count(parity) > 0;

    if (lowerBound > dRemaining) {return false;}
    else if (poss && current.allOpposite()) {
        return true;
    } else if (dRemaining <= 0) {
        return false;
    } else {
        for (auto& m : m_G3Moves) {
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

void Solver::g2Phase(Cube& cube, std::vector<Move>& moves, int dLimit) {
    for (int i = 0; i <= dLimit; ++i) {
        if (dfsG2(cube, moves, i)) {break;}
        printf("Searching depth: %d\n", i);
        moves.clear();
    }
}


bool Solver::dfsG3(Cube& current, std::vector<Move>& solveMoves, int dRemaining) {
    __uint128_t parity = current.getCornerEncoding();
    int lowerBound;

    if (m_G3Table.count(parity)) {
        lowerBound = m_G3Table[parity];
    } else {
        // If not in there, lower bound is G2 pruning depth + 1
        lowerBound = 8;
    }
    
    if (current.isSolved()) {
        return true;
    } else if (dRemaining <= 0) {
        return false;
    } else {
        for (auto& m : m_G4Moves) {
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

void Solver::g3Phase(Cube& cube, std::vector<Move>& moves, int dLimit) {
    for (int i = 0; i <= dLimit; ++i) {
        if (dfsG3(cube, moves, i)) {break;}
        printf("Searching depth: %d\n", i);
        moves.clear();
    }
}


void Solver::solve(Cube& cube) {
    std::vector<Move> moves;

    
    // Going from G0 to G1
    printf("G0 --> G1\n");
    g0Phase(cube, moves, 10);
    printf("Found moves: %s\n", movesToString(moves).c_str());
    cube.applyMoves(moves);
    moves.clear();
    

    
    
    printf("G1 --> G2\n");
    g1Phase(cube, moves, 10);
    printf("Found moves: %s\n", movesToString(moves).c_str());
    cube.applyMoves(moves);
    moves.clear();
    

    
    printf("G2 --> G3\n");
    g2Phase(cube, moves, 13);
    printf("Found moves: %s\n", movesToString(moves).c_str());
    cube.applyMoves(moves);
    moves.clear();
    

    printf("G3 --> Solved\n");
    g3Phase(cube, moves, 14);
    printf("Found moves: %s\n", movesToString(moves).c_str());
    cube.applyMoves(moves);
    moves.clear();
}

