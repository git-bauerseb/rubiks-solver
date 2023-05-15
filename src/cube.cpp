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

// Rotations
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
    permute(RIGHT, );
    permute(RIGHT, );
}

void Cube::rotateRPrime() {

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