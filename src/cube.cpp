#include "cube.hpp"

#include <iostream>

CubeRepresentation Cube::getTotalRepresentation() const {
    
    CubeRepresentation repr;

    // Face U/R in repr.m_repr[0]
    // Face F/D in repr.m_repr[1]
    // Face L/B in repr.m_repr[2]

    int offset = 0;

    for (int i = 0; i < 6; ++i) {
        if (!(i % 2)) {repr.m_representation[i/2] = 0; offset = 0;}
        for (int j = 0; j < 9; ++j) {
            repr.m_representation[i / 2] |= (static_cast<uint64_t>(getPieceColor(i, j)) << offset);
            offset += 3;
        }
    }

    return repr;
}

void Cube::applyMoves(const std::string& representation) {
    const int n = representation.size();

    for (int i = 0; i < n; ) {
        char current = representation[i];
        if (current != ' ') {
            applyMove(representation, i);
            while (i < n && representation[i] != ' ') {i++;}
        } else {
            i++;
        }
    }
}

void Cube::applyMove(const std::string& representation, int offset) {
    const int n = representation.size();

    char base = representation[offset];

    int move = Move::R;

    switch (base) {
        case 'R': move = Move::R; break;
        case 'L': move = Move::L; break;
        case 'U': move = Move::U; break;
        case 'D': move = Move::D; break;
        case 'F': move = Move::F; break;
        case 'B': move = Move::B; break;
    }

    // Check if there is a second character that encodes a move
    if (offset < n-1 && representation[offset+1] == '\'') {
        move++;
    } else if (offset < n-1 && representation[offset+1] == '2') {
        move += 2;
    }

    applyMove(static_cast<Move>(move));
}

bool Cube::isSolved() const {
    for (int i = 0; i < 6; ++i) {
        for (int p = 0; p < 9; ++p) {
            if (!(getPieceColor(i, p) == i)) return false;
        }
    }

    return true;
}

bool Cube::allOpposite() const {
    // Check front face
    for (int i = 0; i < 9; ++i) {
        int color = getPieceColor(FRONT, i);
        if (color != Color::GREEN && color != Color::BLUE) return false;
    }

    // Check back face
    for (int i = 0; i < 9; ++i) {
        int color = getPieceColor(BACK, i);
        if (color != Color::GREEN && color != Color::BLUE) return false;
    }

    // Check left face
    for (int i = 0; i < 9; ++i) {
        int color = getPieceColor(LEFT, i);
        if (color != Color::ORANGE && color != Color::RED) return false;
    }

    // Check right face
    for (int i = 0; i < 9; ++i) {
        int color = getPieceColor(RIGHT, i);
        if (color != Color::ORANGE && color != Color::RED) return false;
    }

    return true;
}

