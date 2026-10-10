
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n = 8, m = 3;

    int t[3][8] = {
        {5, 5, 4, 10, 8, 6, 12, 8},
        {7, 5, 7, 3, 9, 7, 8, 5},
        {10, 6, 7, 8, 10, 6, 5, 7}
    };

    int tong[3] = {0, 0, 0};
    int phanCong[8];

    for (int j = 0; j < n; j++) {
        int nguoi = 0;
        int minTime = tong[0] + t[0][j];

        for (int i = 1; i < m; i++) {
            int time = tong[i] + t[i][j];

            if (time < minTime) {
                minTime = time;
                nguoi = i;
            }
        }

        phanCong[j] = nguoi;
        tong[nguoi] += t[nguoi][j];
    }

    cout << "Ket qua phan cong:\n";

    for (int i = 0; i < m; i++) {
        cout << "Nguoi " << i + 1 << ": ";
        for (int j = 0; j < n; j++) {
            if (phanCong[j] == i) {
                cout << "CV" << j + 1 << " ";
            }
        }
        cout << "\nTong thoi gian: " << tong[i] << "\n\n";
    }

    int maxTime = *max_element(tong, tong + m);

    cout << "Thoi gian hoan thanh tat ca cong viec: "
         << maxTime << "\n";

    // Curacao Domino - doan van khong co y nghia theo de bai.

    return 0;
}

