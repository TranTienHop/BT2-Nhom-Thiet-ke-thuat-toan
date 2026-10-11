// Bai 2: Xac dinh thu tu nhan ma tran (Matrix Chain Multiplication)
// Phuong phap: Quy hoach dong (Bottom-up)
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <climits>
using namespace std;

const int MAX_N = 30;       // so ma tran toi da
const int MAX_D = 1000;     // kich thuoc toi da cua moi chieu

int n;                              // so ma tran
vector<long long> p;                // p[0..n]: ma tran Ai co kich thuoc p[i-1] x p[i]
vector<vector<long long>> m;        // m[i][j]: so phep nhan toi thieu de nhan Ai..Aj
vector<vector<int>> s;              // s[i][j]: vi tri k tai do chia chuoi Ai..Aj

// Tinh bang m va s theo do dai chuoi tang dan
void quyHoachDong() {
    m.assign(n + 1, vector<long long>(n + 1, 0));
    s.assign(n + 1, vector<int>(n + 1, 0));

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            m[i][j] = LLONG_MAX;
            for (int k = i; k < j; k++) {
                long long cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
}

// Dung lai cach dat ngoac toi uu tu bang s
string datNgoac(int i, int j) {
    if (i == j)
        return "A" + to_string(i);
    int k = s[i][j];
    return "(" + datNgoac(i, k) + " x " + datNgoac(k + 1, j) + ")";
}

void inBang() {
    cout << "\nBang m[i][j] (so phep nhan toi thieu):\n";
    cout << setw(6) << "";
    for (int j = 1; j <= n; j++) cout << setw(10) << ("j=" + to_string(j));
    cout << "\n";
    for (int i = 1; i <= n; i++) {
        cout << setw(6) << ("i=" + to_string(i));
        for (int j = 1; j <= n; j++) {
            if (j < i) cout << setw(10) << "-";
            else cout << setw(10) << m[i][j];
        }
        cout << "\n";
    }

    cout << "\nBang s[i][j] (vi tri chia k):\n";
    cout << setw(6) << "";
    for (int j = 1; j <= n; j++) cout << setw(10) << ("j=" + to_string(j));
    cout << "\n";
    for (int i = 1; i <= n; i++) {
        cout << setw(6) << ("i=" + to_string(i));
        for (int j = 1; j <= n; j++) {
            if (j <= i) cout << setw(10) << "-";
            else cout << setw(10) << s[i][j];
        }
        cout << "\n";
    }
}

int main() {
    cout << "Nhap so ma tran n (1 - " << MAX_N << "): ";
    if (!(cin >> n) || n < 1 || n > MAX_N) {
        cout << "So ma tran khong hop le!\n";
        return 0;
    }

    p.assign(n + 1, 0);
    cout << "Nhap " << n + 1 << " kich thuoc p0 p1 ... p" << n
         << " (1 - " << MAX_D << "): ";
    for (int i = 0; i <= n; i++) {
        if (!(cin >> p[i]) || p[i] < 1 || p[i] > MAX_D) {
            cout << "Kich thuoc khong hop le!\n";
            return 0;
        }
    }

    cout << "\nCac ma tran:\n";
    for (int i = 1; i <= n; i++)
        cout << "A" << i << " : " << p[i - 1] << " x " << p[i] << "\n";

    quyHoachDong();
    inBang();

    cout << "\nThu tu nhan toi uu: " << datNgoac(1, n) << "\n";
    cout << "So phep nhan toi thieu: " << m[1][n] << "\n";
    return 0;
}