__uint128_t Cube::getCornerEncoding() const {

    __uint128_t encoded = 0;
    
    // First corner
    encoded = encoded | (0x7 & getPieceColor(UP, 8))
             | ((0x7 & getPieceColor(RIGHT, 0)) << 3)
             | ((0x7 & getPieceColor(FRONT, 2)) << 6);

    // Second corner
    encoded = encoded | ((0x7 & getPieceColor(UP, 2)) << 9)
             | ((0x7 & getPieceColor(BACK, 0)) << 12)
             | ((0x7 & getPieceColor(RIGHT, 2)) << 15);

    // Third corner
    encoded = encoded | ((0x7 & getPieceColor(UP, 0)) << 18)
             | ((0x7 & getPieceColor(BACK, 2)) << 21)
             | ((0x7 & getPieceColor(LEFT, 0)) << 24);

    // Fourth corner
    encoded = encoded | ((0x7 & getPieceColor(UP, 6)) << 27)
             | ((0x7 & getPieceColor(LEFT, 2)) << 30)
             | (static_cast<__uint128_t>(0x7 & getPieceColor(FRONT, 0)) << 33);

    // Fifth corner
    encoded = encoded | (static_cast<__uint128_t>(0x7 & getPieceColor(DOWN, 2)) << 36)
             | (static_cast<__uint128_t>(0x7 & getPieceColor(FRONT, 8)) << 39)
             | (static_cast<__uint128_t>(0x7 & getPieceColor(RIGHT, 6)) << 42);

    // Sixth corner
    encoded = encoded | (static_cast<__uint128_t>(0x7 & getPieceColor(DOWN, 8)) << 45)
             | (static_cast<__uint128_t>(0x7 & getPieceColor(BACK, 6)) << 48)
             | (static_cast<__uint128_t>(0x7 & getPieceColor(RIGHT, 8)) << 51);

    // Seventh corner
    encoded = encoded | (static_cast<__uint128_t>(0x7 & getPieceColor(DOWN, 6)) << 54)
             | (static_cast<__uint128_t>(0x7 & getPieceColor(BACK, 8)) << 57)
             | (static_cast<__uint128_t>(0x7 & getPieceColor(LEFT, 6)) << 60);

    // Eight corner
    encoded = encoded | (static_cast<__uint128_t>(0x7 & getPieceColor(FRONT, 6)) << 63)
             | (static_cast<__uint128_t>(0x7 & getPieceColor(DOWN, 0)) << 66)
             | (static_cast<__uint128_t>(0x7 & getPieceColor(LEFT, 8)) << 69);
    return encoded;
}

// Check if edge with color c1/c2 belongs to E-slice
static bool isEEdge(int c1, int c2) {
    return (c1 == Color::BLUE || c1 == Color::RED || c1 == Color::GREEN || c1 == Color::ORANGE)
        && (c2 == Color::BLUE || c2 == Color::RED || c2 == Color::GREEN || c2 == Color::ORANGE);
}

int Cube::eSliceEdges() const {
    int cnt = 0;

    // Check first edge
    int c1 = getPieceColor(FRONT, 5);
    int c2 = getPieceColor(RIGHT, 3);
    cnt += isEEdge(c1, c2);


    // Check second edge
    c1 = getPieceColor(RIGHT, 5);
    c2 = getPieceColor(BACK, 3);
    cnt += isEEdge(c1, c2);


    // Check third edge
    c1 = getPieceColor(BACK, 5);
    c2 = getPieceColor(LEFT, 3);
    cnt += isEEdge(c1, c2);

    // Check first edge
    c1 = getPieceColor(LEFT, 5);
    c2 = getPieceColor(FRONT, 3);
    cnt += isEEdge(c1, c2);

    return cnt;
}

uint8_t Cube::getCornerParity() const {
    int idx = 0;
    uint8_t oBitset = 0;

    // First corner
    int uColor = getPieceColor(UP, 8);
    if (uColor == Color::WHITE || uColor == Color::YELLOW) {oBitset |= (1 << idx);}
    idx++;

    // Second corner
    uColor = getPieceColor(UP, 2);
    if (uColor == Color::WHITE || uColor == Color::YELLOW) {oBitset |= (1 << idx);}
    idx++;

    // Third corner
    uColor = getPieceColor(UP, 0);
    if (uColor == Color::WHITE || uColor == Color::YELLOW) {oBitset |= (1 << idx);}
    idx++;

    // Fourth corner
    uColor = getPieceColor(UP, 6);
    if (uColor == Color::WHITE || uColor == Color::YELLOW) {oBitset |= (1 << idx);}
    idx++;

    // Fifth
    uColor = getPieceColor(DOWN, 2);
    if (uColor == Color::WHITE || uColor == Color::YELLOW) {oBitset |= (1 << idx);}
    idx++;

    // Sixth
    uColor = getPieceColor(DOWN, 8);
    if (uColor == Color::WHITE || uColor == Color::YELLOW) {oBitset |= (1 << idx);}
    idx++;


    // Seventh
    uColor = getPieceColor(DOWN, 6);
    if (uColor == Color::WHITE || uColor == Color::YELLOW) {oBitset |= (1 << idx);}
    idx++;

    // Eigth
    uColor = getPieceColor(DOWN, 0);
    if (uColor == Color::WHITE || uColor == Color::YELLOW) {oBitset |= (1 << idx);}
    idx++;

    return oBitset;
}

