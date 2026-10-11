//CAU 9B: AP DUNG THUAT TOAN DAN KIEN CHO BAI 7 (BAI 2 PHAN HEURISTIC)
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const int NUM_PERSONS = 3;  // m = 3 nguoi
const int NUM_JOBS = 8;     // n = 8 cong viec
const int NUM_ANTS = 15;
const int MAX_ITER = 60;
const double ALPHA = 1.0;
const double BETA = 2.0;
const double RHO = 0.5;
const double Q = 100.0;


int t[NUM_PERSONS][NUM_JOBS] = {
    {5, 5, 4, 10, 8, 6, 12, 8},
    {7, 5, 7, 3, 9, 7, 8, 5},
    {10, 6, 7, 8, 10, 6, 5, 7}
};


double pheromone[NUM_JOBS][NUM_PERSONS];

int selectPersonForJob(int job, const vector<int>& currentWorkloads) {
    vector<double> probs(NUM_PERSONS, 0.0);
    double sum = 0.0;

    for (int p = 0; p < NUM_PERSONS; p++) {
        double expectedWorkload = currentWorkloads[p] + t[p][job];
        double eta = 1.0 / expectedWorkload;
        probs[p] = pow(pheromone[job][p], ALPHA) * pow(eta, BETA);
        sum += probs[p];
    }

    double r = ((double)rand() / RAND_MAX) * sum;
    double currentSum = 0.0;
    for (int p = 0; p < NUM_PERSONS; p++) {
        currentSum += probs[p];
        if (currentSum >= r) return p;
    }
    return NUM_PERSONS - 1;
}

int main() {
    srand(time(NULL));

    
    for (int j = 0; j < NUM_JOBS; j++) {
        for (int p = 0; p < NUM_PERSONS; p++) {
            pheromone[j][p] = 1.0;
        }
    }

    int bestMakespan = 1e9;
    vector<int> bestAssignment(NUM_JOBS);

    for (int iter = 0; iter < MAX_ITER; iter++) {
        vector<vector<int> > antAssignments(NUM_ANTS, vector<int>(NUM_JOBS));
        vector<int> antMakespans(NUM_ANTS, 0);

        for (int k = 0; k < NUM_ANTS; k++) {
            vector<int> workloads(NUM_PERSONS, 0);

            for (int j = 0; j < NUM_JOBS; j++) {
                int chosenPerson = selectPersonForJob(j, workloads);
                antAssignments[k][j] = chosenPerson;
                workloads[chosenPerson] += t[chosenPerson][j];
            }

            int makespan = 0;
            for (int p = 0; p < NUM_PERSONS; p++) {
                if (workloads[p] > makespan) makespan = workloads[p];
            }
            antMakespans[k] = makespan;

            if (makespan < bestMakespan) {
                bestMakespan = makespan;
                bestAssignment = antAssignments[k];
            }
        }

       
        for (int j = 0; j < NUM_JOBS; j++) {
            for (int p = 0; p < NUM_PERSONS; p++) {
                pheromone[j][p] *= (1.0 - RHO);
            }
        }

       
        for (int k = 0; k < NUM_ANTS; k++) {
            for (int j = 0; j < NUM_JOBS; j++) {
                int p = antAssignments[k][j];
                pheromone[j][p] += Q / antMakespans[k];
            }
        }
    }

    cout << "=== THUAT TOAN DAN KIEN (ACO) CHO PHAN CONG CONG VIEC (BAI 7) ===\n";
    cout << "Thoi gian hoan thanh tat ca cong viec nho nhat (Makespan): " << bestMakespan << "\n\n";
    
    vector<int> totalTime(NUM_PERSONS, 0);
    for (int p = 0; p < NUM_PERSONS; p++) {
        cout << "Nguoi " << p + 1 << " lam cac viec: ";
        for (int j = 0; j < NUM_JOBS; j++) {
            if (bestAssignment[j] == p) {
                cout << "Viec " << j + 1 << " (" << t[p][j] << "h)  ";
                totalTime[p] += t[p][j];
            }
        }
        cout << "=> Tong: " << totalTime[p] << "h\n";
    }

    return 0;
}
