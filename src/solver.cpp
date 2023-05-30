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


// G4
void Solver::g4TableToFile() {
    // Create table file
    std::ofstream tFile;
    tFile.open("../resources/table4.pru",
        std::ios_base::out 
        | std::ios_base::binary);

    // Write map

    // First, write map size
    write<std::size_t>(tFile, m_G4Table.size());

    // Write key/value pairs
    for (std::map<CubeRepresentation, int, CubeRepresentationCompare>::iterator it = m_G4Table.begin();
            it != m_G4Table.end(); ++it) {
        
        write<uint64_t>(tFile, it->first.m_representation[0]);
        write<uint64_t>(tFile, it->first.m_representation[1]);
        write<uint64_t>(tFile, it->first.m_representation[2]);
        int value = it->second;
        write<int>(tFile, value);
    }

    tFile.close();
}

void Solver::readG4Table() {
    if (!std::filesystem::exists("../resources/table4.pru")) {
        std::cout << "Error! Pruning table not available\n";
    } else {
        std::ifstream tFile;
        tFile.open("../resources/table4.pru",
        std::ios_base::in 
        | std::ios_base::binary);

        std::size_t size = read<std::size_t>(tFile);
        std::cout << "G4 table has size: " << size << "\n";

        for (int i = 0; i < size; ++i) {
            CubeRepresentation repr;
            repr.m_representation[0] = read<uint64_t>(tFile);
            repr.m_representation[1] = read<uint64_t>(tFile);
            repr.m_representation[2] = read<uint64_t>(tFile);
            int value = read<int>(tFile);
            m_G4Table.insert({repr, value});
        }
    }
}

void Solver::idG4(Cube& cube, int cDepth, int rDepth) {
    if (rDepth < 0) {return;}
    CubeRepresentation encoding = cube.getTotalRepresentation();

    if (m_G4Table.count(encoding) == 0) {
        m_G4Table.insert({encoding, cDepth});
    }

    for (auto& m : m_G4Moves) {
        Cube newC = cube;
        newC.applyMove(m);

        if (rDepth-1 >= 0)
        idG4(newC, cDepth+1, rDepth-1);
    }
}

void Solver::generateG4Table(int depth) {
    std::cout << "Generating pruning tables for G4\n";

    if (!std::filesystem::exists("../resources/table4.pru")) {
        Cube cube;
        for (int i = 0; i <= depth; ++i) {
            idG4(cube,0,i);
            std::cout << "Depth: " << i << " Map size: " << m_G4Table.size() << "\n";
        }
        std::cout << "Done! Size: " << m_G4Table.size() << "\n";
        std::cout << "Write table to ../resources/table4.pru\n";
        g4TableToFile();
    } else {
        std::cout << "Pruning table for G4 already exists\n";
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
    
    generateG1Table(G1_PRUNING_DEPTH);
    readG1Table();

    generateG2Table(G2_PRUNING_DEPTH);
    readG2Table();

    // Generate a table that stores corner information about which
    // configurations of a cube can be generated with half turns
    // Needed in going from G2 to G3
    generateHalfTurnTable();
    readHalfTurnTable();

    generateG3Table(G3_PRUNING_DEPTH);
    readG3Table();
}

template<typename S, typename E, typename Lookup>
bool Solver::dfs(Cube& cube, std::vector<Move>& path,
                 const S& isSolved, const std::vector<Move>& moves,
                 const E& getEncoding, int remDepth,
                 Lookup& lookup, int pruningDepth) const {

    auto encoding = getEncoding(cube);

    int lowerBound;

    if (lookup.count(encoding)) {
        lowerBound = lookup[encoding];
    } else {
        lowerBound = pruningDepth + 1;
    }

    if (lowerBound > remDepth || remDepth <= 0) {return false;}
    else if (isSolved(cube)) {return true;}
    else {
        for (const Move& m : moves) {
            Cube newCube = cube;
            newCube.applyMove(m);

            path.push_back(m);
            if (dfs(newCube, path, isSolved, moves,
                    getEncoding, remDepth-1, lookup, pruningDepth)) {
                return true;
            }
            path.pop_back();
        }

        return false;
    }
}

template<typename S, typename E, typename Lookup>
void Solver::iddfs(Cube& cube, std::vector<Move>& path, const S& isSolved,
            const std::vector<Move>& moves, const E& getEncoding,
            int depthLimit, Lookup& lookup, int pruningDepth) const {
    for (int i = 0; i <= depthLimit; ++i) {
        printf("Searching depth: %d\n", i);
        if (dfs(cube, path, isSolved, moves, getEncoding, i, lookup, pruningDepth)) {
            break;
        }

        path.clear();
    }
}

void Solver::solve(Cube& cube) {
    std::vector<Move> moves;

    printf("G0 (Random) => G1\n");
    const auto g1IsSolved = [&](const Cube& cube) {
        return cube.getEdgeParity() == ((1 << 12) - 1);
    };
    const auto g1Encoding = [&](const Cube& cube) {
        return cube.getEdgeParity();
    };
    iddfs<decltype(g1IsSolved), decltype(g1Encoding), decltype(m_G1Table)>(
        cube, moves, g1IsSolved,
        m_G1Moves, g1Encoding, 10,
        m_G1Table, G1_PRUNING_DEPTH
    );
    printf("Found moves: %s\n", movesToString(moves).c_str());
    cube.applyMoves(moves);
    moves.clear();

    /*
    printf("G1 => G2\n");
    const auto g2IsSolved = [&](const Cube& cube) {
        return ((cube.getCornerParity() << 8) | (cube.eSliceEdges()))
            == 0xFF04;
    };
    const auto g2Encoding = [&](const Cube& cube) {
        return ((cube.getCornerParity() << 8) | (cube.eSliceEdges()));
    };
    iddfs<decltype(g2IsSolved), decltype(g2Encoding), decltype(m_G2Table)>(
        cube, moves, g2IsSolved,
        m_G2Moves, g2Encoding, 10,
        m_G2Table, G2_PRUNING_DEPTH
    );
    printf("Found moves: %s\n", movesToString(moves).c_str());
    cube.applyMoves(moves);
    moves.clear();

    
    printf("G2 => G3\n");
    const auto g3IsSolved = [&](const Cube& cube) {
        return m_HalfPossible.count(cube.getCornerEncoding()) > 0
            && cube.allOpposite();
    };
    const auto g3Encoding = [&](const Cube& cube) {return cube.getCornerEncoding();};
    iddfs<decltype(g3IsSolved), decltype(g3Encoding), decltype(m_G3Table)>(
        cube, moves, g3IsSolved,
        m_G3Moves, g3Encoding, 13,
        m_G3Table, G3_PRUNING_DEPTH);
    printf("Found moves: %s\n", movesToString(moves).c_str());
    cube.applyMoves(moves);
    moves.clear();

    
    printf("G3 => G4 (Solved)\n");
    const auto g4IsSolved = [&](const Cube& cube) {return cube.isSolved();};
    const auto g4Encoding = [&](const Cube& cube) {return cube.getTotalRepresentation();};
    iddfs<decltype(g4IsSolved), decltype(g4Encoding), decltype(m_G4Table)>(
        cube, moves, g4IsSolved,
        m_G4Moves, g4Encoding, 14,
        m_G4Table, G4_PRUNING_DEPTH);
    printf("Found moves: %s\n", movesToString(moves).c_str());
    cube.applyMoves(moves);
    moves.clear();
    */
}

