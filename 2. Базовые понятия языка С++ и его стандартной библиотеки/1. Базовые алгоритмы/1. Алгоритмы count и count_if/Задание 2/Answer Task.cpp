#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


bool StartsWithA(const string& str) {
    return !str.empty() && (str[0] == 'A' || str[0] == 'a');
}


int CountStartsWithA(const vector<string>& xs) {
    
    return count_if(xs.begin(), xs.end(), StartsWithA);
}

int main() {
    // не меняйте содержимое функции main
    
    cout << CountStartsWithA({"And"s, "another"s, "one"s, "gone"s, "another"s, "one"s, "bites"s, "the"s, "dust"s}) << endl;
    return 0;
}