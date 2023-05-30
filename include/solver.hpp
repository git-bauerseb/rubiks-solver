#ifndef RC_SOLVER_SOLVER_H
#define RC_SOLVER_SOLVER_H

#include <iostream>
#include <filesystem>

#include <set>
#include <map>
#include <vector>

#include <cstdint>

#include "cube.hpp"
#include "util.hpp"

// Represents a solver object that, given a specific instance of a cube,
// can solve it using Thistletwaite algorithm.
class Solver {

    public:

        // Initialize solver (i.e. load prunint tables for search)
        void init();

        // G1

        // Generate search-tree pruning table for transition from G0-G1
        // Maps edge parity (16-bit integer) to minimum depth to reach this
        // parity.
        //
        // If during search our remaining depth < min. depth to reach parity
        // search tree can be pruned.
        void generateG1Table(int depth);

        // Read in the pruning table generated for G0-G1 search.
        // The pruning table has to be generated beforehand by calling generateG1Table(depth)
        void readG1Table();

        // G2
        void generateG2Table(int depth);
        void readG2Table();

        // G3
        void generateG3Table(int depth);
        void readG3Table();

        // Use G3 table for G4
        void generateG4Table(int depth);
        void readG4Table();


        void solve(Cube& cube);


    private:

        const int G1_PRUNING_DEPTH = 6;
        const int G2_PRUNING_DEPTH = 8;
        const int G3_PRUNING_DEPTH = 8;
        const int G4_PRUNING_DEPTH = 8;


        // Applies a depth first search
        // Arguments
        //  S - lambda function which returns true if the provided cube is solved according
        //      to current state
        //  M - lambda function returning the allowable moves
        template<typename S, typename E, typename Lookup>
        bool dfs(Cube& cube,
                 std::vector<Move>& path,
                 const S& isSolved,
                 const std::vector<Move>& moves,
                 const E& getEncoding,
                 int rDepth,
                 Lookup& lookup,
                 int pruningDepth) const;


        template<typename S, typename E, typename Lookup>
        void iddfs(Cube& cube,
                   std::vector<Move>& path,
                   const S& isSolved,
                   const std::vector<Move>& moves,
                   const E& getEncoding,
                   int depthLimit,
                   Lookup& lookup,
                   int pruningDepth) const;



        void generateHalfTurnTable();
        void halfTurnID(Cube& cube, int rDepth);

        void readHalfTurnTable();


        // Iterative deepening search for G1 table generation.
        // Arguments:
        //      cDepth  -   current depth
        //      rDepth  -   remaining depth
        void idG1(Cube& cube, int cDepth, int rDepth);
        void idG2(Cube& cube, int cDepth, int rDepth);
        void idG3(Cube& cube, int cDepth, int rDepth);
        void idG4(Cube& cube, int cDepth, int rDepth);

        // Write G1 pruning table to output file
        void g1TableToFile();   
        void g2TableToFile();
        void g3TableToFile();
        void g4TableToFile();
        

        std::map<uint16_t, int> m_G1Table;          // Pruning table for group G1
        std::map<uint16_t, int> m_G2Table;          // Pruning table for group G2
        std::map<__uint128_t, int> m_G3Table;       // Pruning table for group G3
        std::map<CubeRepresentation, int,
            CubeRepresentationCompare> m_G4Table;   // Pruning table for group G4


        std::set<__uint128_t> m_HalfPossible;   // Stores corner configuration of all
                                                // cubes that can be solved by half turns

        const std::vector<Move> m_G1Moves = {
            Move::U, Move::U_PRIME, Move::U2,
            Move::D, Move::D_PRIME, Move::D2,
            Move::F, Move::F_PRIME, Move::F2,
            Move::B, Move::B_PRIME, Move::B2,
            Move::L, Move::L_PRIME, Move::L2,
            Move::R, Move::R_PRIME, Move::R2
        };

        std::vector<Move> m_G2Moves = {
            Move::U, Move::U_PRIME, Move::U2, 
            Move::D, Move::D_PRIME, Move::D2,
            Move::L, Move::L_PRIME, Move::L2,
            Move::R, Move::R_PRIME, Move::R2,
            Move::F2, Move::B2
        };

        const std::vector<Move> m_G3Moves = {
            Move::U, Move::U_PRIME, Move::U2,
            Move::D, Move::D_PRIME, Move::D2,
            Move::F2, Move::B2, Move::L2, Move::R2
        };

        const std::vector<Move> m_G4Moves = {
            Move::U2, Move::D2, Move::L2, Move::R2, Move::F2, Move::B2
        };

        const std::vector<Move> m_HalfTurns = {
            Move::U2, Move::D2, Move::L2, Move::R2, Move::F2, Move::B2
        };


};

#endif