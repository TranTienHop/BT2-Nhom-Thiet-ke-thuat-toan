
#include <iostream>
#include <vector>
using namespace std;

// dp[72] = 1.4e18 la gia tri lon nhat con vua kieu long long
const int MAX_N = 70;

int n, k;
vector<bool> hong;
vector<long long> dp;

void quyHoachDong() {
    dp.assign(n + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        if (hong[i])
            continue;

        for (int buoc = 1; buoc <= 3; buoc++) {
            if (i - buoc >= 0)
                dp[i] += dp[i - buoc];
        }
    }
}

void inBangQuyHoachDong() {
    cout << "\nBang quy hoach dong:\n";
    for (int i = 0; i <= n; i++) {
        cout << "dp[" << i << "] = " << dp[i];
        if (i == 0)
            cout << " (mat dat)";
        else if (hong[i])
            cout << " (bac hong)";
        cout << endl;
    }
}

int main() {
    cout << "Nhap so bac thang n (1 - " << MAX_N << "): ";
    if (!(cin >> n) || n < 1 || n > MAX_N) {
        cout << "So bac thang khong hop le!\n";
        return 0;
    }

    cout << "Nhap so bac thang bi hong k (0 - " << n << "): ";
    if (!(cin >> k) || k < 0 || k > n) {
        cout << "So bac hong khong hop le!\n";
        return 0;
    }

    hong.assign(n + 1, false);
    if (k > 0)
        cout << "Nhap " << k << " vi tri bac hong (1 - " << n << "): ";

    for (int t = 0; t < k; t++) {
        int x;
        if (!(cin >> x) || x < 1 || x > n) {
            cout << "Vi tri bac hong khong hop le!\n";
            return 0;
        }
        hong[x] = true;
    }

    quyHoachDong();
    inBangQuyHoachDong();

    cout << "\nSo cach leo len dinh nui (bac " << n << "): "
         << dp[n] << endl;

    if (hong[n])
        cout << "Bac thu " << n << " bi hong nen khong the len dinh.\n";

    return 0;
}
