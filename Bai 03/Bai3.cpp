#include <iostream>
#include <vector>

using namespace std;

int m, n;
int grid[105][105];
bool visited[105][105];

int maxTreasure = -1;
vector<pair<int, int>> bestPath;
vector<pair<int, int>> currentPath;

int dx[] = {1, 0, 0, -1};
int dy[] = {0, 1, -1, 0};

bool isValid(int x, int y) {
    return (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] != -1 && !visited[x][y]);
}

void backtrack(int x, int y, int currentSum) {
    if (x == m - 1) {
        if (currentSum > maxTreasure) {
            maxTreasure = currentSum;
            bestPath = currentPath;
        }
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (isValid(nx, ny)) {
            visited[nx][ny] = true;
            currentPath.push_back({nx, ny});

            backtrack(nx, ny, currentSum + grid[nx][ny]);

            currentPath.pop_back();
            visited[nx][ny] = false;
        }
    }
}

int main() {
    cout << "Nhap so hang m va so cot n: " << flush;
    if (!(cin >> m >> n)) return 0;

    cout << "Nhap ma tran (nhap -1 cho o bi sap):\n" << flush;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            visited[i][j] = false;
        }
    }

    if (grid[0][0] == -1) {
        cout << "O xuat phat (0, 0) bi sap! Khong the bat dau nhe ban.\n";
        return 0;
    }

    visited[0][0] = true;
    currentPath.push_back({0, 0});

    backtrack(0, 0, grid[0][0]);

    if (maxTreasure == -1) {
        cout << "\nKhong co duong di hop le den hang cuoi cung!\n";
    } else {
        cout << "\nTong so kho bau lon nhat: " << maxTreasure << "\n";
        cout << "Duong di: ";
        for (size_t i = 0; i < bestPath.size(); i++) {
            cout << "(" << bestPath[i].first << ", " << bestPath[i].second << ")";
            if (i + 1 < bestPath.size()) cout << " -> ";
        }
        cout << "\n";
    }

    return 0;
}
