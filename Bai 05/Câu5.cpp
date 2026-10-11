
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int m, n;
vector<vector<int>> a;
vector<pair<int, int>> duongDi;
int dem = 0;

void quayLui(int i, int j) {
    if (i == m - 1 && j == n - 1) {
        dem++;
        cout << "Duong di " << dem << ": ";

        for (int k = 0; k < duongDi.size(); k++) {
            cout << "(" << duongDi[k].first
                 << "," << duongDi[k].second << ")";

            if (k < duongDi.size() - 1)
                cout << " -> ";
        }

        cout << endl;
        return;
    }

    if (j + 1 < n) {
        duongDi.push_back({i, j + 1});
        quayLui(i, j + 1);
        duongDi.pop_back();
    }

    if (i + 1 < m) {
        duongDi.push_back({i + 1, j});
        quayLui(i + 1, j);
        duongDi.pop_back();
    }
}

void quyHoachDong() {
    vector<vector<int>> dp(m, vector<int>(n));

    dp[0][0] = a[0][0];

    for (int j = 1; j < n; j++)
        dp[0][j] = dp[0][j - 1] + a[0][j];

    for (int i = 1; i < m; i++)
        dp[i][0] = dp[i - 1][0] + a[i][0];

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = min(dp[i - 1][j],
                           dp[i][j - 1]) + a[i][j];
        }
    }

    cout << "\nChi phi nho nhat: "
         << dp[m - 1][n - 1] << endl;

    vector<pair<int, int>> path;
    int i = m - 1;
    int j = n - 1;

    path.push_back({i, j});

    while (i != 0 || j != 0) {
        if (i == 0)
            j--;
        else if (j == 0)
            i--;
        else if (dp[i - 1][j] <= dp[i][j - 1])
            i--;
        else
            j--;

        path.push_back({i, j});
    }

    reverse(path.begin(), path.end());

    cout << "Duong di toi uu: ";
    for (int k = 0; k < path.size(); k++) {
        cout << "(" << path[k].first
             << "," << path[k].second << ")";

        if (k < path.size() - 1)
            cout << " -> ";
    }

    cout << endl;
}

int main() {
    cout << "Nhap m va n: ";
    cin >> m >> n;

    if (m <= 0 || n <= 0) {
        cout << "Kich thuoc khong hop le!";
        return 0;
    }

    a.resize(m, vector<int>(n));

    cout << "Nhap ma tran chi phi:\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    cout << "\n=== QUAY LUI ===\n";
    duongDi.push_back({0, 0});
    quayLui(0, 0);
    cout << "Tong so duong di: " << dem << endl;

    cout << "\n=== QUY HOACH DONG ===\n";
    quyHoachDong();

    return 0;
}

