
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <climits>
using namespace std;

const int SO_LUAN_VAN = 12;
const int SO_NGUOI = 4;

struct LuanVan {
    int ma;
    int soTrang;
};



LuanVan luanVan[SO_LUAN_VAN] = {
    {1, 205}, {2, 135}, {3, 80}, {4, 90},
    {5, 70}, {6, 110}, {7, 60}, {8, 85},
    {9, 200}, {10, 140}, {11, 170}, {12, 120}
};

int tocDo[SO_NGUOI] = {8, 8, 8, 4};
int soNguoi;
int tongTai[SO_NGUOI];
int soLuong[SO_NGUOI];

int phanCong[SO_NGUOI][SO_LUAN_VAN];
int phanCongTotNhat[SO_NGUOI][SO_LUAN_VAN];
int soLuongTotNhat[SO_NGUOI];

long long thoiGianTotNhat = LLONG_MAX;

void quayLui(int viTri) {
    if (viTri == SO_LUAN_VAN) {
        int thoiGianLonNhat = 0;

        for (int i = 0; i < soNguoi; i++) {
            thoiGianLonNhat = max(thoiGianLonNhat, tongTai[i]);
        }

        if (thoiGianLonNhat < thoiGianTotNhat) {
            thoiGianTotNhat = thoiGianLonNhat;

            for (int i = 0; i < soNguoi; i++) {
                soLuongTotNhat[i] = soLuong[i];

                for (int j = 0; j < soLuong[i]; j++) {
                    phanCongTotNhat[i][j] = phanCong[i][j];
                }
            }
        }

        return;
    }

    int maLuanVan = luanVan[viTri].ma;
    int soTrang = luanVan[viTri].soTrang;


    for (int i = 0; i < soNguoi; i++) {
        bool trungTai = false;

        for (int j = 0; j < i; j++) {
            if (tocDo[i] == tocDo[j] && tongTai[i] == tongTai[j]) {
                trungTai = true;
                break;
            }
        }

        if (trungTai) {
            continue;
        }

        int taiMoi = soTrang * 8 / tocDo[i];
        int taiCu = tongTai[i];
        tongTai[i] += taiMoi;

        int thoiGianTam = 0;
        for (int j = 0; j < soNguoi; j++) {
            thoiGianTam = max(thoiGianTam, tongTai[j]);
        }

        if (thoiGianTam < thoiGianTotNhat) {
            phanCong[i][soLuong[i]] = maLuanVan;
            soLuong[i]++;

            quayLui(viTri + 1);

            soLuong[i]--;
        }

        tongTai[i] = taiCu;
    }
}

void giaiBaiToan(int soNguoiThamGia) {
    soNguoi = soNguoiThamGia;
    thoiGianTotNhat = LLONG_MAX;

    for (int i = 0; i < SO_NGUOI; i++) {
        tongTai[i] = 0;
        soLuong[i] = 0;
        soLuongTotNhat[i] = 0;
    }

    sort(luanVan, luanVan + SO_LUAN_VAN,
        [](LuanVan a, LuanVan b) {
            return a.soTrang > b.soTrang;
        });

    quayLui(0);

    cout << "\nPhuong an phan cong:\n";

    for (int i = 0; i < soNguoi; i++) {
        int tongTrang = 0;

        cout << (i < 3 ? "Nhan vien " : "Quan ly ");
        cout << (i < 3 ? i + 1 : 1) << ": ";

        for (int j = 0; j < soLuongTotNhat[i]; j++) {
            int ma = phanCongTotNhat[i][j];

            cout << "Q" << ma;
            if (j < soLuongTotNhat[i] - 1) {
                cout << ", ";
            }

            for (int k = 0; k < SO_LUAN_VAN; k++) {
                if (luanVan[k].ma == ma) {
                    tongTrang += luanVan[k].soTrang;
                    break;
                }
            }
        }

        cout << "\nTong so trang: " << tongTrang;
        cout << "\nThoi gian: "
             << (double)tongTrang / tocDo[i] << " gio\n\n";
    }

    cout << fixed << setprecision(3);
    cout << "Thoi gian hoan thanh toan bo: "
         << (double)thoiGianTotNhat / 8 << " gio\n";
}

int main() {
    cout << "3 nhan vien: \n";
    giaiBaiToan(3);
    
    cout<<"===============================\n";

    cout << "3 nhan vien va 1 quan ly: \n";
    giaiBaiToan(4);

    return 0;
}