// Edge orientation member functions
uint16_t Cube::getEdgeParity() const {

    int topC = Color::WHITE;
    int botC = Color::YELLOW;

    // Index into bitset
    int idx = 0;

    // Bitset used for storing information about orientation
    uint16_t oBitset = 0;

    // Check first edge (UF)
    int uC = getPieceColor(UP, 7); int dC = getPieceColor(FRONT, 1);
    if ((uC == topC || uC == botC) || ((uC == Color::BLUE || uC == Color::GREEN) && !(dC == topC || dC == botC))) {oBitset |= (1 << idx);}
    idx++;
    // Check second edge (UR)
    uC = getPieceColor(UP, 5); dC = getPieceColor(RIGHT, 1);
    if ((uC == topC || uC == botC) || ((uC == Color::BLUE || uC == Color::GREEN) && !(dC == topC || dC == botC))) {oBitset |= (1 << idx);}
    idx++;
    // Check third edge (UB)
    uC = getPieceColor(UP, 1); dC = getPieceColor(BACK, 1);
    if ((uC == topC || uC == botC) || ((uC == Color::BLUE || uC == Color::GREEN) && !(dC == topC || dC == botC))) {oBitset |= (1 << idx);}
    idx++;
    // Check fourth edge (UL)
    uC = getPieceColor(UP, 3); dC = getPieceColor(LEFT, 1);
    if ((uC == topC || uC == botC) || ((uC == Color::BLUE || uC == Color::GREEN) && !(dC == topC || dC == botC))) {oBitset |= (1 << idx);}
    idx++;
    // DF
    uC = getPieceColor(DOWN, 1); dC = getPieceColor(FRONT, 7);
    if ((uC == topC || uC == botC) || ((uC == Color::BLUE || uC == Color::GREEN) && !(dC == topC || dC == botC))) {oBitset |= (1 << idx);}
    idx++;
    // DR
    uC = getPieceColor(DOWN, 5); dC = getPieceColor(RIGHT, 7);
    if ((uC == topC || uC == botC) || ((uC == Color::BLUE || uC == Color::GREEN) && !(dC == topC || dC == botC))) {oBitset |= (1 << idx);}
    idx++;
    // DB
    uC = getPieceColor(DOWN, 7); dC = getPieceColor(BACK, 7);
    if ((uC == topC || uC == botC) || ((uC == Color::BLUE || uC == Color::GREEN) && !(dC == topC || dC == botC))) {oBitset |= (1 << idx);}
    idx++;
    // DL
    uC = getPieceColor(DOWN, 3); dC = getPieceColor(LEFT, 7);
    if ((uC == topC || uC == botC) || ((uC == Color::BLUE || uC == Color::GREEN) && !(dC == topC || dC == botC))) {oBitset |= (1 << idx);}
    idx++;

    // Edges in E-slice
    // First edge
    int fC = getPieceColor(FRONT, 5); int bC = getPieceColor(RIGHT, 3);
    if ((fC == topC || fC == botC) || ((fC == Color::BLUE || fC == Color::GREEN) && !(bC == topC || bC == botC))) {oBitset |= (1 << idx);}
    idx++;

    fC = getPieceColor(FRONT, 3); bC = getPieceColor(LEFT, 5);
    if ((fC == topC || fC == botC) || ((fC == Color::BLUE || fC == Color::GREEN) && !(bC == topC || bC == botC))) {oBitset |= (1 << idx);}
    idx++;

    fC = getPieceColor(BACK, 3); bC = getPieceColor(RIGHT, 5);
    if ((fC == topC || fC == botC) || ((fC == Color::BLUE || fC == Color::GREEN) && !(bC == topC || bC == botC))) {oBitset |= (1 << idx);}
    idx++;

    fC = getPieceColor(BACK, 5); bC = getPieceColor(LEFT, 3);
    if ((fC == topC || bC == botC) || ((fC == Color::BLUE || bC == Color::GREEN) && !(bC == topC || bC == botC))) {oBitset |= (1 << idx);}
    idx++;

    return oBitset;
}


