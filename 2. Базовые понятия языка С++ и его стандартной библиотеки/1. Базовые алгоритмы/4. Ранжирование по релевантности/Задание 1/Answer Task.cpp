#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

double Average(const vector<int>& xs) {
    if (xs.empty()) {
        return 0;
    }
    return accumulate(xs.begin(), xs.end(), 0.0) / xs.size();
}

int main() {
    cout << Average({}) << endl;
    cout << Average({2, 5}) << endl;
    cout << Average({7, 2, 6}) << endl;
}