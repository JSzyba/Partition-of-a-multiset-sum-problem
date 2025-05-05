#include <iostream>
#include <fstream>
#include <vector>
#include "nlohmann/json.hpp"
#define setSize 20
#define scale 1


using namespace std;
using json=nlohmann::json;

void printSubset(const vector<int>& subset, const vector<int>& vectorIndexes, const vector<vector<int>>& set) {
    vector<bool> contributes;
    for(int i=0; i<vectorIndexes.size(); i++)
        contributes.push_back(false);
    for(int i=0; i<subset.size(); i++)
        for(int j=0; j<vectorIndexes.size(); j++)
            for(int k=0; k<set[vectorIndexes[j]].size(); k++)
                if( !contributes[j] && set[vectorIndexes[j]][k] == subset[i])
                    contributes[j] = true;
    cout << "Elementy z wektorow: ";
    for (int num : subset) {
        cout << num << " ";
    }
    cout << "(indeksy: ";
    for (int i=0; i<vectorIndexes.size(); i++) {
        if(contributes[i])
            cout << vectorIndexes[i] << " ";
    }
    cout << ")" << endl;
}

vector<vector<int>> wczytajZJSON(const string& nazwaPliku, int &sum) {
    vector<vector<int>> wynik;

    ifstream plik(nazwaPliku);
    if (plik.is_open()) {
        json j;
        plik >> j;

        if (j.contains("sum") && j.contains("matrix")) {
            sum = j["sum"];
            for (const auto& wiersz : j["matrix"]) {
                vector<int> tempRow;
                for (const auto& element : wiersz) {
                    tempRow.push_back(element);
                }
                wynik.push_back(tempRow);
            }
        } else {
            cerr << "Blad: Nieprawidlowy format danych w pliku JSON." << endl;
        }

        plik.close();
    } else {
        cerr << "Nie mozna otworzyc pliku do odczytu." << endl;
    }

    return wynik;
}

bool isSubsetSum(const vector<int>& arr, int targetSum, vector<int>& subset) {
    int n = arr.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(targetSum + 1, false));

    for (int i = 0; i <= n; ++i) {
        dp[i][0] = true;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= targetSum; ++j) {
            if (arr[i - 1] <= j) {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i - 1]];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    if (!dp[n][targetSum]) {
        return false;
    }

    int i = n, j = targetSum;
    while (i > 0 && j > 0) {
        if (dp[i - 1][j]) {
            --i;
        } else {
            subset.push_back(arr[i - 1]);
            j -= arr[i - 1];
            --i;
        }
    }
    return true;
}

void subsetSumWithLimit(const vector<vector<int>>& matrix, int targetSum, int q) {
    int n = matrix.size();
    vector<int> subset;
    for (int mask = 0; mask < (1 << n); ++mask) {
        vector<int> temp;
        vector<int> vectorIndexes;

        for (int j = 0; j < n; ++j) {
            if ((mask & (1 << j)) != 0) {
                temp.insert(temp.end(), matrix[j].begin(), matrix[j].end());
                vectorIndexes.push_back(j);
            }
        }
        if (temp.size() > 0 && temp.size() <= q*matrix[0].size()) {
            if (isSubsetSum(temp, targetSum, subset)) {
                //printSubset(subset, vectorIndexes, matrix);
                subset.clear();
            }
        }
    }
}

int main() {
    for(int i=0; i<2; i++)
    {
        for(int no=1; no<=20; no++)
        {
            string name = "matrix_" + to_string(setSize) + "_" + to_string(scale) + "_" + to_string(no)+"_" + to_string(i) + ".json";
            clock_t timeStart, timeEnd;
            int targetSum = 0;
            vector<vector<int>> matrix = wczytajZJSON(name, targetSum);
            int q = 2;
            cout << "Szukana suma: " << targetSum << endl;
            cout << "Liczba wektorow branych pod uwage: <= " << q << endl;
            timeStart = clock();
            subsetSumWithLimit(matrix, targetSum, q);
            timeEnd = clock();
            double timeUsed = (double)(timeEnd-timeStart)/CLOCKS_PER_SEC;
            cout << timeUsed << endl;
        }
    }
    return 0;
}