std::string moveToString(Move move) {
    switch (move) {
        case U: return "U";
        case U_PRIME: return "U'";
        case U2: return "U2";
        case D: return "D";
        case D_PRIME: return "D'";
        case D2: return "D2";
        case R: return "R";
        case R_PRIME: return "R'";
        case R2: return "R2";
        case L: return "L";
        case L_PRIME: return "L'";
        case L2: return "L2";
        case F: return "F";
        case F_PRIME: return "F'";
        case F2: return "F2";
        case B: return "B";
        case B_PRIME: return "B'";
        case B2: return "B2";
        case M: return "M";
        case M_PRIME: return "M'";        
    }
    return "";
}

 std::string movesToString(const std::vector<Move>& moves) {
    std::string result = "";
    for (int i = 0; i < moves.size(); ++i) {
        result += moveToString(moves[i]) + " ";
    }

    if (moves.size() > 0) 
    result += moves[moves.size()-1];
    return result;
}


Cube::Cube() {
    memset(m_faces, 0, sizeof(m_faces));

    for (int f = 0; f <= BACK; ++f) {
        for (int i = 0; i < 9; ++i) {
            setPieceColor(f, i, f);
        }
    }
}


void Cube::applyMove(Move move) {
    switch (move) {
        case U: rotateU(); break;
        case U2: rotateU(); rotateU(); break;
        case U_PRIME: rotateUPrime(); break;
        case D: rotateD(); break;
        case D2: rotateD(); rotateD(); break;
        case D_PRIME: rotateDPrime(); break;
        case R: rotateR(); break;
        case R2: rotateR(); rotateR(); break;
        case R_PRIME: rotateRPrime(); break;
        case L: rotateL(); break;
        case L2: rotateL(); rotateL(); break;
        case L_PRIME: rotateLPrime(); break;
        case F: rotateF(); break;
        case F2: rotateF(); rotateF(); break;
        case F_PRIME: rotateFPrime(); break;
        case B: rotateB(); break;
        case B2: rotateB(); rotateB(); break;
        case B_PRIME: rotateBPrime(); break;
        case M: rotateLPrime(); rotateR(); break;
        case M_PRIME: rotateL(); rotateRPrime(); break;
        default: break;
    }
}


void Cube::applyMoves(const std::vector<Move>& moves) {
    for (auto& move : moves) {
        applyMove(move);
    }
}


bool Cube::haveColor(Color color, int idx1, int idx2, int idx3, int idx4) {
    return getPieceColor(idx1 / 9, idx1 % 9)
        == getPieceColor(idx2 / 9, idx2 % 9)
        && getPieceColor(idx2 / 9, idx2 % 9)
        == getPieceColor(idx3 / 9, idx3 % 9)
        && getPieceColor(idx3 / 9, idx3 % 9)
        == getPieceColor(idx4 / 9, idx4 % 9)
        && getPieceColor(idx2 / 9, idx2 % 9) == color;
}


bool Cube::haveColor(Color color, int idx1, int idx2) {
    return getPieceColor(idx1 / 9, idx1 % 9)
        == getPieceColor(idx2 / 9, idx2 % 9)
        && getPieceColor(idx2 / 9, idx2 % 9)
        == color;
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
        int b6 = getPieceColor(BACK, 6-i*3);
        int d2 = getPieceColor(DOWN, 2 + i*3);
        setPieceColor(FRONT, 2 + i*3, d2);
        setPieceColor(UP, 2 + i*3, f2);
        setPieceColor(BACK, 6-i*3, u2);
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
    permute(DOWN, 0,2,8,6);
    permute(DOWN, 1,5,7,3);
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