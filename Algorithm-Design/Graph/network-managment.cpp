#include <iostream>
#include <vector>
#include <limits>
#include<string>


using namespace std;


int main() {
    const long int inf = numeric_limits<int>::max();

    vector<vector<string>> adjmatrixstrings;
    string temp;
    int dimentions;
    cin >> dimentions;
    adjmatrixstrings.resize(dimentions, vector<string>(dimentions));
    vector<vector<double>> adjmatrix(dimentions, vector<double>(dimentions));
    for (int i = 0; i < dimentions; i++) {
        for (int j = 0; j < dimentions; j++) {
            cin >> temp;
            adjmatrixstrings[i][j] = temp;
        }
    }


    for (int i = 0; i < dimentions; ++i) {
        for (int j = 0; j < dimentions; ++j) {
            if (adjmatrixstrings[i][j] == "inf") {
                adjmatrix[i][j] = -1;
            }
            else {
                adjmatrix[i][j] = stoi(adjmatrixstrings[i][j].c_str());
            }
        }
    }






    for (int k = 0; k < dimentions; ++k) {
        for (int i = 0; i < dimentions; ++i) {
            for (int j = 0; j < dimentions; ++j) {
                if ((adjmatrix[i][j] > adjmatrix[i][k] + adjmatrix[k][j] ||adjmatrix[i][j]==-1) && adjmatrix[k][j] != -1 && adjmatrix[i][k] != -1) {

                    adjmatrix[i][j] = adjmatrix[i][k] + adjmatrix[k][j];
                }
            }
        }
    }


    for (int i = 0; i < dimentions; i++) {
        for (int j = 0; j < dimentions; j++) {
            if (adjmatrix[i][j] == -1) {
                cout << "inf ";
            }
            else {
                cout << adjmatrix[i][j] << " ";
            }
        }
        cout << endl;
    }
        
    return 0;
}
