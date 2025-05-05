#include <fstream>
#include <time.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "nlohmann/json.hpp"
#define q 2
#define numberOfElements 19
#define exponent 1

using namespace std;
using json = nlohmann::json;

void zapiszDoJSON(const int& sum, const vector<vector<int>>& matrix, const string& nazwaPliku) {
    json j;
    j["sum"] = sum;
    j["matrix"] = matrix;

    std::ofstream plik(nazwaPliku);
    if (plik.is_open()) {
        plik << j.dump(4);
        plik.close();
        cout << "Dane zostaly zapisane do pliku " << nazwaPliku << std::endl;
    } else {
        cerr << "Nie mozna otworzyc pliku do zapisu." << std::endl;
    }
}

void printVector(vector<vector<int>> matrix)
{
    for(int i=0; i<matrix.size()/100; i++)
    {
        for(int j=0; j<matrix[i].size()/100; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

int generator(vector<vector<int>> &matrix, int n, int scale, int determineSum, int subSets)
{
    int sum = 0;
    vector<int> blank={};
    int first = rand()%n;
    int second = rand()%n;
    do
    {
        second = rand()%n;
    } while (second == first);
    int target = 0;
    for(int i=0; i<n; i++)
    {
        matrix.push_back(blank);
        for(int j=0; j<n; j++)
        {
            int element = (int)(pow(10,scale+2)*rand()/RAND_MAX);
            //cout << element << endl;
            sum += element;
            if(determineSum && (i == second || i == first) && 10*rand()/RAND_MAX >=5)
                target += element;
            matrix[i].push_back(element);
        }
    }
    if(determineSum)
    {
        if(!target)
            target += (matrix[first][0] + matrix[second][0]);
        return target;
    }
    return int(subSets*sum/n*(0.8f+0.4f*rand()/RAND_MAX));
}

int main()
{
    srand(time(NULL));
    for(int det=0; det<2; det++)
        for(int no = 0; no < 20; no++)
        {
            vector<vector<int>> matrix={};
            int s = generator(matrix, numberOfElements, exponent, det, q);
            string ss = "matrix_" + to_string(numberOfElements) + "_" + to_string(exponent) + "_" + to_string(no+1) + "_" + to_string(det) + ".json";
            zapiszDoJSON(s, matrix, ss);
            printVector(matrix);
            cout << endl << s << endl;
        }
    return 0;
}
