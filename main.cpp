#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <numeric>

struct User {
    std::string name;
    int age{};
};

int sum(const std::vector<int>& vector)
{
    return std::accumulate(vector.begin(), vector.end(), 0);
}

User get_user(bool create)
{
    if (create) {
        return User{.name = "Alice", .age=30};
    }

    return User{.name = "Admin", .age = 999};
}

void print_name(const User& user)
{
    if (user.name == "") {                // ❌ лучше .empty()
        std::cout << "Empty\n";
    }
}

void process(std::vector<int>& data)
{
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (*it < 0) {
            data.erase(it);
        }
    }
}

int main()
{
    std::vector<int> values = {1, 2, 3};

    std::cout << sum(values) << '\n';

    const User user = get_user(true);
    print_name(user);

    const int value = 42;
    std::cout << value << '\n';

    std::map<std::string, int> word_to_count;
    word_to_count.emplace("one", 1);
    word_to_count.emplace("two", 2);

    for (const auto& [key, value] : word_to_count) { 
        std::cout << key << '\n';
    }

    return 0;
}