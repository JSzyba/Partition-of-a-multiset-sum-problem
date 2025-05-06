#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "nlohmann/json.hpp"
#define setSize 20
#define scale 1
#define marginOfError 10

using namespace std;
using json=nlohmann::json;


vector<vector<int>> wczytajZJSON(const string& nazwaPliku, int &sum) {
    vector<vector<int>> wynik;

    ifstream plik(nazwaPliku);
    if (plik.is_open()) {
        json j;
        plik >> j;

        if (j.contains("sum") && j.contains("matrix")) {
            sum = j["sum"];
            for (const auto& wiersz : j["matrix"]) {
                std::vector<int> tempRow;
                for (const auto& element : wiersz) {
                    tempRow.push_back(element);
                }
                wynik.push_back(tempRow);
            }
        } else {
            std::cerr << "Blad: Nieprawidlowy format danych w pliku JSON." << std::endl;
        }

        plik.close();
    } else {
        std::cerr << "Nie mozna otworzyc pliku do odczytu." << std::endl;
    }

    return wynik;
}


void greedySubsetSumWithLimit(const vector<vector<int>>& matrix, int targetSum, int q, int error) {
    vector<pair<int, int>> elements;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            elements.push_back({matrix[i][j], i});
        }
    }
    sort(elements.rbegin(), elements.rend());

    int currentSum = 0;
    vector<int> subset;
    vector<int> vectorCount;

    int iterator=0;
    while(abs(currentSum - targetSum) > error && iterator < elements.size()) {
            if(currentSum + elements[iterator].first > targetSum+error)
            {
                iterator++;
                continue;
            }
            if(find(vectorCount.begin(), vectorCount.end(), elements[iterator].second) != vectorCount.end())
            {
                currentSum += elements[iterator].first;
                subset.push_back(elements[iterator].first);
            }
            else if(vectorCount.size() < q)
            {
                currentSum += elements[iterator].first;
                subset.push_back(elements[iterator].first);
                vectorCount.push_back(elements[iterator].second);
            }
            if(abs(currentSum - targetSum) <= error)
                break;
            iterator++;
        }
    /*
    cout << "Wybrane elementy: ";
    for (int num : subset) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Z wektorow: ";
    sort(vectorCount.begin(), vectorCount.end());
    for(int num : vectorCount)
    {
        cout << num << " ";
    }
    cout << endl;
    cout << "Suma: " << currentSum << endl;
    */
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
            greedySubsetSumWithLimit(matrix, targetSum, q, marginOfError);
            timeEnd = clock();
            double timeUsed = (double)(timeEnd-timeStart)/CLOCKS_PER_SEC;
            cout << timeUsed << endl;
        }
    }
    return 0;
}