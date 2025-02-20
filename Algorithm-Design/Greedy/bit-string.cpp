#include <iostream>
#include <vector>
#include <algorithm>
#include<string>

using namespace std;

vector<string> strings;


void fun(int n,int h,string prefix) {
    if (h == 0) {
        strings.push_back(prefix + string(n-prefix.size(),'0'));
    }
    else {
        if (n == prefix.size()) {
            strings.push_back(prefix);
        }

        else {
            if (h > 0) {
                fun(n,h-1,prefix+"1");
            }
            fun(n,h,prefix+"0");
        }
    }
}

int main() {
    char trash;
    int test_cases,n,h;
    vector<string> results;
    cin >> test_cases;

    for (int t = 0; t < test_cases; ++t) {
        cin.ignore();
        cin >> n;
        cin >> h;

        fun(n,h,"");

        sort(strings.begin(), strings.end());
        for (auto temp_result : strings) {
            if (temp_result.length() == n) {
                if (count(temp_result.begin(), temp_result.end(), '1') == h) {
                    results.push_back(temp_result);
                }
            }

               
        }

        for (auto result : results) {
            cout << result << endl;
        }
        strings.clear();
        results.clear();
    }

    return 0;
}
