#include <iostream>
#include <vector>

void PrintWorryCount(const std::vector<bool>& is_nervous) {
    // подсчитываем количество элементов в векторе is_nervous, равных true
    int worry_count = 0;
    for (bool status : is_nervous) {
        if (status) {
            ++worry_count;
        }
    }
    std::cout << worry_count << '\n';
}

int main() {
    // не меняйте содержимое функции main
    PrintWorryCount({true, true, false, true});
    return 0;
}