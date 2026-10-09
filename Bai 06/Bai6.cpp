#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

struct Job {
    int id;
    int time;
};

bool compareJobs(const Job& a, const Job& b) {
    return a.time > b.time;
}

void solveLPT(int n, int m, const vector<int>& times) {
    vector<Job> jobs(n);
    for (int i = 0; i < n; ++i) {
        jobs[i] = {i + 1, times[i]};
    }

    sort(jobs.begin(), jobs.end(), compareJobs);

    vector<vector<Job>> machine_jobs(m);
  
    vector<int> machine_times(m, 0);

    for (int i = 0; i < n; ++i) {
        int min_machine = 0;
        for (int j = 1; j < m; ++j) {
            if (machine_times[j] < machine_times[min_machine]) {
                min_machine = j;
            }
        }
        
        machine_jobs[min_machine].push_back(jobs[i]);
        machine_times[min_machine] += jobs[i].time;
    }

    cout << "=== KET QUA PHAN CONG (HEURISTIC LPT) ===" << endl;
    int max_makespan = 0;
    for (int j = 0; j < m; ++j) {
        cout << "May " << j + 1 << " (Tong thoi gian = " << machine_times[j] << "): ";
        for (const auto& job : machine_jobs[j]) {
            cout << "J" << job.id << "(" << job.time << ") ";
        }
        cout << endl;
        max_makespan = max(max_makespan, machine_times[j]);
    }

    cout << "\n-> Thoi gian hoan thanh tat ca cong viec (Makespan): " << max_makespan << endl;
}

int main() {
    int n = 12;
    int m = 3;
    vector<int> times = {5, 7, 15, 3, 18, 40, 15, 7, 20, 14, 6, 10};

    solveLPT(n, m, times);

    return 0;
}