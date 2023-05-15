#include "cube.hpp"

Cube::Cube() {
    memset(m_faces, 0, sizeof(m_faces));

    for (int f = 0; f <= BACK; ++f) {
        for (int i = 0; i < 9; ++i) {
            setPieceColor(f, i, f);
        }
    }
}

void Cube::printCube() {
    // Print top face
    int offset = 3;
    for (int i = 0; i < 9; ++i) {
        if (i == 0 || (i % 3) == 0) printf("%*c", offset, ' ');
        printf("%c", getColor(getPieceColor(UP, i)));
        if (i % 3 == 2) printf("\n");
    }

    // Print L, F, R, B faces
    for (int j = 0; j < 3; ++j) {
        for (auto& face :  std::vector<int>{LEFT, FRONT, RIGHT, BACK}) {
            for (int i = 0; i < 3; ++i) {
                char color = getColor(getPieceColor(face, j*3 + i));
                printf("%c", color);
            }
        }

        printf("\n"); 
    }

    // Print D face
    for (int i = 0; i < 9; ++i) {
        if (i == 0 || (i % 3) == 0) printf("%*c", offset, ' ');
        printf("%c", getColor(getPieceColor(DOWN, i)));
        if (i % 3 == 2) printf("\n");
    }
}


// ROTATIONS


void Cube::rotateU() {
    // L1 -> B1, B1 -> R1, R1 -> F1, F1 -> L1
    for (int i = 0; i < 3; ++i) {
        int l1 = getPieceColor(LEFT, i);
        int b1 = getPieceColor(BACK, i);
        int r1 = getPieceColor(RIGHT, i);
        int f1 = getPieceColor(FRONT, i);
        setPieceColor(BACK, i, l1);
        setPieceColor(RIGHT, i, b1);
        setPieceColor(FRONT, i, r1);
        setPieceColor(LEFT, i, f1);
    }

    // U1 -> U3, U3 -> U9, U9 -> U7
    // Corner/edge pieces
    permute(UP, 0,2,8,6);
    permute(UP, 1,5,7,3);
}

void Cube::rotateUPrime() {
    // L0 -> F0, F0 -> R0, R0 -> B0, B0 -> L0
    for (int i = 0; i < 3; ++i) {
        int l1 = getPieceColor(LEFT, i);
        int f1 = getPieceColor(FRONT, i);
        int r1 = getPieceColor(RIGHT, i);
        int b1 = getPieceColor(BACK, i);
        setPieceColor(FRONT, i, l1);
        setPieceColor(RIGHT, i, f1);
        setPieceColor(BACK, i, r1);
        setPieceColor(LEFT, i, b1);
    }

    // Corner/edge pieces
    permute(UP, 0, 6, 8, 2);
    permute(UP, 1,3,7,5);
}

void Cube::rotateR() {
    // F2 -> U2, U2 -> B6, B6 -> D2, D2 -> F2
    for (int i = 0; i < 3; ++i) {
        int f2 = getPieceColor(FRONT, 2 + i*3);
        int u2 = getPieceColor(UP, 2 + i*3);
        int b6 = getPieceColor(BACK, i*3);
        int d2 = getPieceColor(DOWN, 2 + i*3);
        setPieceColor(FRONT, 2 + i*3, d2);
        setPieceColor(UP, 2 + i*3, f2);
        setPieceColor(BACK, i*3, u2);
        setPieceColor(DOWN, 2 + i*3, b6);
    }

    // Corner/edge cases
    permute(RIGHT,0,2,8,6);
    permute(RIGHT,1,5,7,3);
}

void Cube::rotateRPrime() {
    // F2 -> D2, D2 -> B6, B6 -> U2, U2 -> F2
    for (int i = 0; i < 3; ++i) {
        int f2 = getPieceColor(FRONT, 2 + i*3);
        int u2 = getPieceColor(UP, 2 + i*3);
        int b6 = getPieceColor(BACK, 6 - i*3);
        int d2 = getPieceColor(DOWN, 2 + i*3);
        setPieceColor(FRONT, 2 + i*3, u2);
        setPieceColor(UP, 2 + i*3, b6);
        setPieceColor(BACK, 6 - i*3, d2);
        setPieceColor(DOWN, 2 + i*3, f2);
    }

    permute(RIGHT,0,6,8,2);
    permute(RIGHT,1,3,7,5);
}

