#include <iostream>
#include <unordered_map>


using namespace std;

int main() {
    
    int number_of_pairs;
    int origin, des;

    while (1) {

        cin >> number_of_pairs;
        unordered_map<int, unordered_map<int, int>> travels;
        int possible = 1;


        if (number_of_pairs == 0) {
            break;
        }

        for (int i = 0; i < number_of_pairs;i++) {
            cin >> origin;
            cin >> des;
            travels[origin][des]++;
        }

        for (auto from_travles : travels) {
            int fr = from_travles.first;
            for (auto to_des : from_travles.second) {
                int to = to_des.first;

                int counter = to_des.second;

                if (travels[to][fr] < counter) {
                    possible = 0;
                    break;
                }
            }
            if (!possible) {
                break;
            }
        }

        if (possible==1) {
            cout << "YES" << endl;
        }
        if (possible == 0) {
            cout << "NO" << endl;

        }
    }
    return 0;
}
