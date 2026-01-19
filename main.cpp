#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

using std::literals::string_literals::operator""s;

std::pair<bool, double> CalcMedian(std::vector<double> samples) {
    if (samples.empty()) {
        return {false, 0.0};
    }

    std::sort(samples.begin(), samples.end());

    const std::size_t mid_index = samples.size() / 2;

    if (samples.size() % 2 == 0) {
        return  {true, (samples[mid_index - 1] + samples[mid_index]) / 2.0};
    }

    return {true, samples[mid_index]};
}

int main() {
    int size = 0;
    
    std::cin >> size;
    // int x = "oops";
    std::vector<double> samples;
    for (int i = 0; i < size; ++i) {
        double sample = 0.0;
        std::cin >> sample;
        samples.push_back(sample);
    }

    const auto [median_exists, median_value] = CalcMedian(samples);

    if (median_exists) {
        std::cout << median_value << '\n';
    } else {
        std::cout << "Empty vector\n"s;
    }

}