void Cube::rotateL() {
    // F0 -> D0, D0 -> B8, B8 -> U0, U0 -> F0
    for (int i = 0; i < 3; ++i) {
        int f0 = getPieceColor(FRONT, 0 + i*3);
        int d0 = getPieceColor(DOWN, 0 + i*3);
        int b8 = getPieceColor(BACK, 8 - i*3);
        int u0 = getPieceColor(UP, 0 + i*3);
        setPieceColor(DOWN, 0 + i*3, f0);
        setPieceColor(BACK, 8 - i*3, d0);
        setPieceColor(UP, 0 + i*3, b8);
        setPieceColor(FRONT, 0 + i*3, u0);
    }

    permute(LEFT,0,2,8,6);
    permute(LEFT,1,5,7,3);
}

void Cube::rotateLPrime() {
    rotateL();
    rotateL();
    rotateL();
}

void Cube::rotateF() {
    // U6 -> R0, R0 -> D2, D2 -> L8, L8 -> U6
    for (int i = 0; i < 3; ++i) {
        int u6 = getPieceColor(UP, 6 + i);
        int r0 = getPieceColor(RIGHT, i*3);
        int d2 = getPieceColor(DOWN, 2 - i);
        int l8 = getPieceColor(LEFT, 8 - i*3);
        setPieceColor(RIGHT, i*3, u6);
        setPieceColor(DOWN, 2-i, r0);
        setPieceColor(LEFT, 8-i*3, d2);
        setPieceColor(UP, 6+i, l8);
    }

    // Corner/edge cases
    permute(FRONT,0,2,8,6);
    permute(FRONT,1,5,7,3);
}

void Cube::rotateFPrime() {
    rotateF();
    rotateF();
    rotateF();
}

void Cube::rotateB() {
    // U2 -> L0, L0 -> D6, D6 -> R8
    for (int i = 0; i < 3; ++i) {
        int u2 = getPieceColor(UP, 2-i);
        int l0 = getPieceColor(LEFT, i*3);
        int d6 = getPieceColor(DOWN, 6+i);
        int r8 = getPieceColor(RIGHT, 8-3*i);
        setPieceColor(UP, 2-i, r8);
        setPieceColor(LEFT, i*3, u2);
        setPieceColor(DOWN, 6+i, l0);
        setPieceColor(RIGHT, 8-3*i, d6);
    }

    // Cornder/edge cases
    permute(BACK,0,2,8,6);
    permute(BACK,1,5,7,3);
}

void Cube::rotateBPrime() {
    // @TODO: Implement properly
    rotateB();
    rotateB();
    rotateB();
}

void Cube::rotateD() {
    // F5 -> R5, R5 -> B5, B5 -> L5, L5 -> F5
    for (int i = 0; i < 3; ++i) {
        int f1 = getPieceColor(FRONT, 6 + i);
        int r1 = getPieceColor(RIGHT, 6 + i);
        int b1 = getPieceColor(BACK, 6 + i);
        int l1 = getPieceColor(LEFT, 6 + i);
        setPieceColor(RIGHT, 6 + i, f1);
        setPieceColor(BACK, 6 + i, r1);
        setPieceColor(LEFT, 6 + i, b1);
        setPieceColor(FRONT, 6 + i, l1);
    }

    // Bottom
    permute(UP, 0,2,8,6);
    permute(UP, 1,5,7,3);
}

void Cube::rotateDPrime() {
    rotateD();
    rotateD();
    rotateD();
}


// Private member functions

inline char Cube::getColor(int value) {
    switch (value) {
        case 0: return 'W';
        case 1: return 'R';
        case 2: return 'G';
        case 3: return 'Y';
        case 4: return 'O';
        case 5: return 'B';
        default: return '\0';
    }
}