#ifndef RC_SOLVER_CUBE_H
#define RC_SOLVER_CUBE_H

#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdint>

// Number of bits used for color encoding in cube representation.
static const int COLOR_BIT_WIDTH = 3;

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

        void rotateD();        // Quarter-rotation (90 deg.) around down face.
        void rotateDPrime();   // Opposite direction as in upper direction (rotateU)


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
        inline int getPieceColor(int face, int position) {
            return (m_faces[face] >> (COLOR_BIT_WIDTH * position)) & 0x7;
        }

        uint64_t m_faces[6];

};

#endif