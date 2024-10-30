#include <iostream>
#include <vector>
using namespace std;

void generatePowerset(const vector<char>& set, vector<char>& subset, int index) {
    if (index == set.size()) {
        cout << "{";
        for (int i = 0; i < subset.size(); ++i) {
            if (i > 0) cout << ", ";
            cout << subset[i];
        }
        cout << "}" << endl;
        return;
    }
    
    generatePowerset(set, subset, index + 1);
    
    subset.push_back(set[index]);
    generatePowerset(set, subset, index + 1);
    
    subset.pop_back();
}

int main() {
    vector<char> set = {'a', 'b', 'c'};
    vector<char> subset;
    
    cout << "??:" << endl;
    generatePowerset(set, subset, 0);
    
    return 0;
}
