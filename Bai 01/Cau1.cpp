#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

const int N = 8;

int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

int board[N][N];

struct Move {
    int x, y;
    int degree;
};

bool isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

int countOnwardMoves(int x, int y) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isValid(nx, ny)) {
            count++;
        }
    }
    return count;
}

bool compareMoves(const Move &a, const Move &b) {
    return a.degree < b.degree;
}

bool solveKnightTour(int x, int y, int moveCount) {
    if (moveCount == N * N) {
        return true;
    }

    vector<Move> nextMoves;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isValid(nx, ny)) {
            Move m;
            m.x = nx;
            m.y = ny;
            m.degree = countOnwardMoves(nx, ny);
            nextMoves.push_back(m);
        }
    }

    sort(nextMoves.begin(), nextMoves.end(), compareMoves);

    for (int i = 0; i < nextMoves.size(); i++) {
        int nx = nextMoves[i].x;
        int ny = nextMoves[i].y;

        board[nx][ny] = moveCount;

        if (solveKnightTour(nx, ny, moveCount + 1)) {
            return true;
        }


        board[nx][ny] = -1;
    }

    return false;
}

void printSolution() {
    cout << "--- Bang ket qua (So thu tu buoc di) ---" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(3) << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = -1;
        }
    }

    int startX, startY;
    cout << "Nhap toa do xuat phat (x y) [0-7]: ";
    cin >> startX >> startY;

    if (startX < 0 || startX >= N || startY < 0 || startY >= N) {
        cout << "Toa do khong hop le!" << endl;
        return 1;
    }

    board[startX][startY] = 0;

    if (solveKnightTour(startX, startY, 1)) {
        cout << "Da tim thay duong di!" << endl;
        printSolution();
    } else {
        cout << "Khong tim thay duong di nao!" << endl;
    }

    return 0;
}
