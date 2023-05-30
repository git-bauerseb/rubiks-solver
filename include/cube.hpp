#ifndef RC_SOLVER_CUBE_H
#define RC_SOLVER_CUBE_H

#include <utility>

#include <bitset>
#include <vector>
#include <string>

#include <cstdio>
#include <cstring>
#include <cstdint>

// Number of bits used for color encoding in cube representation.
static const int COLOR_BIT_WIDTH = 3;

// A rubiks cube is (here) described by 6 sides, 9 pieces on each side
// and 3 bits per color.
// This requires 144 bits which can be stored in 3 64-bit numbers.
struct CubeRepresentation {
    uint64_t m_representation[3];
};

struct CubeRepresentationCompare {
    bool operator() (const CubeRepresentation& lhs,
                    const CubeRepresentation& rhs) const {

        if (lhs.m_representation[0] != rhs.m_representation[0]) {
            return lhs.m_representation[0] < rhs.m_representation[0];
        } else  {
            if (lhs.m_representation[1] != rhs.m_representation[1]) {
                return lhs.m_representation[1] < rhs.m_representation[1];
            } else {
                return lhs.m_representation[2] < rhs.m_representation[2];
            }
        }
    }
};


// Enumeration of all possibly allowed moves
// Ordering is important (used in function Cube::applyMove())
enum Move : uint8_t {
    U,
    U_PRIME,
    U2,
    D,
    D_PRIME,
    D2,
    R,
    R_PRIME,
    R2,
    L,
    L_PRIME,
    L2,
    F,
    F_PRIME,
    F2,
    B,
    B_PRIME,
    B2,
    M,
    M_PRIME
};

std::string moveToString(Move move);
std::string movesToString(const std::vector<Move>& moves);

enum Face : uint8_t {
    UP      = 0,
    RIGHT   = 1,
    FRONT   = 2,
    DOWN    = 3,
    LEFT    = 4,
    BACK    = 5
};

// Integral values representing the colors on the cube.
// The ordering the same as on the faces.
enum Color : uint8_t {
    WHITE   = 0,
    RED     = 1,
    GREEN   = 2,
    YELLOW  = 3,
    ORANGE  = 4,
    BLUE    = 5
};

// Represents a rubiks cube in memory and supports
// rotation along faces.
// 
// The cube is represented as an array of 6 64-bit unsigned numbers.
// Each 3-bit part of the number encodes the color of one piece.
class Cube {

    public:
        // Creates a default cube in the solved state.
        Cube();

        // Rotations
        void rotateU();         // Quarter-rotation (90 deg.) around upper face
        void rotateUPrime();    // Quarter-rotation (90 deg.) in opposite (counter-clockwise) direction
        
        void rotateR();
        void rotateRPrime();

        void rotateL();
        void rotateLPrime();

        void rotateF();
        void rotateFPrime();

        void rotateB();
        void rotateBPrime();

        void rotateD();        // Quarter-rotation (90 deg.) around down face.
        void rotateDPrime();   // Opposite direction as in upper direction (rotateU)

        // Checks if pieces have the same color (in absolute addressing).
        // Absolute addressing: Per face index 0...8 and then address of face.
        // So 6th piece of right side would have address: RIGHT * 9 + 5 = 9 + 5 = 14
        bool haveColor(Color color, int idx1, int idx2, int idx3, int idx4);
        bool haveColor(Color color, int idx1, int idx2);

        // Checks whether the cube is in solved state, i.e. all pieces on each face have same color as the middle piece
        bool isSolved() const;

        // Check for each face whether it only contains color from the face or opposite face
        bool allOpposite() const;

        // Returns the edge parity (good/bad) edges of the cube.
        // The edges are indexed from 0-11 and need 1-bit encoding (0 = bad edge, 1 = good edge)
        uint16_t getEdgeParity() const;

        // Returns the corner parity (good/bad) of the cube.
        // The corners are indexed from 0-7 and need 1-bit encoding as in edge parity
        uint8_t getCornerParity() const;

        // Encoding of corners
        __uint128_t getCornerEncoding() const;

        // Get encoding of entire cube in 144 bits (192-bit actually)
        CubeRepresentation getTotalRepresentation() const;

        // Count the number of edges that are currently in the E-slice and belong there
        int eSliceEdges() const;


        void applyMoves(const std::vector<Move>& moves);
        void applyMove(Move move);


        // Applies a move encoded in the string provided as argument. The following move convention
        // is used:
        // 
        // F - 90 deg. clockwise rotation around front face (green)
        // B - 90 deg. clockwise rotation around back face (blue)
        // R - 90 deg. clockwise rotation around right face (red)
        // L - 90 deg. clockwise rotation around left face (orange)
        // U - 90 deg. clockwise rotation around up face (white)
        // D - 90 deg. clockwise rotation around bottom face (yellow)
        // 
        // If the move has a '2' as suffix it means the operation is applied twice
        // (e.g. R2 -> R R) => 180 deg. rotation
        // If the move has a ''' as suffix it reverses the rotation direction to counter-clockwise
        // (e.g. R' -> 90 deg. counter clockwise, R' = R R R)
        // 
        // Arguments
        //  representation  - string representing the move
        //  offset          - offset from which the decoding of a single move happens
        void applyMove(const std::string& representation, int offset);

        void applyMoves(const std::string& representation);


        // I/O routines

        // Print cube representation to stdout.
        // The printed layout is
        //    U
        //   LFRB 
        //    D
        void printCube();

    private:

        // Convert integral color (such as enum COLOR) to
        // character representation.
        inline char getColor(int value);

        // On a given face, permute the indices s.t. i1 -> i2 -> i3 -> i4 -> i1
        inline void permute(int face, int i1, int i2, int i3, int i4) {
            int tmp[4];
            tmp[0] = getPieceColor(face, i1);
            tmp[1] = getPieceColor(face, i2);
            tmp[2] = getPieceColor(face, i3);
            tmp[3] = getPieceColor(face, i4);

            setPieceColor(face, i2, tmp[0]);
            setPieceColor(face, i3, tmp[1]);
            setPieceColor(face, i4, tmp[2]);
            setPieceColor(face, i1, tmp[3]);
        }

        // Get the integral color value from a specific face and
        // position.
        inline void setPieceColor(int face, int position, int color) {
            m_faces[face] = m_faces[face] & ~(0x7 << (3 * position));
            m_faces[face] |= ((color & 0x7) << (COLOR_BIT_WIDTH * position));
        }

        // Set the color at a specified face and position.
        inline int getPieceColor(int face, int position) const {
            return (m_faces[face] >> (COLOR_BIT_WIDTH * position)) & 0x7;
        }

        uint64_t m_faces[6];

};

#endif