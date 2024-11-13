#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void processInput(char dataType, int n, int q, vector<string>& data, vector<string>& queries) {
    if (dataType == 'i') {
        vector<int> intData(n);
        for (int i = 0; i < n; ++i) {
            intData[i] = stoi(data[i]);
        }
        for (int i = 0; i < q; ++i) {
            int target = stoi(queries[i]);
            auto it = lower_bound(intData.begin(), intData.end(), target);
            if (it != intData.end() && *it == target) {
                cout << distance(intData.begin(), it) << endl;
            }
            else {
                cout << -1 << endl;
            }
        }
    }
    else {
        for (int i = 0; i < q; ++i) {
            auto it = lower_bound(data.begin(), data.end(), queries[i]);
            if (it != data.end() && *it == queries[i]) {
                cout << distance(data.begin(), it) << endl;
            }
            else {
                cout << -1 << endl;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    string dataType;
    int n, q;

    while (cin >> dataType >> n >> q) {
        char dataTypeChar = dataType[0];
        vector<string> data(n);

        for (int i = 0; i < n; ++i) {
            cin >> data[i];
        }

        vector<string> queries(q);
        for (int i = 0; i < q; ++i) {
            cin >> queries[i];
        }

        processInput(dataTypeChar, n, q, data, queries);
    }

    return 0;
}