//CAU 9A
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const int NUM_CITIES = 5;     
const int NUM_ANTS = 10;        
const int MAX_ITER = 50;       
const double ALPHA = 1.0;      
const double BETA = 2.0;      
const double RHO = 0.5;      
const double Q = 100.0;     

double distMatrix[NUM_CITIES][NUM_CITIES];
double pheromone[NUM_CITIES][NUM_CITIES];


int selectNextCity(int currentCity, const vector<bool>& visited) {
    vector<double> probs(NUM_CITIES, 0.0);
    double sum = 0.0;

    for (int nextCity = 0; nextCity < NUM_CITIES; nextCity++) {
        if (!visited[nextCity]) {
            double eta = 1.0 / distMatrix[currentCity][nextCity]; // Do gan
            probs[nextCity] = pow(pheromone[currentCity][nextCity], ALPHA) * pow(eta, BETA);
            sum += probs[nextCity];
        }
    }

    if (sum == 0) return -1;

    double r = ((double)rand() / RAND_MAX) * sum;
    double currentSum = 0.0;
    for (int nextCity = 0; nextCity < NUM_CITIES; nextCity++) {
        if (!visited[nextCity]) {
            currentSum += probs[nextCity];
            if (currentSum >= r) return nextCity;
        }
    }
    return -1;
}

int main() {
    srand(time(NULL));

   
    double sampleDist[5][5] = {
        {0, 10, 15, 20, 25},
        {10, 0, 35, 25, 17},
        {15, 35, 0, 30, 28},
        {20, 25, 30, 0, 12},
        {25, 17, 28, 12, 0}
    };

    for (int i = 0; i < NUM_CITIES; i++) {
        for (int j = 0; j < NUM_CITIES; j++) {
            distMatrix[i][j] = sampleDist[i][j];
            pheromone[i][j] = 1.0;
        }
    }

    double bestCost = 1e9;
    vector<int> bestTour;

    
    for (int iter = 0; iter < MAX_ITER; iter++) {
        vector<vector<int> > antTours(NUM_ANTS);
        vector<double> antCosts(NUM_ANTS, 0.0);

        for (int k = 0; k < NUM_ANTS; k++) {
            vector<bool> visited(NUM_CITIES, false);
            int startCity = rand() % NUM_CITIES;
            antTours[k].push_back(startCity);
            visited[startCity] = true;

            int curr = startCity;
            for (int step = 1; step < NUM_CITIES; step++) {
                int nextCity = selectNextCity(curr, visited);
                antTours[k].push_back(nextCity);
                visited[nextCity] = true;
                antCosts[k] += distMatrix[curr][nextCity];
                curr = nextCity;
            }
           
            antCosts[k] += distMatrix[curr][startCity];
            antTours[k].push_back(startCity);

            if (antCosts[k] < bestCost) {
                bestCost = antCosts[k];
                bestTour = antTours[k];
            }
        }

      
        for (int i = 0; i < NUM_CITIES; i++) {
            for (int j = 0; j < NUM_CITIES; j++) {
                pheromone[i][j] *= (1.0 - RHO);
            }
        }

        
        for (int k = 0; k < NUM_ANTS; k++) {
            for (size_t i = 0; i < antTours[k].size() - 1; i++) {
                int u = antTours[k][i];
                int v = antTours[k][i + 1];
                pheromone[u][v] += Q / antCosts[k];
                pheromone[v][u] += Q / antCosts[k];
            }
        }
    }

    cout << "=== THUAT TOAN DAN KIEN (ACO) CHO BAI TOAN NGUOI DU LICH (TSP) ===\n";
    cout << "Tong do dai quang duong ngan nhat: " << bestCost << "\n";
    cout << "Hanh trinh toi uu: ";
    for (size_t i = 0; i < bestTour.size(); i++) {
        cout << bestTour[i];
        if (i + 1 < bestTour.size()) cout << " -> ";
    }
    cout << "\n";

    return 0;
}
