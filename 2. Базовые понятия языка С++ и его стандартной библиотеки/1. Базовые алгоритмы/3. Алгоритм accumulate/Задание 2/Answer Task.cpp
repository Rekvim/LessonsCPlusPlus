#include <set>
#include <string>
#include <numeric>
#include <iostream> 

using namespace std;

string FoldWithMinus(string left, string right) {
    
    return left + " -"s + right;
}

string AddStopWords(const string& query, const set<string>& stop_words) {
    
    return std::accumulate(stop_words.begin(), stop_words.end(), query, FoldWithMinus);
}

int main() {
    // Пример использования функции
    set<string> stopWords = {"of", "in"};
    cout << AddStopWords("some tasty oranges", stopWords) << endl;
    cout << AddStopWords("", stopWords) << endl;
    cout << AddStopWords("some tasty oranges", {}) << endl;
    return 0;
}
