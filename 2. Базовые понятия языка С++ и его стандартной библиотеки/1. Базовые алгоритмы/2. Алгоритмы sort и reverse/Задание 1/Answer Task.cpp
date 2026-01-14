#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main() {
    
    vector<pair<int, string>> people;
    int count;
    
    cin >> count;
    
    for (int i = 0; i < count; ++i) {
        string name;
        int age;
        cin >> name >> age;
        people.push_back({age, name});
    }

    sort(people.begin(), people.end());
    reverse(people.begin(), people.end());

    for (const auto& person : people) {
        cout << person.second << endl;
    }
}