#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int N = 8;

string tenMon[N] = {
    "Lap trinh C",
    "Cau truc du lieu",
    "Co so du lieu",
    "Mang may tinh",
    "Toan roi rac",
    "Lap trinh Java",
    "Thiet ke Web",
    "He dieu hanh"
};

vector<int> ke[N];

void themCanh(int u, int v) {
    ke[u].push_back(v);
    ke[v].push_back(u);
}

int bac(int u) {
    return (int)ke[u].size();
}

int main() {
    themCanh(0, 1);
    themCanh(0, 2);
    themCanh(0, 4);
    themCanh(1, 2);
    themCanh(1, 5);
    themCanh(2, 3);
    themCanh(2, 6);
    themCanh(3, 4);
    themCanh(3, 7);
    themCanh(4, 5);
    themCanh(5, 6);
    themCanh(6, 7);

    vector<int> thuTu(N);

    for (int i = 0; i < N; i++) {
        thuTu[i] = i;
    }

    sort(thuTu.begin(), thuTu.end(),
        [](int a, int b) {
            if (bac(a) != bac(b))
                return bac(a) > bac(b);
            return a < b;
        }
    );

    cout << "BAC CAC DINH:\n";

    for (int u : thuTu) {
        cout << char('A' + u) << " - "
             << tenMon[u] << ": "
             << bac(u) << "\n";
    }

    vector<int> mau(N, 0);
    int soMau = 0;

    for (int u : thuTu) {
        vector<bool> daDung(N + 1, false);

        for (int v : ke[u]) {
            if (mau[v] != 0) {
                daDung[mau[v]] = true;
            }
        }

        int c = 1;

        while (daDung[c]) {
            c++;
        }

        mau[u] = c;
        soMau = max(soMau, c);
    }

    cout << "\nTHU TU TO MAU:\n";

    for (int u : thuTu) {
        cout << char('A' + u) << " - "
             << tenMon[u]
             << ": Ca thi " << mau[u] << "\n";
    }

    cout << "\nLICH THI:\n";

    for (int c = 1; c <= soMau; c++) {
        cout << "Ca thi " << c << ": ";

        bool dauTien = true;

        for (int u = 0; u < N; u++) {
            if (mau[u] == c) {
                if (!dauTien) {
                    cout << ", ";
                }

                cout << char('A' + u)
                     << " - " << tenMon[u];

                dauTien = false;
            }
        }

        cout << "\n";
    }

    cout << "\nTong so ca thi: " << soMau << "\n";

    bool hopLe = true;

    for (int u = 0; u < N; u++) {
        for (int v : ke[u]) {
            if (mau[u] == mau[v]) {
                hopLe = false;
                break;
            }
        }
    }

    cout << "Lich thi hop le: "
         << (hopLe ? "Co" : "Khong") << "\n";

    return 0;
}
